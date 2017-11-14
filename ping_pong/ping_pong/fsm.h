/*
 * fsm.h
 *
 * Created: 14.11.2017 15:01:52
 *  Author: julihag
 */ 


#ifndef FSM_H_
#define FSM_H_



typedef enum{PLAY_GAME, HIGHSCORE, NEW_HIGHSCORE, IDLE} states;
extern states current_state;


#endif /* FSM_H_ */