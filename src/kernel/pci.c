#include "io.h"
#include "pci.h"

uint16_t pciconfig_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus;
    uint32_t lslot = (uint32_t)slot;
    uint32_t lfunc = (uint32_t)func;
    uint16_t tmp = 0;
 
    // Create configuration address as per Figure 1
    address = (uint32_t)((lbus << 16) | (lslot << 11) |
              (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
 
    // Write out the address
    outl(0xCF8, address);
    // Read in the data
    // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
    tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
    return tmp;
}

uint16_t pci_get_vendor(uint8_t bus, uint8_t slot, uint8_t func) {
    uint16_t vendor, device;
    /* Try and read the first configuration register. Since there are no
     * vendors that == 0xFFFF, it must be a non-existent device. */
    vendor = pciconfig_read_word(bus, slot, func, 0);
    return vendor;
}

uint16_t pci_get_device(uint8_t bus, uint8_t slot, uint8_t func) {
    uint16_t vendor, device;
    vendor = pciconfig_read_word(bus, slot, func, 2);
    return vendor;
}

uint16_t pci_get_class(uint8_t bus, uint8_t slot, uint8_t func) {
    uint16_t vendor, device;
    vendor = pciconfig_read_word(bus, slot, func, 10);
    return vendor;
}

/*

bitmasking test area

--------abcdefgh
--------------g-
-----------g----

*/