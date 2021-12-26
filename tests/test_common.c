/*
 * This file is part of C11_TEMPLATE.
 *
 * This is a simple unit testing library to bootstrap development.
 * 
 */

#include "unit_test.h"

#include "common.h"

DECLARE_TEST (compute_median)
{
    int test_array[] = {1, 2, 3, 4, 5};

    float median = compute_median(test_array, 5);

    TEST_ASSERT_EQUAL_FLT(median, 3.0f, 1e-4f);
}

TEST_REGISTRY_START()
{
    TEST_REGISTER(compute_median);
}

DECLARE_TEST_MAIN()
