/*
 * debug.h
 * Created on Mon Aug 10 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Disassembler & Debugging related functionality
 */

#ifndef ra_debug_h
#define ra_debug_h

#include "code.h"

void disassemble_chunk(Chunk* chunk, const char* name);
int disassemble_instruction(Chunk* chunk, int offset);

#endif
