#include "../include/bus.h"
#include <stdint.h>
#include <stdlib.h>

bus_t* initialize_bus(){
    bus_t *bus = (bus_t*)malloc(sizeof(bus_t));
    bus->ram = malloc(sizeof(uint8_t)*(64*1024));
    bus->cpu = create_cpu();
    bus->cpu->write = &write;
    bus->cpu->read = &read;

    for(int i = 0; i < 64*1024; i++){
        bus->ram[i] = 0x00;
    }

    connect_bus(bus->cpu, bus);
    return bus;
}

void destroy_bus(bus_t *bus){
    destroy_cpu(bus->cpu);
    free(bus->ram);
    free(bus);
}

void write_ram(bus_t* bus, uint16_t address, uint8_t data){
    if(address >= 0x0000 && address <= 0xffff)
        bus->ram[address] = data;
}

uint8_t read_ram(bus_t* bus, uint16_t address, int bReadOnly){
    if(address >= 0x0000 && address <= 0xffff)
        return bus->ram[address];
    return 0x00;
}

void write(cpu6502_t *cpu, uint16_t address, uint8_t data){
    write_ram(cpu->bus, address, data);
}
uint8_t read(cpu6502_t *cpu, uint16_t address){
    return read_ram(cpu->bus, address, 0);
}
