/*
 * joystick.h
 *
 * Created: 04.10.2017 16:22:13
 *  Author: andrholt
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_


int joystick_read(int channel);
int slider_read(int channel);
int buttons_read(int button);



#endif /* JOYSTICK_H_ */