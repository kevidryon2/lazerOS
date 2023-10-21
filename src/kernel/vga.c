#include "vga.h"
#include "memory.h"

int cursor_x = 0;
int cursor_y = 0;

void vga_update_cursor() {
	int pos = cursor_y * VGA_SCREEN_WIDTH + cursor_x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void vga_setc(char c, int x, int y, Color fg, Color bg) {
	*(char*)INDEX(VGA_SCREEN, ((x+y*VGA_SCREEN_WIDTH)*2)) = c;
	*(char*)INDEX(VGA_SCREEN, ((x+y*VGA_SCREEN_WIDTH)*2+1)) = fg | (bg << 4);
}

void vga_putc(char c, Color fg, Color bg) {
	vga_setc(c, cursor_x, cursor_y, fg, bg);
	cursor_x++;
	if (cursor_x >= VGA_SCREEN_WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}
}

void vga_puts(char *s, Color fg, Color bg) {
	char c;
	for (int i=0; i<strlen(s); i++) {
		c = s[i];
		vga_putc(c, fg, bg);
	}
}