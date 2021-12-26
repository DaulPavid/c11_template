/*
 * This file is part of C11_TEMPLATE.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "common.h"

int
main (int argc, char* argv[])
{
    int test_array[] = {1, 2, 3, 4};

    printf("Median: %f\n", compute_median(test_array, 4));
    printf("C11_TEMPLATE %d %s\n", argc, argv[0]);

    return EXIT_SUCCESS;
}
