#ifndef BUS_H
#define BUS_H

#include "cpu6502.h"
#include <stdint.h>

typedef struct bus{
    cpu6502_t *cpu;
    uint8_t *ram;
} bus_t;

bus_t* initialize_bus();
void destroy_bus(bus_t* bus);
void write_ram(bus_t* bus, uint16_t address, uint8_t data);
uint8_t read_ram(bus_t* bus, uint16_t address, int bReadOnly);
void write(cpu6502_t* cpu, uint16_t address, uint8_t data);
uint8_t read(cpu6502_t* cpu, uint16_t address);

#endif//BUS_H
