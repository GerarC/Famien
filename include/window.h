#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void initialize_window(GLFWwindow **window, int width, int height);
void update(GLFWwindow *window);
void input_callback(GLFWwindow *window, int key, int scancode, int action,
					int mods);
void main_loop(GLFWwindow *window);

/* void process */

#endif // WINDOW_H
