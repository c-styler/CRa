/*
 * memory.h
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Wrapper module over the libc allocator, mainly for debugging
 */

#ifndef ra_memory_h
#define ra_memory_h

#include "common.h"

void* ra_realloc(void* block, size_t new_size);
void ra_free(void* block);

#endif
