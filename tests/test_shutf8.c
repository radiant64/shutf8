#include "test_decode_codepoint.h"
#include "test_encode_codepoint.h"
#include "test_decode_alloc.h"
#include "test_encode_alloc.h"
#include "test_step.h"

int main(int argc, char** argv) {
    int total = 0;
    int successful = 0;
    {
        t_testsuite suite = prepare_decode_codepoint();
        run_tests(&suite);
        total += suite.total;
        successful += suite.successful;
    }
    {
        t_testsuite suite = prepare_encode_codepoint();
        run_tests(&suite);
        total += suite.total;
        successful += suite.successful;
    }
    {
        t_testsuite suite = prepare_decode_alloc();
        run_tests(&suite);
        total += suite.total;
        successful += suite.successful;
    }
    {
        t_testsuite suite = prepare_encode_alloc();
        run_tests(&suite);
        total += suite.total;
        successful += suite.successful;
    }
    {
        t_testsuite suite = prepare_step();
        run_tests(&suite);
        total += suite.total;
        successful += suite.successful;
    }
    return total - successful;
}

