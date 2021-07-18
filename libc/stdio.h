///////////////////////////////////////////////////////////////////////////////
// \author (c) Marco Paland (info@paland.com)
//             2014-2019, PALANDesign Hannover, Germany
//
// \license The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// \brief Tiny printf, sprintf and (v)snprintf implementation, optimized for
// speed on
//        embedded systems with a very limited resources. These routines are
//        thread safe and reentrant! Use this instead of the bloated
//        standard/newlib printf cause these use malloc for printf (and may not
//        be thread safe).
//
///////////////////////////////////////////////////////////////////////////////

#ifndef CKB_C_STDLIB_STDIO_H_
#define CKB_C_STDLIB_STDIO_H_
#include <entry.h>

/*
 * This function uses `ckb_debug` syscall to output formatted messages.
 *
 * Pass `-D CKB_C_STDLIB_PRINTF` flag to GCC to enable printf;
 * If the flag is undefined the printf will be compiled as an empty function.
 *
 * Some versions of GCC raise errors on compiling since those versions have a
 * built-in printf function; pass `-fno-builtin-printf` flag to GCC to fix the
 * compiling.
 */
int printf(const char* format, ...);
/*
 * This function uses `ckb_debug` syscall to output formatted messages.
 *
 * Pass `-D CKB_C_STDLIB_PRINTF` flag to GCC to enable ckb_printf;
 * If the flag is undefined the ckb_printf will be compiled as an empty
 * function.
 */
int ckb_printf(const char* format, ...);
int ckb_debug(const char* s);

#endif /* CKB_C_STDLIB_STDIO_H_ */
