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
uint16_t pci_get_vendor(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_device(uint8_t bus, uint8_t slot, uint8_t func);
uint16_t pci_get_class(uint8_t bus, uint8_t slot, uint8_t func);
bool pci_check_valid_device(PCI_Address addr);