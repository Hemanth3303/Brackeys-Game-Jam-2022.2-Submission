#include "game.h"

#include <stdlib.h>

/*
* REMEMBER: Theme is "Your're not Alone"
*/

int main(void) {

	Game *game;
	game=(Game *)calloc(1, sizeof(Game));

	float prev=0, now=0;
	float dt=0;
	game_init(game);
	while(game->is_running) {
		game_handle_inputs(game);
		game_update(game, dt);
		game_render(game);

		dt=now-prev;
		prev=now;
		now=glfwGetTime();

		// printf("%f dt\n", dt);
	}
	game_deinit(game);

	free((void *)game);

	return 0;
}