#include "io.h"

void outb(uint16_t port, uint8_t data) {
	__asm__(
		"pop edx\n"
		"pop eax\n"
		"out dx, eax\n"
	);
}