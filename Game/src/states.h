#pragma once

typedef enum States {
	MENU=0,
	PLAY,
	PAUSE,
	CONFIRM_QUIT,
}States;

typedef enum Player_States {
	OUT=0,
	NORMAL,
	SEARCH,
}Player_States;