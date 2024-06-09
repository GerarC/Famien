#include "../include/window.h"
#include "../include/log.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void initialize_window(GLFWwindow **window, int width, int height) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: initializing glfw");
		return;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	*window = glfwCreateWindow(width, height, "Famien", NULL, NULL);
	if (!*window) {
        log_error("there's something wrong creating a glfw window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(*window);
	if (glewInit() != GLEW_OK) {
        log_error("there's is something wrong with glew initialization");
		return;
	}
	glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(*window, input_callback);
}

void update(GLFWwindow *window) {
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void input_callback(GLFWwindow *window, int key, int scancode, int action,
					int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			break;
		}
	}
}

void main_loop(GLFWwindow *window) {
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 9.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		update(window);
	}
}
