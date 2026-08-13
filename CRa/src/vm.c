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
static void push(VM* vm, Value value);
static Value pop(VM* vm);

void vm_init(VM* vm)
{
    vm->stack_top = vm->stack;
}

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
        printf("          ");
        for (Value* slot = vm->stack; slot < vm->stack_top; slot++)
        {
            printf("[ ");
            value_print(*slot);
            printf(" ]");
        }
        printf("\n");
        disassemble_instruction(vm->chunk,
                                (int)(vm->ip - vm->chunk->code));
#endif
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_RETURN: {
            value_print(pop(vm));
            printf("\n");
            return INTERPRET_RESULT_OK;
        }
        break;

        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(vm, constant);
            break;
        }
        break;
        }
    }

#undef READ_BYTE()
#undef READ_CONSTANT()
}

static void push(VM* vm, Value value)
{
    if ((vm->stack_top - vm->stack) >= VALUE_STACK_MAX)
    {
        assert("ERROR: Stack Overflow");
    }

    *(vm->stack_top) = value;
    vm->stack_top++;
}

static Value pop(VM* vm)
{
    if (vm->stack_top <= vm->stack)
    {
        assert("ERROR: Stack Underflow");
    }
    vm->stack_top--;
    return *(vm->stack_top);
}
