/*
 * joystick.h
 *
 * Created: 04.10.2017 16:22:13
 *  Author: andrholt
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_


/*
//ifølge hardware
#define CHANNEL_Y 4	
#define CHANNEL_X 5		
#define SLIDER_L 6
#define SLIDER_R 7
*/


#define CHANNEL_X 4
#define CHANNEL_Y 5
#define SLIDER_L 7
#define SLIDER_R 6

typedef enum{UP, DOWN, RIGHT, LEFT, CENTER} joystick_dir;

int joystick_read(int channel);
int slider_read(int channel);
int buttons_read(int button);
void send_slider_pos(void);

joystick_dir find_joystick_dir(void); 







#endif /* JOYSTICK_H_ */