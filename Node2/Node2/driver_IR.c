/*
 * driver_IR.c
 *
 * Created: 01.11.2017 17:24:10
 *  Author: julihag
 */ 

#include "driver_IR.h"
#include "driver_ADC.h"
#include <stdio.h>



int IR_digital_filter(void){
	uint16_t total_read_value = 0;
	
	for(int i = 0 ; i < 4 ; i++){
		total_read_value += ADC_read();
	}
	return total_read_value/4;
}

int IR_game_over(){
	if(IR_digital_filter() < 250){
		return 1;
	}
	return 0;
	
}



