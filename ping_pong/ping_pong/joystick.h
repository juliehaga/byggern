/*
 * joystick.h
 *
 * Created: 04.10.2017 16:22:13
 *  Author: andrholt
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_

typedef enum{UP, DOWN, RIGHT, LEFT, CENTER} joystick_dir;

typedef enum {UP, DOWN, LEFT, RIGHT, CENTER} joystick_dir;

int joystick_read(int channel);
int slider_read(int channel);
int buttons_read(int button);
<<<<<<< HEAD
joystick_dir find_joystick_dir(void); 
=======
joystick_dir find_joystick_dir(void);


>>>>>>> d8fe2f8554f76637ee35c7a76ac53d0a72acce3e


#endif /* JOYSTICK_H_ */