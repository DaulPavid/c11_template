/*
 * This file is part of C11_TEMPLATE.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "print_hello.h"

int
main (int argc, char* argv[])
{
    print_hello();

    printf("C11_TEMPLATE %d %s\n", argc, argv[0]);

    return EXIT_SUCCESS;
}
