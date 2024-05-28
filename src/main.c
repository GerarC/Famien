#include "../include/bus.h"
#include "../include/config.h"
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main(int argc, char** argv) {
    Bus bus;
    initialize_bus(&bus);
    GLFWwindow* window = NULL;
    if(!glfwInit()){
        fprintf(stderr, "ERROR: initializing glfw");
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Famie", NULL, NULL);
    if(!window){
        fprintf(stderr, "ERROR: creating glfw window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewExperimental = 1;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "ERROR: initializing glew");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    do {

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
            && glfwWindowShouldClose(window) == 0);

    printf("HOLA");

    glfwTerminate();

    return 0;
}
