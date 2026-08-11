/*
 * code.h
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Defines bytecode opcodes and chunks
 */

#ifndef ra_code_h
#define ra_code_h

#include "common.h"
#include "value.h"

typedef enum
{
    OP_RETURN,
    OP_CONSTANT,
} Opcode;

typedef struct
{
    int number;
    int size; // How many bytes this line covers
} LineEntry;

typedef struct
{
    int count;
    int capacity;
    uint8_t* code;

    LineEntry* lines;
    int lines_count;
    int lines_capacity;

    ValueArray constants;
} Chunk;

void chunk_init(Chunk* chunk);
void chunk_push(Chunk* chunk, uint8_t byte, int line);
int chunk_push_constant(Chunk* chunk, Value value);
void chunk_clear(Chunk* chunk);

#endif
