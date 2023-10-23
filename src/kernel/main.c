#include <stdbool.h>
#include "vga.h"
#include "memory.h"
#include "io.h"
#include "printf.h"
#include "pci.h"

char *string_table[] = {
	"Kernel 1st half loaded.\n",
	"Memory map:\n",
	"PCI Devices:\n"
};

struct {
	Color fg;
	Color bg;
	char *name;
} ram_segs_table[] = {
	{0xf,0x0,"End       "},
	{0xa,0x0,"RAM       "},
	{0xd,0x0,"Reserved  "},
	{0xe,0x0,"ACPI      "},
	{0xe,0x0,"ACPI NVS  "},
	{0xf,0xc,"Bad memory"},
};

void start() {
	//we are now in 32-bit protected mode!
	//anyway, at the start of the 4th sector there is the kernel.
	//initially, no more than 20 (16 belonging to the kernel) sectors are loaded.
	//the kernel is at the start of the fourth sector, and is loaded at 0x8400
	
	vga_clearscreen(7, 0);
	
	vga_activate_cursor();
	
	vga_puts(string_table[0], 7, 0);

	vga_putc('\n', 0, 0);

	//Print memory map
	vga_puts(string_table[1], 7, 0);
	
	for (int i=0; i<MEMORY_SEGS_COUNT; i++) {
		vga_puts(
					ram_segs_table[MEMORY_MAP[i].reg_type].name,
					ram_segs_table[MEMORY_MAP[i].reg_type].fg,
					ram_segs_table[MEMORY_MAP[i].reg_type].bg
					);
		
		vga_printf(7, 0, "%8x", MEMORY_MAP[i].reg_address);
		
		vga_putc('-', 7, 0);
		
		vga_printf(7, 0, "%8x", MEMORY_MAP[i].reg_address+MEMORY_MAP[i].reg_length);
		
		vga_printf(7, 0, "    %d B\n", MEMORY_MAP[i].reg_address);
		//vga_printf(7, 0, "    %x B\n", MEMORY_MAP[i].reg_length);
	}
	
	vga_putc('\n', 12, 0);
	
	PCI_Address addr = {1, 0, 0, 0, 0};
	
	//List PCI devices
	vga_puts(string_table[2], 7, 0);
	for (int i=0; i<16; i++) {
		if (true) {
			vga_printf(15, 0, "vendor %2x, %d %d device.\n", pci_get_vendor(addr), addr.bus, addr.dev);
		}
		
		addr.dev++;
		
		if (addr.dev == 0) addr.bus++;
	}
	
	while (true) {
		
	}
}