#ifndef ra_code_h
#define ra_code_h

#include "common.h"

typedef enum
{
    OP_RETURN,
} Opcode;

typedef struct
{
    int count;
    int capacity;
    uint8_t* code;
} Chunk;

void chunk_init(Chunk* c);
void chunk_push(Chunk* c, uint8_t val);
void chunk_clear(Chunk* c);

#endif
