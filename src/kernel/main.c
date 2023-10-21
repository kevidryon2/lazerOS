#include <stdbool.h>
#include "vga.h"
#include "memory.h"
#include "io.h"

char helloworld[] = "Hello, World!";

void start() {
	//we are now in 32-bit protected mode!
	//anyway, at the start of the 4th sector there is the kernel.
	//initially, no more than 20 (16 belonging to the kernel) sectors are loaded.
	//the kernel is at the start of the fourth sector, and is loaded at 0x8400

	for (int i=0; i<256; i++) {
		vga_setc(i, i, 0, i & 0x0f, (~i >> 4) & 0x0f);
	}

	while (true) {
		
	}
}