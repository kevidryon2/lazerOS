#include "io.h"

void outb( unsigned short port, unsigned char val )
{
   asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}

void outw( unsigned short port, unsigned short val )
{
   asm volatile("outw %0, %1" : : "a"(val), "Nd"(port) );
}

void outl( unsigned short port, unsigned long val )
{
   asm volatile("outl %0, %1" : : "a"(val), "Nd"(port) );
}

unsigned char inb(unsigned short int port) {
        unsigned char value;
        asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
        return value;
}

unsigned short inw(unsigned short int port) {
        unsigned short value;
        asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));
        return value;
}

unsigned long inl(unsigned short int port) {
        unsigned long value;
        asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));
        return value;
}