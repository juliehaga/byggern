/*
 * game.h
 *
 * Created: 14.11.2017 09:38:55
 *  Author: julihag
 */ 


#ifndef GAME_H_
#define GAME_H_

#define USB 1
#define PS2 2
#define EASY 0
#define MEDIUM 1
#define HARD 2

#define END_GAME_ID 1
#define INIT_ID 2
#define PLAY_ID 3
#define ERROR_ID 4


typedef enum {IDLE, PLAY, HIGHSCORE, RESET_HIGHSCORE, NEW_HIGHSCORE} states;

void play_game(void);



#endif /* GAME_H_ */