#include "game.h"

//yes all the game logic code is in one file, please don't judge me
//i am too tired from opengl-ing atm

void game_init(Game *game) {
	srand(time(NULL));
	
	glfwInit();

	game->width=800;
	game->height=600;
	game->title="Light-Robo";
	game->is_running=true;
	game->state=MENU;
	game->player_state=OUT;

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
	renderable_init(&game->enemy, (vec3){rand()%(game->width-64), rand()%(game->height-64)}, (vec2){64, 64}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/enemy.png");
	renderable_init(&game->win_pic, (vec3){game->width/2-512/2, game->height/2-128/2, 0}, (vec2){512, 128}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/win.png");
	renderable_init(&game->loose_pic, (vec3){game->width/2-512/2, game->height/2-128/2, 0}, (vec2){512, 128}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/loose.png");
	renderable_init(&game->menu, (vec3){game->width/2-512/2, game->height/2-512/2, 0}, (vec2){512, 512}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/menu.png");

	cc_array_new(&game->coins);

	for(int i=0; i<COIN_COUNT; i++) {
		float x=rand()%(game->width-64);
		float y=rand()%(game->height-64);
		Renderable2D *coin=(Renderable2D *)calloc(1, sizeof(Renderable2D));
		renderable_init(coin, (vec3){x, y, 0}, (vec2){64, 64}, (vec4){1, 1, 1, 1}, game->shader, "res/sprites/coin.png");
		cc_array_add(game->coins, (void *)coin);
	}

}

void game_handle_inputs(Game *game) {
	if(glfwGetKey(game->window, GLFW_KEY_ESCAPE)==GLFW_PRESS) {
		if(game->state==PAUSE){
			glfwSetWindowShouldClose(game->window, true);
		}
		else if(game->state==PLAY) {
			game->state=PAUSE;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_ENTER)==GLFW_PRESS) {
		if(game->state==PAUSE){
			game->state=PLAY;
		}
	}

	if(glfwGetKey(game->window, GLFW_KEY_SPACE)==GLFW_PRESS && game->state==MENU) {
		game->state=PLAY;
		game->player_state=NORMAL;
	}

	if(glfwGetKey(game->window, GLFW_KEY_F)==GLFW_PRESS && game->state==PLAY) {
		game->player_state=NORMAL;
	}

	if(glfwGetKey(game->window, GLFW_KEY_G)==GLFW_PRESS && game->state==PLAY) {
		game->player_state=SEARCH;
	}

	if(glfwGetKey(game->window, GLFW_KEY_R)==GLFW_PRESS && (game->state==LOOSE || game->state==WIN)) {
		game_deinit(game);
		game_init(game);
	}

	glfwPollEvents();
}

void game_update(Game *game, float dt) {
	if(glfwWindowShouldClose(game->window)) {
		game->is_running=false;
	}

	if(game->state==PLAY) {
		glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
		game->player.position[0]=(glm_lerp(game->player.position[0], game->mouse_position[0], 0.02));
		game->player.position[1]=(glm_lerp(game->player.position[1], game->mouse_position[1], 0.02));
	}
	else {
		glfwSetInputMode(game->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	if(game->state==PLAY) {
		game->enemy.position[0]=glm_lerp(game->enemy.position[0], game->player.position[0], 0.0003);
		game->enemy.position[1]=glm_lerp(game->enemy.position[1], game->player.position[1], 0.0003);
	}
	
	if(game->state==PLAY
	&& game->player.position[0]+game->player.size[0]-9>game->enemy.position[0]+16
	&& game->player.position[0]+9<game->enemy.position[0]+game->enemy.size[0]-16
	&& game->player.position[1]+game->player.size[1]-9>game->enemy.position[1]+16
	&& game->player.position[1]+9<game->enemy.position[1]+game->enemy.size[1]-16) {
		game->state=LOOSE;
	}

	if(game->player_state==NORMAL) {
		for(int i=0; i<COIN_COUNT; i++) {
			if(cc_array_size(game->coins)) {
				Renderable2D *coin;
				cc_array_get_at(game->coins, i, (void *)&coin);
				if(game->player.position[0]+game->player.size[0]-9>coin->position[0]+11 && game->player.position[0]+9<coin->position[0]+coin->size[0]-11 && game->player.position[1]-9+game->player.size[1]>coin->position[1]+11 && game->player.position[1]+9<coin->position[1]+coin->size[1]-7) {
					cc_array_remove_at(game->coins, i, (void *)coin);
					renderable_deinit(coin);
				}
			}
			else {
				game->state=WIN;
			}
		}
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
	int light_state=game->player_state-1;
	shader_set_uniform1i(game->shader, "lighting_type", light_state);

	shader_disable();

	simple_renderer2d_submit(game->renderer, &game->bg_sprite);

	if(game->player_state==NORMAL) {
		if(cc_array_size(game->coins)) {
			for(int i=0; i<COIN_COUNT; i++) {
				void *ptr;
				cc_array_get_at(game->coins, i, &ptr);
				simple_renderer2d_submit(game->renderer, (Renderable2D *)ptr);
			}
		}
	}

	if(game->player_state==SEARCH) {
		simple_renderer2d_submit(game->renderer, &game->enemy);
	}

	simple_renderer2d_submit(game->renderer, &game->player);

	if(game->state==WIN) {
		simple_renderer2d_submit(game->renderer, &game->win_pic);
		shader_enable(game->shader);
		shader_set_uniform2f(game->shader,"light_position", (vec2){game->width/2, game->height/2});
		shader_disable();
	}

	if(game->state==LOOSE) {
		simple_renderer2d_submit(game->renderer, &game->loose_pic);
		shader_enable(game->shader);
		shader_set_uniform2f(game->shader,"light_position", (vec2){game->width/2, game->height/2});
		shader_disable();
	}

	if(game->state==MENU) {
		simple_renderer2d_submit(game->renderer, &game->menu);
	}

	simple_renderer2d_flush(game->renderer);

	glfwSwapBuffers(game->window);
}

void game_deinit(Game *game) {

	renderable_deinit(&game->bg_sprite);
	renderable_deinit(&game->player);
	renderable_deinit(&game->enemy);
	renderable_deinit(&game->win_pic);
	renderable_deinit(&game->loose_pic);
	renderable_deinit(&game->menu);
	cc_array_destroy(game->coins);
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
