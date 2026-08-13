/*
 * value.h
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Defines the representation of Ra values
 */

#ifndef ra_value_h
#define ra_value_h

#include "common.h"

typedef double Value;

typedef struct
{
    int count;
    int capacity;
    Value* values;
} ValueArray;

void value_print(Value value);

void value_array_init(ValueArray* array);
void value_array_push(ValueArray* array, Value value);
Value value_array_get(ValueArray* array, int index);
void value_array_clear(ValueArray* array);

#endif
