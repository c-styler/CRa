/*
 * code.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Defines bytecode opcodes and chunks
 */

#include "code.h"
#include "array.h"
#include "memory.h"

#include <memory.h>
#include <stdlib.h>

void chunk_init(Chunk* chunk)
{
    assert(chunk);

    memset(chunk, 0, sizeof(Chunk));
    value_array_init(&chunk->constants);
}

void chunk_push(Chunk* chunk, uint8_t byte)
{
    assert(chunk);

    chunk->capacity = GROW_CAPACITY(chunk->capacity);
    chunk->code =
        ra_realloc(chunk->code, sizeof(uint8_t) * chunk->capacity);

    chunk->code[chunk->count] = byte;
    chunk->count++;
}

void chunk_push(Chunk* c, uint8_t val)
{
    if (c->code && (c->capacity < c->count + 1))
    {
        c->capacity *= 2;
        c->code = ra_realloc(c->code, sizeof(uint8_t) * c->capacity);
    }
    else
    {
        c->capacity = 8;
        c->code = ra_realloc(NULL, sizeof(uint8_t) * c->capacity);
    }

    c->code[c->count] = val;
    c->count++;
}

void chunk_clear(Chunk* chunk)
{
    assert(chunk);

    ra_free(chunk->code);
    value_array_clear(&chunk->constants);
    chunk_init(chunk);
}
