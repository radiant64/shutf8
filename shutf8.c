#include "shutf8.h"

const char* shutf8_step(const char* cursor) {
    const unsigned char* c = cursor;
    if (!*c) {
        return cursor;
    } else if (((*c & 0x80) && (*c < 0xc0)) || (*c >= 0xf1)) {
        /* Malformed UTF-8 character. */
        return NULL;
    }
    switch (*c & 0xf0) {
    case 0xf0:
        if (((c[1] & c[2] & c[3]) & 0xc0) != 0x80) {
            return NULL;
        }
        return &(cursor[4]);
    case 0xe0:
        if (((c[1] & c[2]) & 0xc0) != 0x80) {
            return NULL;
        }
        return &(cursor[3]);
    case 0xc0:
        if ((c[1] & 0xc0) != 0x80) {
            return NULL;
        }
        return &(cursor[2]);
    default:
        return &(cursor[1]);
    }
}

shutf8_utf32_c shutf8_decode_codepoint(const char* cursor) {
    const unsigned char* c = cursor;
    if (((*c & 0x80) && (*c < 0xc0)) || (*c >= 0xf1)) {
        /* Malformed UTF-8 character. */
        return -1;
    }
    switch (*c & 0xf0) {
    case 0xc0:
        if ((c[1] & 0xc0) != 0x80) {
            return -1;
        }
        /* Mask: 00011111 00111111 */
        return ((c[0] & 0x1f) << 6) | (c[1] & 0x3f);
    case 0xe0:
        if (((c[1] & c[2]) & 0xc0) != 0x80) {
            return -1;
        }
        /* Mask: 00001111 00111111 00111111 */
        return ((c[0] & 0x0f) << 12) | ((c[1] & 0x3f) << 6) | (c[2] & 0x3f);
    case 0xf0:
        if (((c[1] & c[2] & c[3]) & 0xc0) != 0x80) {
            return -1;
        }
        /* Mask: 00000111 00111111 00111111 00111111 */
        return ((c[0] & 0x07) << 18)
            | ((c[1] & 0x3f) << 12)
            | ((c[2] & 0x3f) << 6)
            | (c[3] & 0x3f);
    default:
        return *c;
    }
}

shutf8_utf32_c* shutf8_decode_alloc(const char* source) {
    shutf8_utf32_c* target;
    size_t i;
    const char* cursor = source;
    size_t len = 0;
    while (*cursor) { 
        len++;
        cursor = shutf8_step(cursor);
        if (!cursor) {
            return NULL;
        }
    }

    target = malloc(sizeof(shutf8_utf32_c) * (len + 1));
    if (!target) {
        return NULL;
    }

    cursor = source;
    for (i = 0; i < len; ++i) {
        target[i] = shutf8_decode_codepoint(cursor);
        cursor = shutf8_step(cursor);
    }
    target[len] = 0;

    return target;
}

unsigned char shutf8_encoded_length(shutf8_utf32_c codepoint) {
    if (codepoint < 0) {
        /* Illegal codepoint. */
        return 0;
    } else if (codepoint < 0x80) {
        return 1;
    } else if (codepoint < 0x800) {
        return 2;
    } else if (codepoint < 0x10000) {
        return 3;
    } else if (codepoint < 0x110000) {
        return 4;
    } 
    /* Illegal codepoint. */
    return 0;
}

shutf8_utf8_c shutf8_encode_codepoint(shutf8_utf32_c codepoint) {
    char b[4];
    unsigned char len = shutf8_encoded_length(codepoint);

    switch (len) {
    case 4:
        b[0] = 0xf0 | (codepoint >> 18);
        b[1] = 0x80 | ((codepoint >> 12) & 0x3f);
        b[2] = 0x80 | ((codepoint >> 6) & 0x3f);
        b[3] = 0x80 | (codepoint & 0x3f);
        break;
    case 3:
        b[0] = 0xe0 | (codepoint >> 12);
        b[1] = 0x80 | ((codepoint >> 6) & 0x3f);
        b[2] = 0x80 | (codepoint & 0x3f);
        break;
    case 2:
        b[0] = 0xc0 | (codepoint >> 6);
        b[1] = 0x80 | (codepoint & 0x3f);
        break;
    case 1:
        b[0] = codepoint;
        break;
    default:
        /* Illegal codepoint. */
        return (shutf8_utf8_c) { 0 };
    }
    
    return (shutf8_utf8_c) { len, b[0], b[1], b[2], b[3] };
}

char* shutf8_encode_alloc(const shutf8_utf32_c* source) {
    char* target;
    size_t c_len;
    size_t len = 0;
    size_t i = 0;
    
    while (source[i]) {
        c_len = shutf8_encoded_length(source[i++]);
        if (!c_len) {
            return NULL;
        }
        len += c_len;
    }

    target = malloc(len + 1);
    if (!target) {
        return NULL;
    }

    i = 0;
    len = 0;
    while (source[i]) {
        shutf8_utf8_c c_encoded = shutf8_encode_codepoint(source[i++]);
        memcpy(&target[len], c_encoded.b, c_encoded.len);
        len += c_encoded.len;
    }
    target[len] = '\0';
    
    return target;
}

