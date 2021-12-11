/*
 * This file is part of C11_TEMPLATE.
 *
 * This is a simple unit testing library to bootstrap development.
 *
 */

#pragma once

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_TESTS (64)

#define TEST_PTR(name) void (*name)()

#define ABS_DIFF(a, b) ((a) > (b) ? ((a) - (b)) : ((b) - (a)))
#define UNUSED(x) (void)(x)

/*!
 *  \brief Macro for declaring a test
 *
 *  \param name Name of the test
 */
#define DECLARE_TEST(name) \
  void test_##name ()

/*!
 *  \brief Macro for starting test registration
 */
#define TEST_REGISTRY_START() \
  void test_registry_collect()

/*!
 *  \brief Macro for registering a test
 *
 *  \param name Name of the test
 */
#define TEST_REGISTER(name) \
  test_register(#name, test_##name, __LINE__);

/*!
 *  \brief Macro for fetching the current test index
 */
#define TEST_INDEX \
  registry_get()->current_index

/*!
 *  \brief Macro for test assertions
 *
 *  \param cond Conditional statement
 */
#define TEST_ASSERT(cond)                                               \
  do                                                                    \
  {                                                                     \
      if (!test_assert((cond)))                                         \
      {                                                                 \
          fprintf(stderr, "[%3d] - Assertion (%s)", TEST_INDEX, #cond); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);           \
      }                                                                 \
  }                                                                     \
  while (0);

#define TEST_ASSERT_PASS(output) TEST_ASSERT((output) == 1)
#define TEST_ASSERT_FAIL(output) TEST_ASSERT((output) == 0)

/*!
 *  \brief Macro for test assertions with integers
 */
#define TEST_ASSERT_EQUAL_INT(a, b)                                      \
  do                                                                     \
  {                                                                      \
      if (!test_assert(((a) == (b))))                                    \
      {                                                                  \
          fprintf(stderr, "[%3d] - [%d] != [%d]", TEST_INDEX, (a), (b)); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);            \
      }                                                                  \
  }                                                                      \
  while (0);

/*!
 *  \brief Macro for test assertions with floats
 *
 *  \param tol Maximum difference between `a` and `b`
 */
#define TEST_ASSERT_EQUAL_FLT(a, b, tol)                               \
  do                                                                   \
  {                                                                    \
      if (!test_assert((ABS_DIFF(a, b) < (tol))))                      \
      {                                                                \
          fprintf(stderr, "[%3d] - %s != %s\n", TEST_INDEX, #a, #b);   \
          fprintf(stderr, "[%3d] - %f != %f",   TEST_INDEX, (a), (b)); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);          \
      }                                                                \
  }                                                                    \
  while (0);

/*!
 *  \brief Macro for test assertions with doubles
 *
 *  \param tol Maximum difference between `a` and `b`
 */
#define TEST_ASSERT_EQUAL_DBL(a, b, tol)                                   \
  do                                                                       \
  {                                                                        \
      if (!test_assert((ABS_DIFF(a, b) < (tol))))                          \
      {                                                                    \
          fprintf(stderr, "[%3d] - %s != %s\n", TEST_INDEX, #a, #b);       \
          fprintf(stderr, "[%3d] - %.4e != %.4e\n", TEST_INDEX, (a), (b)); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);              \
      }                                                                    \
  }                                                                        \
  while (0);

/*!
 *  \brief Macro for test assertions with complex floats
 *
 *  \param tol Maximum difference between components of `a` and `b`
 */
#define TEST_ASSERT_EQUAL_FC(a, b, tol)                                      \
  do                                                                         \
  {                                                                          \
      if (!test_assert((ABS_DIFF(a.re, b.re) < (tol))))                      \
      {                                                                      \
          fprintf(stderr, "[%3d] - %s.re != %s.re\n", TEST_INDEX, #a, #b);   \
          fprintf(stderr, "[%3d] - %.4e != %.4e\n", TEST_INDEX, a.re, b.re); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);                \
      }                                                                      \
      if (!test_assert((ABS_DIFF(a.im, b.im) < (tol))))                      \
      {                                                                      \
          fprintf(stderr, "[%3d] - %s.im != %s.im\n", TEST_INDEX, #a, #b);   \
          fprintf(stderr, "[%3d] - %.4e != %.4e\n", TEST_INDEX, a.im, b.im); \
          fprintf(stderr, " failed on line %d!\n", __LINE__);                \
      }                                                                      \
  }                                                                          \
  while (0);

/*!
 *  \brief Macro that declares the main of the unit test program
 */
#define DECLARE_TEST_MAIN()                                           \
  int main (int argc, char *argv[])                                   \
  {                                                                   \
      test_registry_t* g_registry = registry_get();                   \
      UNUSED(argc);                                                   \
      UNUSED(argv);                                                   \
      test_registry_init();                                           \
      test_registry_collect();                                        \
      test_run_all();                                                 \
      return (g_registry->failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE); \
  }

/*! Unit test structure */
typedef struct
{
    const char* name;

    volatile sig_atomic_t line;
    volatile sig_atomic_t status;

    size_t failed_asserts;

    TEST_PTR(unit_test);
}
test_t;

/*! Unit test registry */
typedef struct
{
    int passed;
    int failed;
    int num_tests;

    int current_index;

    test_t unit_tests[MAX_TESTS];
}
test_registry_t;

/*!
 *  \brief Retrieve the global registry
 *
 *  \return Pointer to the registry
 */
test_registry_t* registry_get ();

/*!
 *  \brief Unit test signal handler
 *
 *  \param Signal ID
 */
void test_handler (int signal);

/*!
 *  \brief Initialize registry
 */
void test_registry_init ();

/*!
 *  \brief Place a test in the registry
 *
 *  \param name Name of the test
 *  \param unit_test Pointer to the test function
 *  \param line Line number
 */
void test_register (const char* name,
                    TEST_PTR    (unit_test),
                    int         line);

/*!
 *  \brief Run an individual unit test
 *
 *  \param index Unit test index
 */
void test_run (int index);

/*!
 *  \brief Run all registered unit tests
 */
void test_run_all ();

/*!
 *  \brief Function for test assertions
 *
 *  \param cond Conditional statement
 */
int test_assert (int cond);

#ifdef __cplusplus
}
#endif
