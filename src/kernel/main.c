#include <stdbool.h>
#include "vga.h"
#include "memory.h"
#include "io.h"

char *string_table[] = {
	"Kernel 1st half loaded.\n",
	"Memory map:\n",
};

void start() {
	//we are now in 32-bit protected mode!
	//anyway, at the start of the 4th sector there is the kernel.
	//initially, no more than 20 (16 belonging to the kernel) sectors are loaded.
	//the kernel is at the start of the fourth sector, and is loaded at 0x8400
	
	vga_clearscreen(7, 0);
	
	vga_activate_cursor();
	
	vga_puts(string_table[0], 7, 0);

	//Print memory map
	vga_puts(string_table[1], 7, 0);
	for (int i=0; i<3000; i++) {
		vga_printf(15, 0, "%2x", rand()%256);
	}

	while (true) {
		
	}
}