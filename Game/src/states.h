#pragma once

typedef enum States {
	MENU=0,
	PLAY,
	PAUSE,
	CONFIRM_QUIT,
	WIN,
	LOOSE,
}States;

typedef enum Player_States {
	OUT=0,
	NORMAL,
	SEARCH,
}Player_States;