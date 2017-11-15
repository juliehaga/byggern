/*
 * fsm.h
 *
 * Created: 14.11.2017 09:38:55
 *  Author: julihag
 */ 


#ifndef FSM_H_
#define FSM_H_

typedef enum states{PLAY_GAME, HIGHSCORE, NEW_HIGHSCORE, IDLE} states;


void play_game(void);
int check_highscore(int score);


#endif /* FSM_H_ */