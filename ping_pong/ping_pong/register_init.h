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

	
	clr_bit(DDRD, DDD2);
	
}



#endif /* REGISTER_INIT_H_ */