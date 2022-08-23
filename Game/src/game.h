#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "renderable2d.h"
#include "simple_renderer2d.h"
#include "shader.h"

#include <stdbool.h>
#include <stdio.h>

typedef struct Game {
	GLFWwindow *window;
	int width, height;
	const char *title;
	bool is_running;
	Shader *shader;
	Simple_Renderer2D *renderer;
	Renderable2D bg_sprite;
	Renderable2D campfire_sprite;
	vec2 mouse_position;
}Game;


void game_init(Game *game);
void game_handle_inputs(Game *game);
void game_update(Game *game, float dt);
void game_render(Game *game);
void game_deinit(Game *game);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);