#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>

#include "idt.h"

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);
extern uint64_t push_registers();
void panic();

#endif