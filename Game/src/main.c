#include "game.h"

#include <stdlib.h>

/*
* REMEMBER: Theme is "Your're not Alone"
*/

int main(void) {

	Game *game;
	game=(Game *)calloc(1, sizeof(Game));

	game_init(game);
	while(game->is_running) {
		game_handle_inputs(game);
		game_update(game);
		game_render(game);
	}
	game_deinit(game);

	free((void *)game);

	return 0;
}