#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cc_array.h"

#include "renderable2d.h"
#include "simple_renderer2d.h"
#include "shader.h"
#include "states.h"

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define COIN_COUNT 30

typedef struct Game {
	GLFWwindow *window;
	int width, height;
	const char *title;
	bool is_running;
	vec3 mouse_position;
	
	Shader *shader;
	Simple_Renderer2D *renderer;
	Renderable2D bg_sprite;
	Renderable2D player;
	Renderable2D enemy;
	Renderable2D win_pic;
	Renderable2D loose_pic;
	Renderable2D menu;
	CC_Array *coins;
	States state;
	Player_States player_state;
}Game;


void game_init(Game *game);
void game_handle_inputs(Game *game);
void game_update(Game *game, float dt);
void game_render(Game *game);
void game_deinit(Game *game);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);