#include "../include/bus.h"
#include "../include/config.h"
#include "../include/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(int argc, char** argv) {
    int running;
    Bus bus;
    GLFWwindow* window = NULL;
    initialize_bus(&bus);
    initialize_window(&window, WIDTH, HEIGHT, &running);


    while(running){
        update(window, &running);
        process_input(window, &running);
    }

    printf("HOLA");

    glfwTerminate();

    return 0;
}
