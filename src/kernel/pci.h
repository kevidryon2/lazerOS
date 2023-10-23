#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed)) {
	unsigned enable : 1;
	unsigned reserved : 7;
	unsigned bus : 8;
	unsigned dev : 5;
	unsigned func : 3;
} PCI_Address;