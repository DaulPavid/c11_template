/*
 * This file is part of C11_TEMPLATE.
 *
 * This is a simple unit testing library to bootstrap development.
 * 
 */

#include "unit_test.h"

DECLARE_TEST (print_hello_0)
{
    TEST_ASSERT(1);
}

TEST_REGISTRY_START()
{
    TEST_REGISTER(print_hello_0);
}

DECLARE_TEST_MAIN()
