#ifndef SHTEST_H
#define SHTEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#if __STDC_VERSION__ >= 19990L
#include <stddef.h>
#else
#include <stdlib.h>
#endif

#define FALSE ((t_bool) 0)
#define TRUE (!FALSE)

#define _STR(N) _STR_EXPAND(N)
#define _STR_EXPAND(N) #N
#define TEST(IDENT) static void IDENT ## _func(t_test*);\
    static t_test IDENT ## obj = { #IDENT, IDENT ## _func };\
    static t_test* IDENT = &IDENT ## obj;\
    static void IDENT ## _func(t_test* _test)

#define TESTSUITE(NAME) t_testsuite prepare_ ## NAME(void) {\
    return (t_testsuite) {\
        #NAME,\
        0,\
        0,\
        {

#define END_TESTSUITE ,\
            NULL\
        }\
    };\
}

#define EXTERN_TESTSUITE(NAME) t_testsuite prepare_ ## NAME(void);

#define REQUIRE(CONDITION) if (!(CONDITION)) {\
    _test->error_outcome = #CONDITION " (at " __FILE__ ":" _STR(__LINE__) ")";\
    return;\
}

typedef char t_bool;

typedef struct t_test {
    const char* name;
    void(*body)(struct t_test*);
    const char* error_outcome;
} t_test;

typedef struct {
    const char* name;
    int successful;
    int total;
    t_test* tests[256];
} t_testsuite;

static void run_tests(t_testsuite* suite) {
    fprintf(stdout, "Running tests in %s:\n\n", suite->name);
    t_test* current = *(suite->tests);
    while(current) {
        current->body(current);
        fprintf(stdout, "-> %s ...\t", current->name);
        if (current->error_outcome == NULL) {
            suite->successful++;
            fprintf(stdout, "OK\n");
        } else {
            fprintf(stdout, "FAILED: %s\n", current->error_outcome);
        }
        current = suite->tests[++(suite->total)];
    }

    fprintf(
        stdout,
        "\n%d/%d tests successful\n----------------\n",
        suite->successful,
        suite->total
    );
}

#ifdef __cplusplus
}
#endif

#endif

