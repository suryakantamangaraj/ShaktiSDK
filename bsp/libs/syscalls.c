/*
Copyright (c) 2013, The Regents of the University of California (Regents).
All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the name of the Regents nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING
OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF REGENTS HAS
BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE. THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED
HEREUNDER IS PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.


modified for shakti

*/

#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include "utils.h"
#include <encoding.h>
#include "qspi.h"
#define SYS_write 64

#undef strcmp


/** @fn  printnum
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
static inline void printnum(void (*putch)(int, void**), void **putdat,
		unsigned long long num, unsigned base, int width, int padc)
{
	unsigned digs[sizeof(num)*CHAR_BIT];
	int pos = 0;

	while (1) {
		digs[pos++] = num % base;
		if (num < base)
			break;
		num /= base;
	}

	while (width-- > pos)
		putch(padc, putdat);

	while (pos-- > 0)
		putch(digs[pos] + (digs[pos] >= 10 ? 'a' - 10 : '0'), putdat);
}

/** @fn  getuint
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
static unsigned long long getuint(va_list *ap, int lflag)
{
	if (lflag >= 2)
		return va_arg(*ap, unsigned long long);
	else if (lflag)
		return va_arg(*ap, unsigned long);
	else
		return va_arg(*ap, unsigned int);
}

/** @fn  
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
static long long getint(va_list *ap, int lflag)
{
	if (lflag >= 2)
		return va_arg(*ap, long long);
	else if (lflag)
		return va_arg(*ap, long);
	else
		return va_arg(*ap, int);
}

/** @fn vprintfmt 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
 void vprintfmt(void (*putch)(int, void**), void **putdat, const char *fmt, va_list ap)
{
	register const char* p;
	const char* last_fmt;
	register int ch, err;
	unsigned long long num;
	int base, lflag, width, precision, altflag, i;
	float float_num = 0;
	char float_arr[30] = {'\0'};
	char padc;

	while (1) {
		while ((ch = *(unsigned char *) fmt) != '%') {
			if (ch == '\0')
				return;
			fmt++;
			putch(ch, putdat);
		}
		
		fmt++;

		// Process a %-escape sequence
		last_fmt = fmt;
		padc = ' ';
		width = -1;
		precision = -1;
		lflag = 0;
		altflag = 0;
reswitch:
		switch (ch = *(unsigned char *) fmt++) {

			// flag to pad on the right
			case '-':
				padc = '-';
				goto reswitch;

				// flag to pad with 0's instead of spaces
			case '0':
				padc = '0';
				goto reswitch;

				// width field
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				for (precision = 0; ; ++fmt) {
					precision = precision * 10 + ch - '0';
					ch = *fmt;
					if (ch < '0' || ch > '9')
						break;
				}
				goto process_precision;

			case '*':
				precision = va_arg(ap, int);
				goto process_precision;

			case '.':
				if (width < 0)
					width = 0;
				goto reswitch;

			case '#':
				altflag = 1;
				goto reswitch;

process_precision:
				if (width < 0)
					width = precision, precision = -1;
				goto reswitch;

				// long flag (doubled for long long)
			case 'l':
				lflag++;
				goto reswitch;

				// character
			case 'c':
				putch(va_arg(ap, int), putdat);
				break;

				// string
			case 's':
				if ((p = va_arg(ap, char *)) == NULL)
					p = "(null)";
				if (width > 0 && padc != '-')
					for (width -= strnlen(p, precision); width > 0; width--)
						putch(padc, putdat);
				for (; (ch = *p) != '\0' && (precision < 0 || --precision >= 0); width--) {
					putch(ch, putdat);
					p++;
				}
				for (; width > 0; width--)
					putch(' ', putdat);
				break;

				// (signed) decimal
			case 'd':
				num = getint(&ap, lflag);
				if ((long long) num < 0) {
					putch('-', putdat);
					num = -(long long) num;
				}
				base = 10;
				goto signed_number;

			case 'f':

				float_num =  va_arg(ap, double);

				ftoa(float_num, float_arr, 6); 

				for( i = 0; float_arr[i] != '\0'; i++)
				{
					putch(float_arr[i], putdat);
					if(i > 29) break;
				}
				break;

				// unsigned decimal
			case 'u':
				base = 10;
				goto unsigned_number;

				// (unsigned) octal
			case 'o':
				// should do something with padding so it's always 3 octits
				base = 8;
				goto unsigned_number;

			case 'x':
				base = 16;
unsigned_number:
				num = getuint(&ap, lflag);
signed_number:
				printnum(putch, putdat, num, base, width, padc);
				break;

				// escaped '%' character
			case '%':
				putch(ch, putdat);
				break;

				// unrecognized escape sequence - just print it literally
			default:
				putch('%', putdat);
				fmt = last_fmt;
				break;
		}
	}
}

/** @fn printf 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
int printf(const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	vprintfmt((void*)putchar, 0, fmt, ap);

	va_end(ap);
	return 0; // incorrect return value, but who cares, anyway?
}

/** @fn size_t strnlen 
 * @brief 
 * @details 
 * @warning 
 * @param[in] 
 * @param[Out] 
 */
size_t strnlen(const char *s, size_t n)
{
	const char *p = s;
	while (n-- && *p)
		p++;
	return p - s;
}

