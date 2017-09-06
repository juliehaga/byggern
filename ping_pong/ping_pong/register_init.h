/*
 * register_init.h
 *
 * Created: 06.09.2017 18:36:12
 *  Author: andrholt
 */ 


#ifndef REGISTER_INIT_H_
#define REGISTER_INIT_H_

void register_init(void){
	//Setter PA0-PA7 til output pins
	 set_bit(DDRA,PA7);
	 set_bit(DDRA,PA6);
	 set_bit(DDRA,PA5);
	 set_bit(DDRA,PA4);
	 set_bit(DDRA,PA3);
	 set_bit(DDRA,PA2);
	 set_bit(DDRA,PA1);
	 set_bit(DDRA,PA0);
	 
	 //Setter PC0-PC3 til output
	 set_bit(DDRC,DDC0);
	 set_bit(DDRC,DDC1);
	 set_bit(DDRC,DDC2);
	 set_bit(DDRC,DDC3);
	
	//enabler SRAM i MCU
	set_bit(MCUCR, SRE);
	set_bit(SFIOR, XMM0);
	
	//Setter ALE til output
	set_bit(DDRE, DDE1);
};



#endif /* REGISTER_INIT_H_ */