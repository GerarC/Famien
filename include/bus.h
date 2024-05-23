#ifndef BUS_H
#define BUS_H

#include "types.h"
#define MAX_MEM 1024 * 64

#include "cpu6502.h"

typedef struct bus_t{
    Cpu6502 cpu;
    Byte ram[MAX_MEM];
} Bus;

void initialize_ram(Byte ram[MAX_MEM]);
void initialize_bus(Bus* bus);
void write_ram(Bus* bus, Word address, Byte data);
Byte read_ram(Bus* bus, Word address);

#endif//BUS_H
