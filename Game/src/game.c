#include "game.h"

void game_init(Game *game) {
	glfwInit();

	game->width=800;
	game->height=600;
	game->title="Game";
	game->is_running=true;
	game->state=PLAY;
	game->player_state=LIGHT_ON;

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

	game->renderer=(Simple_Renderer2D *)calloc(1, sizeof(Simple_Renderer2D));
	
	shader_init(game->shader, "res/shaders/game.vert", "res/shaders/game.frag");

	simple_renderer2d_init(game->renderer);

	shader_enable(game->shader);
	shader_set_uniform_mat4f(game->shader, "projection_matrix", ortho);
	shader_disable();

	renderable_init(&game->bg_sprite, (vec3){0, 0, 0}, (vec2){game->width, game->height}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/floor.png");
	renderable_init(&game->player, game->mouse_position, (vec2){40, 40}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/player.png");
}

void game_handle_inputs(Game *game) {
	if(glfwGetKey(game->window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
		if(game->state==MENU){
			glfwSetWindowShouldClose(game->window, true);
		}
		else if(game->state==PLAY) {
			game->state=PAUSE;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_ENTER)==GLFW_PRESS) {
		if(game->state==MENU){
			game->state=PLAY;
		}
		else if(game->state==PAUSE) {
			game->state=PLAY;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_F)==GLFW_PRESS) {
		game->player_state=LIGHT_ON;
	}

	if(glfwGetKey(game->window, GLFW_KEY_G)==GLFW_PRESS) {
		game->player_state=LIGHT_OFF;
	}

	glfwPollEvents();
}

void game_update(Game *game, float dt) {
	if(glfwWindowShouldClose(game->window)) {
		game->is_running=false;
	}

	if(game->state==PLAY) {
		glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		game->player.position[0]=game->mouse_position[0];
		game->player.position[1]=game->mouse_position[1];
	}
	else {
		glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

}

void game_render(Game *game) {
	glClear(GL_COLOR_BUFFER_BIT);

	float x=game->player.position[0]+game->player.size[0]/2;
	float y=game->player.position[1]+game->player.size[1]/2;

	shader_enable(game->shader);
	
	//to correct light position when window is stretched x*initial_width/current_width, y*initial_hieght/current_height
	shader_set_uniform2f(game->shader,"light_position", (vec2){x*800/game->width, y*600/game->height});
	shader_set_uniform1i(game->shader, "tex", 0);
	shader_set_uniform1i(game->shader, "lighting_type", game->player_state);

	shader_disable();

	simple_renderer2d_submit(game->renderer, &game->bg_sprite);
	simple_renderer2d_submit(game->renderer, &game->player);

	simple_renderer2d_flush(game->renderer);

	glfwSwapBuffers(game->window);
}

void game_deinit(Game *game) {

	renderable_deinit(&game->bg_sprite);
	renderable_deinit(&game->player);
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
	game_ptr->mouse_position[2]=0.0f;

}