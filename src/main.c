#include <stdio.h>
#include "../include/cpu6502.h"
#include "../include/bus.h"
#include "../include/map.h"
#include "../include/utils.h"

int main(int argc, char** argv) {
    Bus bus;
    printf("Bus instanced\n");
    printf("\n");
    const char* key;
    map_iter_t iter = map_iter(&map);
    map_str_t map;
    map_init(&map);

    initialize_bus(&bus);

    for (u32 i = 0; i<10; i++) printf("Ram[%i]: %02X\n", i, bus.ram[i]);
    bus.ram[0xFFFC] = 0x56;
    bus.ram[0xFFFD] = 0xF1;
    bus.ram[0xF156] = 0x61;
    bus.ram[0xF157] = 0x61;
    bus.ram[0xF158] = 0x65;
    bus.ram[0xF159] = 0x65;
    bus.ram[0xF15A] = 0x01;
    bus.ram[0xF15B] = 0x01;
    bus.ram[0xF15C] = 0x06;
    bus.ram[0xF15D] = 0x06;
    bus.ram[0xF15E] = 0x08;
    bus.ram[0xF15F] = 0xBA;
    bus.ram[0xF160] = 0xFE;
    bus.ram[0xF161] = 0x65;
    bus.ram[0xF162] = 0xF1;
    bus.ram[0xF163] = 0xB6;
    bus.ram[0xF164] = 0xB6;
    bus.ram[0xF165] = 0xB6;
    bus.ram[0xF166] = 0xFE;
    bus.ram[0xF160] = 0x61;
    bus.ram[0xF161] = 0x61;
    bus.ram[0xF162] = 0x65;
    bus.ram[0xF163] = 0x65;
    bus.ram[0xF164] = 0x01;
    bus.ram[0xF165] = 0x01;
    bus.ram[0xF166] = 0x06;
    bus.ram[0xF167] = 0x06;
    bus.ram[0xF168] = 0x08;
    bus.ram[0xF169] = 0xBA;
    bus.ram[0xF16A] = 0xFE;
    bus.ram[0xF16B] = 0x65;
    bus.ram[0xF16C] = 0xF1;
    bus.ram[0xF16D] = 0xB6;
    bus.ram[0xF16E] = 0xB6;
    bus.ram[0xF16F] = 0xB6;
    bus.ram[0xF170] = 0xFE;
    printf("\n");
    disassembly(bus.cpu, &map, 0xF156, 0xF166);
    iter = map_iter(&map);
    while((key = map_next(&map, &iter))){
        printf("%s\n", *map_get(&map, key));
    }
    printf("\n");

    reset_cpu(&bus.cpu);
    bus.cpu.a = 0x24;
    bus.cpu.x = 0x14;
    bus.cpu.y = 0xFF;
    execute_cpu(&bus.cpu);

    printf("\n");
    for (u32 i = 0xF154; i<0xF17F; i++) printf("Ram[%04X]: %02X\n", i, bus.ram[i]);
    execute_cpu(&bus.cpu);
    execute_cpu(&bus.cpu);

    printf("\n");
    disassembly(bus.cpu, &map, 0xF156, 0xF170);
    iter = map_iter(&map);
    while((key = map_next(&map, &iter))){
        printf("%s\n", *map_get(&map, key));
    }

    map_deinit(&map);
    return 0;
}
