/*
 * register_init.h
 *
 * Created: 06.09.2017 18:36:12
 *  Author: andrholt
 */ 


#ifndef REGISTER_INIT_H_
#define REGISTER_INIT_H_
void register_init(void);

void register_init(void){
	//enabler externt minne i MCU
	set_bit(MCUCR, SRE);
	set_bit(SFIOR, XMM2);

	//enable interrupts in MCU
	clr_bit(MCUCR,ISC00);
	set_bit(MCUCR,ISC01);
	set_bit(GICR,INT0);
	
	
	clr_bit(DDRD, DDD2);
	
	//Set timer/counter1 interrupt
	//Normal mode
	clr_bit(TCCR1A, WGM11);
	clr_bit(TCCR1A, WGM10);
	
	//Prescaler Fosc/1024
	set_bit(TCCR1B, CS11);
	set_bit(TCCR1B, CS10);
	
	//Interrupt enable overflow
	set_bit(TIMSK, TOIE1);

}



#endif /* REGISTER_INIT_H_ */