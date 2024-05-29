#include "../include/bus.h"
#include "../include/config.h"
#include "../include/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "../include/map.h"
#include "../include/utils.h"

int main(int argc, char** argv) {
    int running;
    Bus bus;
    GLFWwindow* window = NULL;
    printf("Bus instanced\n");
    printf("\n");
    const char* key;
    map_str_t map;
    map_init(&map);
    map_iter_t iter = map_iter(&map);

    initialize_bus(&bus);
    initialize_window(&window, WIDTH, HEIGHT, &running);

    printf("HOLA");

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

    reset_cpu(&bus.cpu);
    bus.cpu.a = 0x24;
    bus.cpu.x = 0x14;
    bus.cpu.y = 0xFF;

    printf("\n");
    disassembly(bus.cpu, &map, 0xF156, 0xF170);
    printf("\n");
    iter = map_iter(&map);
    while((key = map_next(&iter))){
        printf("%s\n", *map_get(&map, key));
    }

    while(running){
        update(window, &running);
        process_input(window, &running);
    }

    map_deinit(&map);
    glfwTerminate();
    return 0;
}
