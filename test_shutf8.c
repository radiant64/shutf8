#include "shutf8.h"
#include "shtest.h"

TEST(verify_shutf8_utf32_c_is_large_enough) {
   REQUIRE(sizeof(shutf8_utf32_c) >= 4); 
}


int main(int argc, char** argv) {
    TESTSUITE(tests,  
        &verify_shutf8_utf32_c_is_large_enough
    )

    return run_tests(tests);
}

