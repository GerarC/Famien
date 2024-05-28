#ifndef BUS_H
#define BUS_H

#include "types.h"
#define MAX_MEM 1024 * 64

#include "cpu6502.h"

/*
 * Represents a Bus, here is connected all the stuff that need to interact
 * since cpu and ram to the sound and input systems
 *
 */
typedef struct bus_t{
    Cpu6502 cpu;
    Byte ram[MAX_MEM];
} Bus;

/*
 * Sets all the data of the given ram in 0
 * */
void initialize_ram(Byte ram[MAX_MEM]);

/*
 * Initialize all the things inside the bus
 */
void initialize_bus(Bus* bus);

/*
 * Writes data in the given ram address of the bus
 *
 */
void write_ram(Bus* bus, Word address, Byte data);

/*
 * Reads data in the given ram address of the bus
 */
Byte read_ram(Bus* bus, Word address);

#endif//BUS_H
