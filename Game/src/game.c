#include "game.h"

void init(Game *game) {
	glfwInit();

	game->width=800;
	game->height=600;
	game->title="Game";
	game->is_running=true;

	game->window=glfwCreateWindow(game->width, game->height, game->title, NULL, NULL);

	if(!game->window) {
		printf("Failed to create window\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(game->window);
	glfwSetFramebufferSizeCallback(game->window, framebuffer_size_callback);
	glfwSetWindowUserPointer(game->window, (void*)game);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("Failed to initialize glad\n");
		glfwTerminate();
		return;
	}

	glViewport(0, 0, game->width, game->height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

}

void handleInputs(Game *game) {
	if(glfwGetKey(game->window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
		glfwSetWindowShouldClose(game->window, true);
	}
	glfwPollEvents();
}

void update(Game *game) {
	if(glfwWindowShouldClose(game->window)) {
		game->is_running=false;
	}
}

void render(Game *game) {
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(game->window);
}

void deinit(Game *game) {
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	Game *game_ptr=(Game*)glfwGetWindowUserPointer(window);
	game_ptr->width=width;
	game_ptr->height=height;
	glViewport(0, 0, game_ptr->width, game_ptr->height);
}