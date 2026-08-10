#ifndef ra_debug_h
#define ra_debug_h

#include "code.h"

void disassemble_chunk(Chunk* chunk, const char* name);
int disassemble_instruction(Chunk* chunk, int offset);

#endif
