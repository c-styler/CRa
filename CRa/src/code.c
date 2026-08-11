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

void chunk_push(Chunk* chunk, uint8_t byte, int line)
{
    assert(chunk);

    if (chunk->count >= chunk->capacity)
    {
        chunk->capacity = GROW_CAPACITY(chunk->capacity);
        chunk->code =
            ra_realloc(chunk->code, sizeof(uint8_t) * chunk->capacity);
    }

    for (int i = 0; i < chunk->lines_count; i++)
    {
        LineEntry* line_entry = chunk->lines + i;
        if (line_entry->number == line)
        {
            line_entry->size++;
            goto line_tracked;
        }
    }

    if (chunk->lines_count >= chunk->lines_capacity)
    {
        chunk->lines_capacity = GROW_CAPACITY(chunk->lines_capacity);
        chunk->lines = ra_realloc(
            chunk->lines, sizeof(LineEntry) * chunk->lines_capacity);
    }

    LineEntry* line_entry = chunk->lines + chunk->lines_count;
    line_entry->number = line;
    line_entry->size = 1;
    chunk->lines_count++;

line_tracked:
    chunk->code[chunk->count] = byte;
    chunk->count++;
}

int chunk_push_constant(Chunk* chunk, Value value)
{
    assert(chunk);

    value_array_push(&chunk->constants, value);
    return chunk->constants.count - 1;
}

void chunk_clear(Chunk* chunk)
{
    assert(chunk);

    ra_free(chunk->code);
    ra_free(chunk->lines);
    value_array_clear(&chunk->constants);
    chunk_init(chunk);
}
