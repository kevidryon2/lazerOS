#include <stdbool.h>
#include "vga.h"
#include "memory.h"
#include "io.h"

char *string_table[] = {
	"Kernel loaded.\nWait... where is the cursor!?",
	"Kernel loaded\n",
};

void start() {
	//we are now in 32-bit protected mode!
	//anyway, at the start of the 4th sector there is the kernel.
	//initially, no more than 20 (16 belonging to the kernel) sectors are loaded.
	//the kernel is at the start of the fourth sector, and is loaded at 0x8400
	
	vga_clearscreen(0);
	
	vga_activate_cursor();
	
	vga_puts(string_table[0], 15, 0);

	while (true) {
		
	}
}