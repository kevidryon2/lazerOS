#include <stdint.h>

void memcpy(register char *dest, register char *src, register int count);
int strlen(register char *s);

#define INDEX(p, i) ((void*)(p)+i)

//Memory regions

#define VGA_SCREEN ((char*)0xb8000)
#define MEMORY_MAP ((int*)0xe822)
#define MEMORY_MAP ((MemorySegment*)0xe822)

typedef struct {
	uint64_t reg_address;
	uint64_t reg_length;
	uint32_t reg_type;
} MemorySegment;