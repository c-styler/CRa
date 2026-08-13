/*
 * vm.h
 * Created on Tue Aug 11 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * The virtual machine that executes our bytecode
 */

#ifndef ra_vm_h
#define ra_vm_h

#include "code.h"
#include "common.h"

typedef struct
{
    Chunk* chunk;
    uint8_t* ip;
} VM;

typedef enum
{
    INTERPRET_RESULT_OK,
    INTERPRET_RESULT_COMPILE_TIME_ERROR,
    INTERPRET_RESULT_RUNTIME_ERROR
} InterpretResult;

InterpretResult vm_interpret(VM* vm, Chunk* chunk);

#endif
