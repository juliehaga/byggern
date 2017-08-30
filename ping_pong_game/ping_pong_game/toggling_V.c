#include <avr/io.h>
#include <util/delay.h>


#define set_bit(reg, pin)\
(reg |= (1<< (pin)))

#define clr_bit(reg, pin)\
(reg &= ~(1<< (pin)))

#define test_bit(reg, pin)\
(reg & (1<< (pin))

int toggling(void)
{	

	
    while(1)
    {
		clr_bit(PORTA, PA0);
        _delay_ms(10000); 
		set_bit(PORTA, PA0);
		_delay_ms(10000);
    }
	return 0;
}
