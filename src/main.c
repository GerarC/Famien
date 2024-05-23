#include <stdio.h>
#include "../include/cpu6502.h"
#include "../include/bus.h"

int main(int argc, char** argv) {
    Bus bus;
    printf("Bus instanced\n");

    initialize_bus(&bus);

    for (u32 i = 0; i<10; i++) printf("Ram[%i]: %02X\n", i, bus.ram[i]);
    bus.ram[0xFFFC] = 0x56;
    bus.ram[0xFFFD] = 0xF1;
    bus.ram[0xF156] = 0x61;
    bus.ram[0xF158] = 0x65;
    bus.ram[0xF15A] = 0x01;
    bus.ram[0xF15C] = 0x06;
    bus.ram[0xF15E] = 0x08;
    bus.ram[0xF15F] = 0xBA;
    bus.ram[0xF160] = 0xFE;
    bus.ram[0xF163] = 0xB6;
    bus.ram[0x0000] = 0x56;
    bus.ram[0xF166] = 0xFE;
    reset_cpu(&bus.cpu);
    bus.cpu.a = 0x24;
    bus.cpu.x = 0x14;
    bus.cpu.y = 0xFF;
    execute_cpu(&bus.cpu);
    for (u32 i = 0xF154; i<0xF166; i++) printf("Ram[%i]: %02X\n", i, bus.ram[i]);

    return 0;
}
