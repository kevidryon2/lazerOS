#include <stdint.h>

void memcpy(char *dest, char *src, int count);
void memset(char *p, int n, char c);
void reverse(char *s, char *d, int n);
void reversestr(char *s, char *d);
void memmove(char *dest, char *src, int count);
int strlen(register char *s);

#define INDEX(p, i) ((void*)(p)+i)

//Memory regions

#define VGA_SCREEN ((char*)0xb8000)
#define MEMORY_SEGS_COUNT (*((uint16_t*)0xe820))
#define MEMORY_MAP ((MemorySegment*)0xe822)

typedef struct {
	uint32_t reg_address_low;
	uint32_t reg_address_high;
	uint32_t reg_length_low;
	uint32_t reg_length_high;
	uint32_t reg_type;
} MemorySegment;