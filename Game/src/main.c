#include "game.h"

#include <stdlib.h>

/*
* REMEMBER: Theme is "Your're not Alone"
*/

int main(void) {

	Game *game;
	game=(Game*)calloc(1, sizeof(Game));

	init(game);
	while(game->is_running) {
		handleInputs(game);
		update(game);
		render(game);
	}
	deinit(game);

	free((void*)game);

	return 0;
}