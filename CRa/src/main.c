/*
 * main.c
 * Created on Mon Aug 10 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 */

#include "code.h"
#include "common.h"
#include "debug.h"

int main(int argc, char* argv[])
{
    Chunk chunk;
    chunk_init(&chunk);
    chunk_push(&chunk, OP_RETURN);

    disassemble_chunk(&chunk, "Chunk1");
    chunk_clear(&chunk);

    return 0;
}
