#include "test_encode_codepoint.h"
#include "../shutf8.h"

TEST(verify_encoded_length_valid_1_byte) {
    unsigned char len = shutf8_encoded_length('a');
    REQUIRE(len == 1);
}

TEST(verify_encoded_length_valid_2_byte) {
}

TEST(verify_encoded_length_valid_3_byte) {
}

TEST(verify_encoded_length_valid_4_byte) {
}

TESTSUITE(encode_codepoint)
    verify_encoded_length_valid_1_byte
END_TESTSUITE
