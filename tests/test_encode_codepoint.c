#include "test_encode_codepoint.h"
#include "../shutf8.h"

TEST(verify_encoded_length_valid_1_byte) {
    unsigned char len = shutf8_encoded_length('a');
    REQUIRE(len == 1);
}

TEST(verify_encoded_length_valid_2_byte) {
    unsigned char len = shutf8_encoded_length(0xe5);
    REQUIRE(len == 2);
}

TEST(verify_encoded_length_valid_3_byte) {
    unsigned char len = shutf8_encoded_length(0x4e2d);
    REQUIRE(len == 3);
}

TEST(verify_encoded_length_valid_4_byte) {
    unsigned char len = shutf8_encoded_length(0x1f600);
    REQUIRE(len == 4);
}

TEST(verify_encoded_length_invalid) {
    unsigned char len = shutf8_encoded_length(0xffffff);
    REQUIRE(len == 0);
}

TEST(verify_encode_codepoint_valid_1_byte) {
    shutf8_utf8_c c = shutf8_encode_codepoint('a');
    REQUIRE(c.len == 1);
    REQUIRE(c.b[0] == 'a');
}

TEST(verify_encode_codepoint_valid_2_bytes) {
    shutf8_utf8_c c = shutf8_encode_codepoint(0xe5);
    REQUIRE(c.len == 2);
    REQUIRE(c.b[0] == 0xc3);
    REQUIRE(c.b[1] == 0xa5);
}

TEST(verify_encode_codepoint_valid_3_bytes) {
    shutf8_utf8_c c = shutf8_encode_codepoint(0x4e2d);
    REQUIRE(c.len == 3);
    REQUIRE(c.b[0] == 0xe4);
    REQUIRE(c.b[1] == 0xb8);
    REQUIRE(c.b[2] == 0xad);
}

TEST(verify_encode_codepoint_valid_4_bytes) {
    shutf8_utf8_c c = shutf8_encode_codepoint(0x1f600);
    REQUIRE(c.len == 4);
    REQUIRE(c.b[0] == 0xf0);
    REQUIRE(c.b[1] == 0x9f);
    REQUIRE(c.b[2] == 0x98);
    REQUIRE(c.b[3] == 0x80);
}

TEST(verify_encode_codepoint_invalid_fails) {
    shutf8_utf8_c c = shutf8_encode_codepoint(-1);
    REQUIRE(c.len == 0);
}

TESTSUITE(encode_codepoint)
    verify_encoded_length_valid_1_byte,
    verify_encoded_length_valid_2_byte,
    verify_encoded_length_valid_3_byte,
    verify_encoded_length_valid_4_byte,
    verify_encoded_length_invalid,
    verify_encode_codepoint_valid_1_byte,
    verify_encode_codepoint_valid_2_bytes,
    verify_encode_codepoint_valid_3_bytes,
    verify_encode_codepoint_valid_4_bytes,
    verify_encode_codepoint_invalid_fails
END_TESTSUITE

