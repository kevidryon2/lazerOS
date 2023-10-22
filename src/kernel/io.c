#include "io.h"

void outb( unsigned short port, unsigned char val )
{
   asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

unsigned char inb(unsigned short int port) {
        unsigned char value;
        asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
        return value;
}