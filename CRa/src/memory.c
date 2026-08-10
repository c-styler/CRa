/*
 * memory.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Wrapper module over the libc allocator, mainly for debugging
 */

#include "memory.h"

#include <stdio.h>
#include <stdlib.h>

void* ra_realloc(void* block, size_t new_size)
{
    assert(new_size > 0);

    void* result = realloc(block, new_size);
    if (result == NULL)
    {
        printf("ERROR: Memory allocation failed\n");
        exit(1);
    }

    return result;
}

void ra_free(void* block)
{
    free(block);
}
