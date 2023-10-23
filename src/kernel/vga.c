#include "vga.h"
#include "memory.h"
#include "io.h"

int cursor_x = 0;
int cursor_y = 0;

void vga_activate_cursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | 14);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | 15);
}

void vga_update_cursor() {

	if (cursor_y >= VGA_SCREEN_HEIGHT) {
		cursor_y--;
		memmove(VGA_SCREEN,
				VGA_SCREEN+VGA_SCREEN_WIDTH*2,
				VGA_SCREEN_WIDTH*VGA_SCREEN_HEIGHT*2-VGA_SCREEN_WIDTH*2
				);
		for (int i=0; i<VGA_SCREEN_WIDTH; i++) {
			vga_setc(0, i, VGA_SCREEN_HEIGHT-1, 7, 0);
		}
	}

	int pos = cursor_y * VGA_SCREEN_WIDTH + cursor_x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void vga_setc(char c, int x, int y, Color fg, Color bg) {
	*(char*)INDEX(VGA_SCREEN, ((x+y*VGA_SCREEN_WIDTH)*2)) = c;
	*(char*)INDEX(VGA_SCREEN, ((x+y*VGA_SCREEN_WIDTH)*2+1)) = fg | (bg << 4);
}

void vga_putc(char c, Color fg, Color bg) {
	switch (c) {
		case '\n':
			cursor_x=0;
			cursor_y++;
			vga_update_cursor();
			break;
		case '\t':
			cursor_x += 8;
			vga_update_cursor();
			break;
		default:
			vga_setc(c, cursor_x, cursor_y, fg, bg);
			cursor_x++;
			if (cursor_x >= VGA_SCREEN_WIDTH) {
				cursor_x = 0;
				cursor_y++;
			}
			vga_update_cursor();
			break;
	}
}

void vga_puts(char *s, Color fg, Color bg) {
	char c;
	for (int i=0; i<strlen(s); i++) {
		c = s[i];
		vga_putc(c, fg, bg);
	}
}

void vga_clearscreen(Color cursor, Color bg) {
	for (int x=0; x<VGA_SCREEN_WIDTH; x++) {
		for (int y=0; y<VGA_SCREEN_HEIGHT; y++) {
			vga_setc(0, x, y, cursor, bg);
		}
	}
}