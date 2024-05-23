#include <stdio.h>
#include <stdint.h>
#include "../include/bus.h"

int main(int argc, char** argv){
    bus_t* bus = initialize_bus();
    
    cpu6502_t *cpu = bus->cpu;

    cpu->a = 0x7F;
    cpu->x = 0x0F;
    cpu->y = 0x40;
    printf("This are the basic parameters of the cpu:");
    printf("\n\t- A Register: 0x%x", cpu->a);
    printf("\n\t- X Register: 0x%x", cpu->x);
    printf("\n\t- Y Register: 0x%x", cpu->y);
    printf("\n\t- fetched: 0x%x", cpu->fetched);
    printf("\n\t- temp: 0x%x", cpu->temp);
    printf("\n\t- absolute address: 0x%x", cpu->address_absolute);
    printf("\n\t- relative address: 0x%x", cpu->address_relative);
    printf("\n\t- flag status: ");
    for(int i = 7; i >= 0; i--) printf("%i", ((cpu->status << i) & 0x80)>>7);
    bus->ram[0] = 0x7F;
    bus->ram[1] = 0x41;
    bus->ram[0x0F] = 0x54;
    bus->ram[0x23] = 0x3B;
    bus->ram[0x24] = 0x7C;
    bus->ram[0x0F + 1] = 0x55;
    bus->ram[0x40] = 0x45;
    bus->ram[0x4114] = 0xFF;
    bus->ram[0x40 + 1] = 0x46;
    bus->ram[0x14] = 0xDB;
    bus->ram[0x15] = 0xFA;
    REL(cpu);
    ADC(cpu);
    printf("\nThis are the basic parameters of the cpu:");
    printf("\n\t- A Register: 0x%x", cpu->a);
    printf("\n\t- X Register: 0x%x", cpu->x);
    printf("\n\t- Y Register: 0x%x", cpu->y);
    printf("\n\t- fetched: 0x%x", cpu->fetched);
    printf("\n\t- temp: 0x%x", cpu->temp);
    printf("\n\t- absolute address: 0x%x", cpu->address_absolute);
    printf("\n\t- relative address: 0x%x", cpu->address_relative);
    printf("\n\t- flag status: ");
    for(int i = 7; i >= 0; i--) printf("%i", ((cpu->status << i) & 0x80)>>7);

    printf("\n\nram: 0x%x\n", bus->ram[0]);


    destroy_bus(bus);
    return 0;
}
