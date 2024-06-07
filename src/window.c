#include "../include/window.h"
#include "../include/text.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

void initialize_window(GLFWwindow **window, int width, int height) {
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: initializing glfw");
		return;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	*window = glfwCreateWindow(width, height, "Famien", NULL, NULL);
	if (!*window) {
		fprintf(stderr, "ERROR: creating glfw window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(*window);
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "ERROR: initializing glew");
		return;
	}
	glfwSetInputMode(*window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(*window, input_callback);
	glfwSwapInterval(1);

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, (GLdouble)width, 0.0, (GLdouble)height, 0.0, 1.0);
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
		glPointSize(10);
		glLineWidth(2.5);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(10.0, 10.0, 0.0);
		glVertex3f(200.0, 200.0, 0.0);
		glEnd();
		update(window);
	}
}
