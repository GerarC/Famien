#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initialize_window(GLFWwindow** window, int width, int height, int* running);
void update(GLFWwindow* window, int* running);
void process_input(GLFWwindow* window, int* running);

/* void process */


#endif//WINDOW_H
