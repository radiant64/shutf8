#include "test_encode.h"
#include "../shutf8.h"

#include <string.h>

TEST(verify_encode_empty_string) {
    const shutf8_utf32_c utf32_str[] = { 0 };
    char* utf8_str = shutf8_encode(utf32_str);
    REQUIRE(strcmp(utf8_str, "") == 0);
    free(utf8_str);
}

TEST(verify_encode_valid_string) {
    const shutf8_utf32_c utf32_str[] = { 0xe5, 0 };
    char* utf8_str = shutf8_encode(utf32_str);
    REQUIRE(strcmp(utf8_str, "å") == 0);
    free(utf8_str);
}

TEST(verify_encode_invalid_string_fails) {
    const shutf8_utf32_c utf32_str[] = { 0xe5, 0xffffff, 0 };
    char* utf8_str = shutf8_encode(utf32_str);
    REQUIRE(utf8_str == NULL);
}

TESTSUITE(encode)
    verify_encode_empty_string,
    verify_encode_valid_string,
    verify_encode_invalid_string_fails
END_TESTSUITE

