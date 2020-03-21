#ifndef SHUTF8_H
#define SHUTF8_H
/**
 * @file shutf8.h
 * Single Header UTF-8
 * version 1.0.0
 */ 
/* Copyright (c) Martin Evald
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifdef __cplusplus
extern "C" {
#endif

#ifndef SHUTF8_UTF32_C
#if __STDC_VERSION__ >= 19990L
#include <stdint.h>
#define SHUTF8_UTF32_C int_least32_t
#else
#define SHUTF8_UTF32_C int
#endif
#endif

/**
 * @typedef shutf8_utf32_c
 * @brief A platform specific type corresponding to a 32 bit signed Unicode
 * codepoint.
 */
typedef SHUTF8_UTF32_C shutf8_utf32_c;

/**
 * @brief A type representing a Unicode codepoint in the form of a UTF-8
 * encoded octet sequence.
 * */
typedef struct shutf8_utf8_c {
    unsigned char len; /**< Number of bytes in the sequence. */
    const unsigned char b[4]; /**< Array of individual octets. */
} shutf8_utf8_c;

/**
 * @brief Decode the UTF-8 encoded codepoint residing at the supplied address
 * into a UTF-32 value.
 * @param cursor Pointer into a UTF-8 encoded string.
 * @return The Unicode codepoint translated into a #shutf8_utf32_c number.
 */
shutf8_utf32_c shutf8_decode(const char* cursor);

/**
 * @brief Returns a pointer to the next codepoint in the supplied UTF-8 encoded
 * string.
 * @param cursor Pointer into a UTF-8 encoded string.
 * @return A pointer to the beginning of the next codepoint in the provided
 * string.
 */
const char* shutf8_step(const char* cursor);

/**
 * @brief Encode a UTF-32 codepoint into a UTF-8 sequence.
 * @param codepoint UTF-32 codepoint.
 * @return The corresponding UTF-8 sequence.
 */
shutf8_utf8_c shutf8_encode_codepoint(shutf8_utf32_c codepoint);

/**
 * @cond NON_DOXYGEN
 */

#define SHUTF8_CHECK_MALFORMED(C) if ((C & 0xc0) != 0x80) { return -1; }

shutf8_utf32_c shutf8_decode(const char* cursor) {
    const unsigned char* c = cursor;
    if ((*c & 0x80) && (*c < 0xc0) || (*c >= 0xf1)) {
        /* Malformed UTF-8 character. */
        return -1;
    }
    switch (*c & 0xf0) {
    case 0xc0:
        SHUTF8_CHECK_MALFORMED(c[1])
        /* Mask: 00011111 00111111 */
        return ((c[0] & 0x1f) << 6) | (c[1] & 0x3f);
    case 0xe0:
        SHUTF8_CHECK_MALFORMED(c[1])
        SHUTF8_CHECK_MALFORMED(c[2])
        /* Mask: 00001111 00111111 00111111 */
        return ((c[0] & 0x0f) << 12) | ((c[1] & 0x3f) << 6) | (c[2] & 0x3f);
    case 0xf0:
        SHUTF8_CHECK_MALFORMED(c[1])
        SHUTF8_CHECK_MALFORMED(c[2])
        SHUTF8_CHECK_MALFORMED(c[3])
        /* Mask: 00000111 00111111 00111111 00111111 */
        return ((c[0] & 0x07) << 18)
            | ((c[1] & 0x3f) << 12)
            | ((c[2] & 0x3f) << 6)
            | (c[3] & 0x3f);
    default:
        return *c;
    }
}

#undef SHUTF8_CHECK_MALFORMED

const char* shutf8_step(const char* cursor) {
    switch (*cursor & 0xf0) {
    case 0xf0:
        return &(cursor[4]);
    case 0xe0:
        return &(cursor[3]);
    case 0xc0:
        return &(cursor[2]);
    default:
        /* Treat malformed codepoints as single bytes. */
        return &(cursor[1]);
    }
}

shutf8_utf8_c shutf8_encode_codepoint(shutf8_utf32_c codepoint) {
    unsigned char len = 1;
    char b[4];

    if (codepoint > 0x10ffff) {
        /* Illegal codepoint. */
        return (shutf8_utf8_c) { 0 };
    } else if (codepoint > 0xffff) {
        len = 4;
        b[0] = 0xf0 | (codepoint >> 18);
        b[1] = 0x80 | ((codepoint >> 12) & 0x3f);
        b[2] = 0x80 | ((codepoint >> 6) & 0x3f);
        b[3] = 0x80 | (codepoint & 0x3f);
    } else if (codepoint > 0x7ff) {
        len = 3;
        b[0] = 0xe0 | (codepoint >> 12);
        b[1] = 0x80 | ((codepoint >> 6) & 0x3f);
        b[2] = 0x80 | (codepoint & 0x3f);
    } else if (codepoint > 0x7f) {
        len = 2;
        b[0] = 0xc0 | (codepoint >> 6);
        b[1] = 0x80 | (codepoint & 0x3f);
    } else {
        b[0] = codepoint;
    }
    
    return (shutf8_utf8_c) { len, b[0], b[1], b[2], b[3] };
}

/**
 * @endcond
 */

#ifdef __cplusplus
}
#endif

#endif

