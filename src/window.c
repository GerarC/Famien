#include "../include/window.h"
#include <stdio.h>

void initialize_window(GLFWwindow** window, int width, int height, int* running){
    if(!glfwInit()){
        fprintf(stderr, "ERROR: initializing glfw");
        return ;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(width, height, "Famien", NULL, NULL);
    if(!*window){
        fprintf(stderr, "ERROR: creating glfw window");
        glfwTerminate();
        return ;
    }
    glfwMakeContextCurrent(*window);
    glewExperimental = 1;
    if(glewInit() != GLEW_OK){
        fprintf(stderr, "ERROR: initializing glew");
        return ;
    }
    glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
    *running = 1;
}


void update(GLFWwindow* window, int* running){
        glfwSwapBuffers(window);
        glfwPollEvents();
}

void process_input(GLFWwindow* window, int* running){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
            || glfwWindowShouldClose(window) != 0) *running = 0;
}
