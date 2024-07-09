/*
Copyright (c) 2014-2018 Jorge Matricali

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

/**
 * Render progress bar like this:
 * |███░░░░░░░░░░░░░░░░░░░░░|  14.51%   [37] 192.168.100.37 root root
 *
 * @author Jorge Matricali <jorgematricali@gmail.com>
 * @param  count   Current iteration
 * @param  total   Total iterations
 * @param  suffix  String suffix
 * @param  bar_len Bar length
 */
void progressbar_render(size_t count, size_t total, char *suffix,
			size_t bar_len)
{
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w);

	size_t max_cols = w.ws_col;

	if (bar_len == 0)
		bar_len = max_cols - 80;
	if (suffix == NULL)
		suffix = "";

	size_t filled_len = bar_len * count / total;
	size_t empty_len = bar_len - filled_len;
	float percents = 100.0f * (float)(count / total);
	size_t fill = max_cols - bar_len - strlen(suffix) - 16;

	printf("\b%c[2K\r", 27);
	if (bar_len > 0) {
		printf("\033[37m|");
		if (filled_len > 0) {
			printf("\033[32m");
			for (size_t i = 0; i < filled_len; ++i) {
				printf("\u2588");
			}
		}
		if (empty_len > 0) {
			printf("\033[37m");
			for (size_t i = 0; i < empty_len; ++i) {
				printf("\u2591");
			}
		}
		printf("\033[37m|\033[0m");
	}
	if (max_cols > 60)
		printf("  %.2f%%   %s", percents, suffix);
	if (fill > 0) {
		for (size_t i = 0; i < fill; ++i) {
			printf(" ");
		}
	}
	printf("\r");
	fflush(stdout);
}
