/*
 * vm.h
 * Created on Tue Aug 11 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * The virtual machine that executes our bytecode
 */

#include "vm.h"
#include "debug.h"

#include <stdio.h>

static InterpretResult run(VM* vm);

InterpretResult vm_interpret(VM* vm, Chunk* chunk)
{
    vm->chunk = chunk;
    vm->ip = vm->chunk->code;

    return run(vm);
}

static InterpretResult run(VM* vm)
{
#define READ_BYTE() (*vm->ip++)
#define READ_CONSTANT()                                                \
    (value_array_get(&vm->chunk->constants, READ_BYTE()))

    while (true)
    {
#ifdef DEBUG_TRACE_EXECUTION
        disassemble_instruction(vm->chunk,
                                (int)(vm->ip - vm->chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_RETURN: {
            return INTERPRET_RESULT_OK;
        }
        break;

        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            value_print(constant);
            printf("\n");
            break;
        }
        break;
        }
    }

#undef READ_BYTE()
#undef READ_CONSTANT()
}
