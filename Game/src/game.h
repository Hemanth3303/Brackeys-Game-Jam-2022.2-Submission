#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct Game {
	GLFWwindow *window;
	int width, height;
	const char *title;
	bool is_running;
}Game;


void init(Game *game);
void handleInputs(Game *game);
void update(Game *game);
void render(Game *game);
void deinit(Game *game);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);