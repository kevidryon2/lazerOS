void itoa(char *s, int ssize, int n, int radix, bool uppercase);
void vga_printf_decimal(int n, Color fg, Color bg, int digits);
void vga_printf_hex(int n, Color fg, Color bg, bool uppercase, int digits);
void vga_printf(Color fg, Color bg, char *fmt, ...);