void memcpy(register char *dest, register char *src, register int count) {
	for (int i=0; i<count; i++) *(dest+i) = *(src+i);
}

int strlen(register char *s) {
	int i;
	for (i=0; s[i]; i++);
	return i;
}