/*
 * This file is part of C11_TEMPLATE.
 *
 */

#include "common.h"

float
compute_median (const int* array, size_t size)
{
    if (array == NULL || size == 0) return 0.0f;

    size_t mid = size / 2;

    float result = 0.0f;
    if ((size % 2) == 0)
    {
        result = ((float) (array[mid - 1] + array[mid])) / 2.0f;
    }
    else
    {
        result = ((float) (array[mid]));
    }
    return result;
}
