#include "libmx.h"

void mx_print_unicode(wchar_t c) {
    char buf[4];
    int len = 0;

    if (c <= 0x7F) {
        buf[len++] = (char)c;  // Однобайтовий символ
    } else if (c <= 0x7FF) {
        buf[len++] = (char)((c >> 6) | 0xC0);      // Два байти для UTF-8
        buf[len++] = (char)((c & 0x3F) | 0x80);
    } else if (c <= 0xFFFF) {
        buf[len++] = (char)((c >> 12) | 0xE0);     // 3
        buf[len++] = (char)(((c >> 6) & 0x3F) | 0x80);
        buf[len++] = (char)((c & 0x3F) | 0x80);
    } else if (c <= 0x10FFFF) {
        buf[len++] = (char)((c >> 18) | 0xF0);     // 4
        buf[len++] = (char)(((c >> 12) & 0x3F) | 0x80);
        buf[len++] = (char)(((c >> 6) & 0x3F) | 0x80);
        buf[len++] = (char)((c & 0x3F) | 0x80);
    }

    write(1, buf, len);  //  сформований буфер
}
