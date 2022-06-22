/*
 * This file is part of C11_TEMPLATE.
 *
 * This is a simple unit testing library to bootstrap development.
 * 
 */

/* Stop MSVC from complaining about POSIX functions */
#define _CRT_NONSTDC_NO_DEPRECATE
#include "unit_test.h"

/* Declare the global registry */
static test_registry_t g_registry;

/*! Macro for printing signal handling file / line */
#define SIGNAL_DEBUG(index, name, line) \
  fprintf(stderr, "[%3d] - Signal caught in %s:%d\n", index, name, line);

/*! Macro for printing signal handling error */
#define SIGNAL_ERROR(index, name, msg) \
  fprintf(stderr, "[%3d] - %s - %s\n", index, name, msg);

test_registry_t*
registry_get ()
{
    return &g_registry;
}

void
test_registry_init ()
{
    g_registry.passed = 0;
    g_registry.failed = 0;
    g_registry.num_tests = 0;
    g_registry.current_index = 0;
}

void
test_register (const char* name, TEST_PTR(unit_test), int line)
{
    test_t *test = &g_registry.unit_tests[g_registry.num_tests];

    test->name = name;
    test->line = line;
    test->status = 1;
    test->unit_test = unit_test;

    g_registry.num_tests++;
}

void
test_run (int index)
{
    test_t *test = &g_registry.unit_tests[index];

    TEST_INDEX = index;

    fprintf(stderr, "[%3d] - Running test %s...\n", index, test->name);

    test->unit_test();

    if (test->status > 0)
    {
        fprintf(stderr, "[%3d] - Running test %s passed!\n", index, test->name);
        g_registry.passed++;
    }
    else
    {
        fprintf(stderr, "[%3d] - Running test %s failed!\n", index, test->name);
        g_registry.failed++;
    }
}

void
test_run_all ()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "| Running all of the unit tests\n");
    fprintf(stderr, "----------------------------------------------\n");

    for (int i = 0; i < g_registry.num_tests; i++)
    {
        test_run(i);
    }

    fprintf(stderr, "----------------------------------------------\n");
    fprintf(stderr, "| Finished running %d tests\n", g_registry.num_tests);
    fprintf(stderr, "| Summary:\n");
    fprintf(stderr, "| - Passed = %d\n", g_registry.passed);
    fprintf(stderr, "| - Failed = %d\n", g_registry.failed);
    fprintf(stderr, "\n");
}

int
test_assert (int cond)
{
    test_t *test = &g_registry.unit_tests[TEST_INDEX];

    if (test->status)
    {
        test->status = cond;
    }
    return cond;
}
