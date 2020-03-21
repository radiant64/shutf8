#include "shutf8.h"
#include "shtest.h"

TEST(verify_shutf8_utf32_c_is_large_enough) {
   REQUIRE(sizeof(shutf8_utf32_c) >= 4); 
}

TEST(verify_decode_valid_single_byte_is_working) {
    shutf8_utf32_c codepoint = shutf8_decode("a");
    REQUIRE(codepoint == 'a');
}

TEST(verify_decode_valid_2_bytes_is_working) {
    const char seq[] = { '\xc3', '\xa5' };
    shutf8_utf32_c codepoint = shutf8_decode(seq);
    REQUIRE(codepoint == 0xe5);
}

TEST(verify_decode_valid_3_bytes_is_working) {
    const char seq[] = { '\xe4', '\xb8', '\xad' };
    shutf8_utf32_c codepoint = shutf8_decode(seq);
    REQUIRE(codepoint == 0x4e2d);
}

TEST(verify_decode_valid_4_bytes_is_working) {
    const char seq[] = { '\xf0', '\x9f', '\x98', '\x80' };
    shutf8_utf32_c codepoint = shutf8_decode(seq);
    REQUIRE(codepoint == 0x1f600);
}

int main(int argc, char** argv) {
    TESTSUITE(tests) = {
        &verify_shutf8_utf32_c_is_large_enough,
        &verify_decode_valid_single_byte_is_working,
        &verify_decode_valid_2_bytes_is_working,
        &verify_decode_valid_3_bytes_is_working,
        &verify_decode_valid_4_bytes_is_working,
        NULL
    };

    return run_tests(tests);
}

