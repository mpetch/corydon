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
// \brief Tiny debugf, sdebugf and sndebugf implementation, optimized for speed
// on
//        embedded systems with a very limited resources.
//        Use this instead of bloated standard/newlib debugf.
//        These routines are thread safe and reentrant.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _DEBUGF_H_
#define _DEBUGF_H_

#include <stdarg.h>
#include <stddef.h>

#include "dri/serial.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Output a character to a custom device like UART, used by the debugf()
 * function This function is declared here only. You have to write your custom
 * implementation somewhere
 * \param character Character to output
 */
void _debugputchar(char character);

/**
 * Tiny debugf implementation
 * You have to implement _debugputchar if you use debugf()
 * To avoid conflicts with the regular debugf() API it is overridden by macro
 * defines and internal underscore-appended functions like debugf_() are used
 * \param format A string that specifies the format of the output
 * \return The number of characters that are written into the array, not
 * counting the terminating null character
 */
#define debugf debugf_
int debugf_(const char* format, ...);

/**
 * Tiny sdebugf implementation
 * Due to security reasons (buffer overflow) YOU SHOULD CONSIDER USING
 * (V)SNDEBUGF INSTEAD!
 * \param buffer A pointer to the buffer where to store the formatted string.
 * MUST be big enough to store the output!
 * \param format A string that specifies the format of the output
 * \return The number of characters that are WRITTEN into the buffer, not
 * counting the terminating null character
 */
#define sdebugf sdebugf_
int sdebugf_(char* buffer, const char* format, ...);

/**
 * Tiny sndebugf/vsndebugf implementation
 * \param buffer A pointer to the buffer where to store the formatted string
 * \param count The maximum number of characters to store in the buffer,
 * including a terminating null character
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that COULD have been written into the
 * buffer, not counting the terminating null character. A value equal or larger
 * than count indicates truncation. Only when the returned value is non-negative
 * and less than count, the string has been completely written.
 */
#define sndebugf sndebugf_
#define vsndebugf vsndebugf_
int sndebugf_(char* buffer, size_t count, const char* format, ...);
int vsndebugf_(char* buffer, size_t count, const char* format, va_list va);

/**
 * Tiny vdebugf implementation
 * \param format A string that specifies the format of the output
 * \param va A value identifying a variable arguments list
 * \return The number of characters that are WRITTEN into the buffer, not
 * counting the terminating null character
 */
#define vdebugf vdebugf_
int vdebugf_(const char* format, va_list va);

/**
 * debugf with output function
 * You may use this as dynamic alternative to debugf() with its fixed
 * _debugputchar() output
 * \param out An output function which takes one character and an argument
 * pointer
 * \param arg An argument pointer for user data passed to output function
 * \param format A string that specifies the format of the output
 * \return The number of characters that are sent to the output function, not
 * counting the terminating null character
 */
int fctdebugf(
    void (*out)(char character, void* arg), void* arg, const char* format, ...
);

#ifdef __cplusplus
}
#endif

#endif  // _DEBUGF_H_
