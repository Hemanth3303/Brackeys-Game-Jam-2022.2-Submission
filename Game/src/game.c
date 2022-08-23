#include "game.h"

void game_init(Game *game) {
	glfwInit();

	game->width=800;
	game->height=600;
	game->title="Game";
	game->is_running=true;

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

	mat4 ortho;
	//x->0 to width left to right
	//y->0 to height from top to bottom
	glm_ortho(0.0f, game->width, game->height, 0.0f, -1.0f, 1.0f, ortho);

	game->shader=(Shader *)calloc(1, sizeof(Shader));
	game->renderer=(Simple_Renderer2D *)calloc(1, sizeof(Simple_Renderer2D));
	
	shader_init(game->shader, "res/shaders/basic.vert", "res/shaders/basic.frag");
	simple_renderer2d_init(game->renderer);

	shader_enable(game->shader);
	shader_set_uniform_mat4f(game->shader, "projection_matrix", ortho);

	renderable_init(&(game->sprite1), (vec3){game->width/2, game->height/2, 0}, (vec2){150, 100}, (vec4){1, 0, 0, 1}, game->shader, "res/sprites/dirt.png");

	renderable_init(&(game->sprite2), (vec3){100, 120, 0}, (vec2){180, 300}, (vec4){0, 0, 1, 1}, game->shader, "res/sprites/block.png");
}

void game_handle_inputs(Game *game) {
	if(glfwGetKey(game->window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
		glfwSetWindowShouldClose(game->window, true);
	}
	glfwPollEvents();
}

void game_update(Game *game) {
	if(glfwWindowShouldClose(game->window)) {
		game->is_running=false;
	}
	game->sprite1.position[0]+=0.01;
}

void game_render(Game *game) {
	glClear(GL_COLOR_BUFFER_BIT);

	float x=game->mouse_position[0];
	float y=game->mouse_position[1];

	shader_set_uniform2f(game->shader,"light_position", (vec2){x, y});
	shader_set_uniform1i(game->shader, "tex", 0);
	simple_renderer2d_submit(game->renderer, &(game->sprite1));
	simple_renderer2d_submit(game->renderer, &(game->sprite2));
	simple_renderer2d_flush(game->renderer);

	glfwSwapBuffers(game->window);
}

void game_deinit(Game *game) {

	renderable_deinit(&(game->sprite1));
	renderable_deinit(&(game->sprite2));
	simple_renderer2d_deinit(game->renderer);

	free((void *)game->shader);
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