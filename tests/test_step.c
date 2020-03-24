#include "test_step.h"
#include "../shutf8.h"

TEST(verify_step_0_no_step) {
    const char seq[] = { 0x00, 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == seq);
}

TEST(verify_step_1_byte_works) {
    const char seq[] = { 'a', 'b' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == &seq[1]);
}

TEST(verify_step_2_bytes_works) {
    const char seq[] = { '\xc3', '\xa5', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == &seq[2]);
}

TEST(verify_step_3_bytes_works) {
    const char seq[] = { '\xe4', '\xb8', '\xad', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == &seq[3]);
}

TEST(verify_step_4_bytes_works) {
    const char seq[] = { '\xf0', '\x9f', '\x98', '\x80', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == &seq[4]);
}

TEST(verify_step_illegal_1_byte_fails) {
    const char seq[] = { 0x80, 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == NULL);
}

TEST(verify_step_illegal_2_bytes_fails) {
    const char seq[] = { '\xc3', '\x15', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == NULL);
}

TEST(verify_step_illegal_3_bytes_fails) {
    const char seq[] = { '\xe4', '\xb8', '\x2d', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == NULL);
}

TEST(verify_step_illegal_4_bytes_fails) {
    const char seq[] = { '\xf0', '\x9f', '\x98', '\x00', 'a' };
    const char* pos = shutf8_step(seq);
    REQUIRE(pos == NULL);
}

TESTSUITE(step)
    verify_step_0_no_step,
    verify_step_1_byte_works,
    verify_step_2_bytes_works,
    verify_step_3_bytes_works,
    verify_step_4_bytes_works,
    verify_step_illegal_1_byte_fails,
    verify_step_illegal_2_bytes_fails,
    verify_step_illegal_3_bytes_fails,
    verify_step_illegal_4_bytes_fails
END_TESTSUITE

