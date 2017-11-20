/*
 * game.h
 *
 * Created: 18.11.2017 01:21:42
 *  Author: johanndk
 */ 


#ifndef GAME_H_
#define GAME_H_

typedef enum {IDLE, USB, PS2} states;
typedef enum{EASY, MEDIUM, HARD}difficulty;

#define END_GAME_ID 1
#define INIT_ID 2
#define PLAY_ID 3
#define ERROR_ID 4

void update_reference_values(void);
void update_input(void);
void set_USB_mode(difficulty mode);
void USB_play_game();
void end_game(void);
void set_PS2_mode(difficulty mode);
void PS2_update_input(void);
void PS2_play_game();

#endif /* GAME_H_ */