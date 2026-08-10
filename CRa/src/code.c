/*
 * code.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Defines bytecode opcodes and chunks
 */

#include "code.h"
#include "memory.h"

#include <memory.h>
#include <stdlib.h>

void chunk_init(Chunk* c)
{
    memset(c, 0, sizeof(Chunk));
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

void chunk_clear(Chunk* c)
{
    ra_free(c->code);
    chunk_init(c);
}
