#include <stdint.h>

#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_HEIGHT 25

typedef uint8_t Color;

void vga_setc(char c, int x, int y, Color fg, Color bg);
void vga_puts(char *s, Color fg, Color bg);
void vga_putc(char c, Color fg, Color bg);
void vga_update_cursor();
void vga_clearscreen(Color cursor, Color bg);
void vga_activate_cursor();