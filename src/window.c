#include "../include/window.h"
#include <GLFW/glfw3.h>
#include <stdio.h>

void initialize_window(GLFWwindow** window, int width, int height){
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
    glfwSetKeyCallback(*window, input_callback);
    glfwSwapInterval(1);
}

void update(GLFWwindow* window){
        glfwSwapBuffers(window);
        glfwPollEvents();
}

void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void main_loop(GLFWwindow* window){
    while(!glfwWindowShouldClose(window)){
        update(window);
    }
}
