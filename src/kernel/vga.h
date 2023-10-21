#include <stdint.h>

#define VGA_SCREEN_WIDTH 80
#define VGA_SCREEN_WIDTH 25

typedef uint8_t Color;

void vga_setc(char c, int x, int y, Color fg, Color bg);