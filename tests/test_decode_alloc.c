#include "test_decode_alloc.h"
#include "../shutf8.h"

#include <string.h>

TEST(verify_decode_empty_string) {
    const char utf8_str[] = "";
    shutf8_utf32_c* utf32_str = shutf8_decode_alloc(utf8_str);
    REQUIRE(*utf32_str == 0);
    free(utf32_str);
}

TEST(verify_decode_valid_string) {
    const char utf8_str[] = { '\xc3', '\xa5', '\0' };
    shutf8_utf32_c* utf32_str = shutf8_decode_alloc(utf8_str);
    REQUIRE(*utf32_str == 0xe5);
    free(utf32_str);
}

TEST(verify_decode_invalid_string_fails) {
    const char utf8_str[] = { '\xc3', '\x15', '\0' };
    shutf8_utf32_c* utf32_str = shutf8_decode_alloc(utf8_str);
    REQUIRE(utf32_str == NULL);
}

TESTSUITE(decode_alloc)
    verify_decode_empty_string,
    verify_decode_valid_string,
    verify_decode_invalid_string_fails
END_TESTSUITE

