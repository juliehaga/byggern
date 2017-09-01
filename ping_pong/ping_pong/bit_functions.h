/*
 * bit_functions.h
 *
 * Created: 01.09.2017 09:40:29
 *  Author: julihag
 */ 


#ifndef BIT_FUNCTIONS_H_
#define BIT_FUNCTIONS_H_

#define set_bit(reg, pin)\
(reg |= (1<< (pin)))

#define clr_bit(reg, pin)\
(reg &= ~(1<< (pin)))

#define test_bit(reg, pin)\
(reg & (1<< (pin))



#endif /* BIT_FUNCTIONS_H_ */