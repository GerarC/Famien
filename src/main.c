#include "../include/bus.h"
#include "../include/config.h"
#include "../include/log.h"
#include "../include/map.h"
#include "../include/utils.h"
#include "../include/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int argc, char **argv) {
	log_debug("Application starts");
	Bus bus;
	GLFWwindow *window = NULL;
	const char *key;
	map_str_t map;
	log_info("Needed variables instanced");

	map_init(&map);
	map_iter_t iter = map_iter(&map);

	initialize_bus(&bus);
	initialize_window(&window, WIDTH, HEIGHT);


	log_info("Setting data in ram to test\n");

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

	log_info("resetting CPU");
	reset_cpu(&bus.cpu);

	bus.cpu.a = 0x24;
	bus.cpu.x = 0x14;
	bus.cpu.y = 0xFF;

	disassembly(bus.cpu, &map, 0xF156, 0xF170);
	printf("\n");
	iter = map_iter(&map);
	while ((key = map_next(&iter))) {
		log_debug("\t%s", *map_get(&map, key));
	}

    log_warn("Custom logging lib has been created");

	main_loop(window);

	map_deinit(&map);
	glfwTerminate();
	return 0;
}
