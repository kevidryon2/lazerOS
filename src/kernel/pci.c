#include "io.h"
#include "pci.h"

uint16_t pci_read_word(uint8_t offset, PCI_Address addr) {
	
	//calculate address
	uint32_t address;
	memcpy(&address, &addr, 3); //sneaky little pointer trick... what could go wrong?
	address = address | offset;

	outl(0xCF8, address);
	
	return (inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff;
}

uint16_t pci_get_vendor(PCI_Address addr) {
	//vendor is the 1st word
	return pci_read_word(0, addr);
}

bool pci_check_valid_device(PCI_Address addr) {
	return pci_get_vendor(addr) != 0xffff;
	//invalid devices return all ones
}

/*

bitmasking test area

--------abcdefgh
--------------g-
-----------g----

*/