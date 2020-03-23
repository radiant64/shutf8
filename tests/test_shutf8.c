#include "test_decode_codepoint.h"
#include "test_encode_codepoint.h"
#include "test_encode.h"
#include "test_step.h"

int main(int argc, char** argv) {
    {
        t_testsuite suite = prepare_decode_codepoint();
        run_tests(&suite);
    }
    {
        t_testsuite suite = prepare_encode_codepoint();
        run_tests(&suite);
    }
    {
        t_testsuite suite = prepare_encode();
        run_tests(&suite);
    }
    {
        t_testsuite suite = prepare_step();
        run_tests(&suite);
    }
    return 0;/*(suite.total - suite.successful);
*/
}

