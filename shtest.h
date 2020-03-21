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
    static t_test IDENT = { #IDENT, IDENT ## _func };\
    static void IDENT ## _func(t_test* _test)

#define TESTSUITE(NAME) t_test* NAME[]

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

static int run_tests(t_test** tests) {
    t_test* current = *tests;
    int successful = 0;
    int total = 0;

    while(current) {
        current->body(current);
        fprintf(stdout, "%s ... ", current->name);
        if (current->error_outcome == NULL) {
            successful++;
            fprintf(stdout, "OK\n");
        } else {
            fprintf(stdout, "FAILED: %s\n", current->error_outcome);
        }
        current = tests[++total];
    }

    fprintf(stdout, "\n%d/%d tests successful\n", successful, total);
}

#ifdef __cplusplus
}
#endif

#endif

