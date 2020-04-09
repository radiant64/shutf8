#ifndef SHUTF8_H
#define SHUTF8_H
/**
 * @file shutf8.h
 * Single Header UTF-8
 *
 * version 3.0.0
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

#include <stdlib.h>
#include <string.h>
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
 * @brief Returns a pointer to the next codepoint in the supplied UTF-8 encoded
 * string.
 * @param cursor Pointer into a UTF-8 encoded string.
 * @return A pointer to the beginning of the next codepoint in the provided
 * string, alternatively @p cursor if the codepoint at @p cursor is 0, or NULL
 * if it is invalid.
 */
const char* shutf8_step(const char* cursor);

/**
 * @brief Decodes the UTF-8 encoded codepoint residing at the supplied address
 * into a UTF-32 value.
 * @param cursor Pointer into a UTF-8 encoded string.
 * @return The Unicode codepoint translated into a #shutf8_utf32_c number.
 */
shutf8_utf32_c shutf8_decode_codepoint(const char* cursor);

/**
 * @brief Decodes a UTF-8 encoded string into UTF-32, allocating space for the
 * result.
 *
 * The zero-terminated UTF-8 string residing at the supplied address will be
 * decoded into a zero terminated UTF-32 string, allocating as much heap memory
 * as is necessary to hold the new string.
 * 
 * Caller is responsible for freeing the allocated memory.
 * 
 * This operation is O(2n), since it will need to iterate over the string once
 * to count how many codepoints it contains, and then again to populate the
 * codepoints after the required memory has been allocated.
 *
 * @param source Pointer to a UTF-8 encoded string.
 * @return A newly allocated string of UTF-32 characters, or NULL on failure
 * (illegal codepoint or failed memory allocation).
 */
shutf8_utf32_c* shutf8_decode_alloc(const char* source);

/**
 * @brief Determines how many octets the UTF-32 codepoint would consist of when
 * recoded to UTF-8.
 * @param codepoint UTF-32 codepoint.
 * @return A number n such that 1 <= n <= 4 for a valid codepoint. 0 otherwise.
 */
unsigned char shutf8_encoded_length(shutf8_utf32_c codepoint);

/**
 * @brief Encodes a UTF-32 codepoint into a UTF-8 sequence.
 * @param codepoint UTF-32 codepoint.
 * @return The corresponding UTF-8 sequence.
 */
shutf8_utf8_c shutf8_encode_codepoint(shutf8_utf32_c codepoint);

/**
 * @brief Encodes a UTF-32 string into UTF-8, allocating space for the result.
 *
 * The supplied zero-terminated UTF-32 string will be encoded into
 * zero-terminated UTF-8, allocating as much heap memory as is necesary to hold
 * the new string.
 *
 * Caller is responsible for freeing the allocated memory.
 *
 * This operation is O(2n), since it will first iterate over the codepoints to
 * determine the total number of octets in the resulting string, and then again
 * when encoding the string after allocating the required memory.
 *
 * @param source A string of @ref shutf8_utf32_c codepoints.
 * @return A newly allocated string of UTF-8 characters, or NULL on failure
 * (illegal codepoint or failed memory allocation).
 */
char* shutf8_encode_alloc(const shutf8_utf32_c* source);

#ifdef __cplusplus
}
#endif

#endif

