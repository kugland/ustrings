/*
 *  ustrings - A UTF-8 aware version of the `strings` utility.
 *
 *  MIT License
 *
 *  Copyright (c) 2026 André Kugland
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>

#define DEC2(a, b) (((a) & 31) << 6 | ((b) & 63))
#define DEC3(a, b, c) (((a) & 15) << 12 | ((b) & 63) << 6 | ((c) & 63))
#define DEC4(a, b, c, d) (((a) & 7) << 18 | ((b) & 63) << 12 | ((c) & 63) << 6 | ((d) & 63))

static const int exp_len_tbl[] = { 2, 2, 2, 2, 3, 3, 4 };

int
main(void)
{
    int ch;
    char buf[4] = { 0 };
    int cur_len = 0, exp_len = 0;

    while ((ch = getchar()) != EOF) {
        if (ch >= 256)
            abort(); /* Should never happen. */

        if (ch < 128) {
            /* ASCII character, just output it */
            putchar(ch);
            cur_len = 0; /* Reset any ongoing UTF-8 sequence */
            continue;
        }

        if (cur_len == 0) { /* Start of a new UTF-8 sequence */
            if (ch >= 192 && ch < 248) {
                /* Determine expected length based on leading byte */
                exp_len = exp_len_tbl[(ch - 192) >> 3];
            } else {
                /* Invalid leading byte, skip */
                continue;
            }
        } else if ((ch & 192) != 128) {
            /* Invalid continuation byte, reset state */
            cur_len = 0;
            continue;
        }

        if (cur_len < exp_len) {
            /* Collect bytes of the UTF-8 sequence */
            buf[cur_len++] = ch;
        }

        if (cur_len == exp_len) {
            /* When we have all bytes, decode them... */
            unsigned int cp = 0;
            if (cur_len == 2) {
                cp = DEC2(buf[0], buf[1]);
            } else if (cur_len == 3) {
                cp = DEC3(buf[0], buf[1], buf[2]);
            } else if (cur_len == 4) {
                cp = DEC4(buf[0], buf[1], buf[2], buf[3]);
            } else {
                abort(); /* Should never happen. */
            }
            /* And check validity */
            if (cp < 0xD800 || (cp >= 0xE000 && cp <= 0x10FFFF)) {
                /* Valid code point, output the bytes */
                fwrite(buf, 1, cur_len, stdout);
            }
            cur_len = 0; /* Reset for next sequence */
        }
    }

    return 0;
}
