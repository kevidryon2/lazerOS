#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
	unsigned enable : 1;
	unsigned reserved : 7;
	unsigned bus : 8;
	unsigned dev : 5;
	unsigned func : 3;
} PCI_Address;

uint16_t pci_read_word(uint8_t offset, PCI_Address addr);
uint16_t pci_get_vendor(PCI_Address addr);
bool pci_check_valid_device(PCI_Address addr);