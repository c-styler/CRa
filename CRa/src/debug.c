/*
 * debug.c
 * Created on Mon Aug 10 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Disassembler & Debugging related functionality
 */

#include "debug.h"

#include <stdio.h>

static int simple_instruction(const char* name, int offset)
{
    printf("%s\n", name);
    return offset;
}

void disassemble_chunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count; offset++)
    {
        offset = disassemble_instruction(chunk, offset);
    }
}

int disassemble_instruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
    case OP_RETURN: {
        return simple_instruction("OP_RETURN", offset);
    }

    default: {
        printf("Unknown opcode: %d\n", instruction);
        return offset + 1;
    }
    break;
        break;
    }
}
