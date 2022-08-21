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


void game_init(Game *game);
void game_handle_inputs(Game *game);
void game_update(Game *game);
void game_render(Game *game);
void game_deinit(Game *game);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);