#include "vga.h"
#include <stdarg.h>
#include <stdbool.h>

char *itoa(char *s, int n, int radix, bool uppercase) {
	int i = 0;
	int on = n;
	bool negative;
	
	char radix_symbols_upper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char radix_symbols_lower[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	
	while (n>0) {
		s[i] = (uppercase) ?
				(radix_symbols_upper[n%radix]) :
				(radix_symbols_lower[n%radix]);
				
		n = n / radix;
		i++;
	}
	
	s[i] = 0;
	
	//reverse the string
	
	reversestr(s);
	
	return s;
	
	/*if (radix != 10) {
	
		for (int i=0; i<ssize; i++) {
			vga_putc('0'+(s[i]>>4), 12, 0);
			vga_putc('0'+(s[i]&15), 12, 0);
			vga_putc(' ', 12, 0);
		}
		
		vga_puts(s, 0, 12);
		vga_putc(' ', 12, 0);
		vga_printf_decimal(strlen(s), 12, 0);
		vga_putc('\n', 12, 0);
		
		for (int i=0; i<ssize; i++) {
			vga_putc('0'+(buffer[i]>>4), 11, 0);
			vga_putc('0'+(buffer[i]&15), 11, 0);
			vga_putc(' ', 11, 0);
		}
		
		vga_puts(buffer, 0, 11);
		vga_putc('\n', 11, 0);
	
	}*/
}

void vga_printf_decimal(int n, Color fg, Color bg, int digits) {
	
	digits = digits ? digits : 1;
	
	char buffer[16];
	memset(buffer, 16, 0);
	itoa(buffer, n, 10, false);
	
	if (digits) {
		int padding = positive(digits-strlen(buffer));
		memmove(buffer+padding, buffer, strlen(buffer)+1);
		memset(buffer, padding, '0');
	}
	
	vga_puts(buffer, fg, bg);
}

void vga_printf_hex(int n, Color fg, Color bg, bool uppercase, int digits) {
	
	digits = digits ? digits : 1;
	
	char buffer[16];
	memset(buffer, 16, 0);
	itoa(buffer, n, 16, uppercase);
	
	if (digits) {
		int padding = positive(digits-strlen(buffer));
		memmove(buffer+padding, buffer, strlen(buffer)+1);
		memset(buffer, padding, '0');
	}
	
	vga_puts(buffer, fg, bg);
}

void vga_printf(Color fg, Color bg, char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	
	char c;
	int i = 0;
	
	while (fmt[i]) {
		c = fmt[i];
		switch (c) {
			case '%':
				i++;
				c = fmt[i];
				switch (c) {
					case '%':
						vga_putc('%', fg, bg);
						break;
					case 'd':
						vga_printf_decimal(va_arg(args, int), fg, bg, 1);
						break;
					case 'x':
						vga_printf_hex(va_arg(args, int), fg, bg, false, 1);
						break;
					case 'X':
						vga_printf_hex(va_arg(args, int), fg, bg, true, 1);
						break;
					case 's':
						vga_puts(va_arg(args, char*), fg, bg);
						break;
					case 'c':
						vga_putc(va_arg(args, int), fg, bg);
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':;
						int digits = c - '0';
						i++;
						c = fmt[i];
						switch (c) {
							case '%':
								vga_putc('%', fg, bg);
								break;
							case 'i':
							case 'd':
								vga_printf_decimal(va_arg(args, int), fg, bg, digits);
								break;
							case 'x':
								vga_printf_hex(va_arg(args, int), fg, bg, false, digits);
								break;
							case 'X':
								vga_printf_hex(va_arg(args, int), fg, bg, true, digits);
								break;
						}
						break;
				}
				break;
			default:
				vga_putc(fmt[i], fg, bg);
		}
		i++;
	}
	
	va_end(fmt);
}