#include "io.h"

void outb(register uint16_t port, register uint8_t data) {
	__asm__(
        "mov edx, DWORD PTR [esp+4]\n"
        "\tmov eax, DWORD PTR [esp+8]\n"
        "\tout dx, al"
    );
}

uint8_t inb(register uint16_t p) {
    __asm__(
        "mov edx, DWORD PTR [esp+4]\n"
        "\tin al, dx"
    );
}