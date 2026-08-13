/*
 * main.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 */

#include "code.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char* argv[])
{
    Chunk chunk;
    chunk_init(&chunk);

    int constant_index = chunk_push_constant(&chunk, 1.2);
    chunk_push(&chunk, OP_CONSTANT, 1);
    chunk_push(&chunk, constant_index, 1);
    chunk_push(&chunk, OP_CONSTANT, 1);
    chunk_push(&chunk, constant_index, 1);
    chunk_push(&chunk, OP_RETURN, 2);

    VM vm = {0};
    vm_init(&vm);
    vm_interpret(&vm, &chunk);

    //    disassemble_chunk(&chunk, "Chunk1");
    chunk_clear(&chunk);

    return 0;
}
