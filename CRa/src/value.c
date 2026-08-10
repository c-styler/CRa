/*
 * value.c
 * Created on Mon Aug 10 2026
 * Part of CRa — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 *
 * Defines the representation of Ra values
 */

#include "value.h"
#include "array.h"
#include "memory.h"

#include <memory.h>
#include <stdio.h>

void value_print(Value value)
{
    printf("%g", value);
}

void value_array_init(ValueArray* array)
{
    assert(array);

    memset(array, 0, sizeof(ValueArray));
}

void value_array_push(ValueArray* array, Value value)
{
    assert(array);

    array->capacity = GROW_CAPACITY(array->capacity);
    array->values =
        ra_realloc(array->values, sizeof(Value) * array->capacity);

    array->values[array->count] = value;
    array->count++;
}

void value_array_clear(ValueArray* array)
{
    assert(array);

    ra_free(array->values);
    value_array_init(array);
}
