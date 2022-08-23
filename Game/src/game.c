#include "game.h"

void game_init(Game *game) {
	glfwInit();

	game->width=800;
	game->height=600;
	game->title="Game";
	game->is_running=true;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	game->window=glfwCreateWindow(game->width, game->height, game->title, NULL, NULL);

	if(!game->window) {
		printf("Failed to create window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(game->window);
	glfwSetFramebufferSizeCallback(game->window, framebuffer_size_callback);
	glfwSetCursorPosCallback(game->window, cursor_position_callback);
	glfwSetWindowUserPointer(game->window, (void*)game);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad\n");
		glfwTerminate();
		return;
	}

	glViewport(0, 0, game->width, game->height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	// glEnable(GL_BLEND);

	mat4 ortho;
	//x->0 to width left to right
	//y->0 to height from top to bottom
	glm_ortho(0.0f, game->width, game->height, 0.0f, -1.0f, 1.0f, ortho);

	game->shader=(Shader *)calloc(1, sizeof(Shader));
	game->campfire_sprite.shader=(Shader *)calloc(1, sizeof(Shader));

	game->renderer=(Simple_Renderer2D *)calloc(1, sizeof(Simple_Renderer2D));
	
	shader_init(game->shader, "res/shaders/basic.vert", "res/shaders/basic.frag");
	shader_init(game->campfire_sprite.shader, "res/shaders/campfire.vert", "res/shaders/campfire.frag");

	simple_renderer2d_init(game->renderer);

	shader_enable(game->shader);
	shader_set_uniform_mat4f(game->shader, "projection_matrix", ortho);
	shader_disable();

	shader_enable(game->campfire_sprite.shader);
	shader_set_uniform_mat4f(game->campfire_sprite.shader, "projection_matrix", ortho);
	shader_disable();

	renderable_init(&game->bg_sprite, (vec3){0, 0, 0}, (vec2){game->width, game->height}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/floor.png");
	renderable_init(&game->campfire_sprite, (vec3){game->width/2-64/2, game->height/1.6, 0}, (vec2){64, 72}, (vec4){0, 0, 0, 1}, NULL, "res/sprites/fire.png");

}

void game_handle_inputs(Game *game) {
	if(glfwGetKey(game->window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
		glfwSetWindowShouldClose(game->window, true);
	}
	glfwPollEvents();
}

void game_update(Game *game, float dt) {
	if(glfwWindowShouldClose(game->window)) {
		game->is_running=false;
	}
}

void game_render(Game *game) {
	glClear(GL_COLOR_BUFFER_BIT);

	float x=game->mouse_position[0];
	float y=game->mouse_position[1];

	shader_enable(game->shader);
	//to correct light position when window is stretched x*initial_width/current_width, y*initial_hieght/current_height
	shader_set_uniform2f(game->shader,"light_position", (vec2){x*800/game->width, y*600/game->height});
	shader_set_uniform1i(game->shader, "tex", 0);
	shader_disable();

	shader_enable(game->campfire_sprite.shader);
	//game->width/2-64/2, game->height/1.6
	shader_set_uniform2f(game->campfire_sprite.shader,"c_light_position", (vec2){x*800/game->width, y*600/game->height});
	shader_set_uniform1i(game->campfire_sprite.shader, "c_tex", 0);
	shader_disable();

	// simple_renderer2d_submit(game->renderer, &game->bg_sprite);
	simple_renderer2d_submit(game->renderer, &game->campfire_sprite);

	simple_renderer2d_flush(game->renderer);

	glfwSwapBuffers(game->window);
}

void game_deinit(Game *game) {

	renderable_deinit(&game->bg_sprite);
	renderable_deinit(&game->campfire_sprite);
	simple_renderer2d_deinit(game->renderer);

	free((void *)game->shader);
	free((void *)game->campfire_sprite.shader);
	free((void *)game->renderer);

	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	Game *game_ptr=(Game *)glfwGetWindowUserPointer(window);
	game_ptr->width=width;
	game_ptr->height=height;
	glViewport(0, 0, game_ptr->width, game_ptr->height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Game *game_ptr=(Game *)glfwGetWindowUserPointer(window);
	game_ptr->mouse_position[0]=(float)xpos;
	game_ptr->mouse_position[1]=(float)ypos;
}