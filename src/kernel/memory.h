#include <stdint.h>
#include <stdbool.h>

void memcpy(char *dest, char *src, int count);
void memset(char *p, int n, char c);
void reverse(char *s, char *d, int n);
void reversestr(char *s);
void memmove(char *dest, char *src, int count);
int strlen(register char *s);
bool contains_l(uint32_t n, uint32_t *a, int l);
bool contains_w(uint16_t n, uint16_t *a, int l);
bool contains_b(uint8_t n, uint8_t *a, int l);

#define INDEX(p, i) ((void*)(p)+i)

//Memory regions

#define VGA_SCREEN ((char*)0xb8000)
#define MEMORY_SEGS_COUNT (*((uint16_t*)0xe820))
#define MEMORY_MAP ((MemorySegment*)0xe822)

typedef struct {
	uint64_t reg_address;
	uint64_t reg_length;
	uint32_t reg_type;
} MemorySegment;