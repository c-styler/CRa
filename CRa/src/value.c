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
    memset(array, 0, sizeof(ValueArray));
}

void value_array_push(ValueArray* array, Value value)
{
    if (array->count >= array->capacity)
    {
        array->capacity = GROW_CAPACITY(array->capacity);
        array->values =
            ra_realloc(array->values, sizeof(Value) * array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

Value value_array_get(ValueArray* array, int index)
{
    assert((index < array->count) || (index >= 0));

    return array->values[index];
}

void value_array_clear(ValueArray* array)
{
    ra_free(array->values);
    value_array_init(array);
}
