#include "../include/bus.h"

void initialize_ram(Byte ram[MAX_MEM]){
    for (u32 i = 0; i < MAX_MEM; i++) ram[i] = 0x00;
}

void initialize_bus(Bus *bus){
    initialize_ram(bus->ram);
    initialize_cpu(&bus->cpu);
    connect_bus(&bus->cpu, bus);
    bus->cpu.read_ram = &read_ram;
    bus->cpu.write_ram = &write_ram;
    reset_cpu(&bus->cpu);
}

Byte read_ram(Bus *bus, Word address){
    return bus->ram[address];
}

void write_ram(Bus *bus, Word address, Byte data){
    bus->ram[address] = data;
}
