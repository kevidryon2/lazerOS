#include "memory.h"

void memcpy(char *dest, char *src, int count) {
	for (int i=0; i<count; i++) *(dest+i) = *(src+i);
}

void memmove(char *dest, char *src, int count) {
	if (dest > src) {
		for (int i=count-1; i>=0; i--) *(dest+i) = *(src+i);
	} else if (src > dest) {
		for (int i=0; i<count; i++)	*(dest+i) = *(src+i);
	}
}

void memset(char *p, int n, char c) {
	for (int i=0; i<n; i++) p[i] = c;
}

int strlen(register char *s) {
	int i;
	for (i=0; s[i]; i++);
	return i;
}

void reverse(char *s, char *d, int n) {
	for (int i=0; i<n; i++) {
		d[n-i-1] = s[i];
	}
}

void reversestr(char *s) {
	int start = 0;
	int end = strlen(s)-1;
	while (start < end) {
		char temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}

bool contains_l(uint32_t n, uint32_t *a, int l) {
	for (int i=0; i<l; i++) {
		if (a[i] == n) return true;
	}
	return false;
}

bool contains_w(uint16_t n, uint16_t *a, int l) {
	for (int i=0; i<l; i++) {
		if (a[i] == n) return true;
	}
	return false;
}

bool contains_b(uint8_t n, uint8_t *a, int l) {
	for (int i=0; i<l; i++) {
		if (a[i] == n) return true;
	}
	return false;
}