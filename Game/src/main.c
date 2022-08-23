#include "game.h"

#include <stdlib.h>

/*
* REMEMBER: Theme is "Your're not Alone"
*/

int main(void) {

	Game *game;
	game=(Game *)calloc(1, sizeof(Game));

	float timer=0;
	unsigned int frames=0;
	game_init(game);
	while(game->is_running) {
		game_handle_inputs(game);
		game_update(game);
		game_render(game);
		frames++;
		if(glfwGetTime()-timer>1.0f) {
			timer+=1.0f;
			printf("%d fps\n", frames);
			frames=0;
		}
	}
	game_deinit(game);

	free((void *)game);

	return 0;
}