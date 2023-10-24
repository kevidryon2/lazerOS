#include <stdbool.h>
#include "vga.h"
#include "memory.h"
#include "io.h"
#include "printf.h"
#include "pci.h"

char *string_table[] = {
	"Lower Kernel Loaded.\n",
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
	
	MemorySegment current_seg;
	
	for (int i=0; i<MEMORY_SEGS_COUNT; i++) {
		current_seg = (MEMORY_MAP)[i];
		
		vga_puts(
					ram_segs_table[current_seg.reg_type].name,
					ram_segs_table[current_seg.reg_type].fg,
					ram_segs_table[current_seg.reg_type].bg
					);
		
		vga_printf(7, 0, "%8x", current_seg.reg_address);
		
		vga_putc('-', 7, 0);
		
		vga_printf(7, 0, "%8x", (uint32_t)current_seg.reg_address+(uint32_t)current_seg.reg_length);
		
		vga_printf(7, 0, "    %d B\n", (uint32_t)current_seg.reg_length);
	}
	
	vga_putc('\n', 12, 0);
	
	PCI_Address addr = {1, 0, 0, 0, 0};
	
	uint32_t vendors[8];
	uint32_t unique_vendors[8];
	
	//List PCI devices
	vga_puts(string_table[2], 7, 0);
	for (int i=0; i<8192; i++) {
		
		for (int i=0; i<8; i++) {
			vendors[i] = pci_check_vendor(addr.bus, addr.dev, i);
		}
		
		memset(unique_vendors, sizeof(unique_vendors), 0xff);
		
		int j=0;
		
		for (int i=0; i<8; i++) {
			if (!contains_l(vendors[i], unique_vendors, 8) && vendors[i] != -1) {
				unique_vendors[j] = vendors[i];
				j++;
			}
		}
		
		for (int i=0; i<8; i++) {
			if (unique_vendors[i] != 0xffffffff) vga_printf(15, 0, "\t%2x:%2x.%d: %8x\n", addr.bus, addr.dev, i, unique_vendors[i]);
		}
		
		if (addr.func == 0) {
			addr.dev++;
			if (addr.dev == 0) addr.bus++;
		}
	}
	
	vga_puts("\nOK", 13, 0);
	
	while (true) {
		
	}
}