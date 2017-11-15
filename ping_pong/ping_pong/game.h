/*
 * fsm.h
 *
 * Created: 14.11.2017 09:38:55
 *  Author: julihag
 */ 


#ifndef FSM_H_
#define FSM_H_

typedef enum {IDLE = 0, EASY = 1, MEDIUM = 2, HARD = 3, HIGHSCORE, NEW_HIGHSCORE} states;


void play_game(states state);



#endif /* FSM_H_ */