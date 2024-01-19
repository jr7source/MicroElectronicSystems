/**
	@author Thomas Grunenberg
	@author Jatin Ramchandani	
	@version 0.1
	@file main.c
	@brief Temperature Controler
*/

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL

const char MtrNum[] __attribute__((__progmem__)) = "28822";

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
uint16_t fan_power, temp, ref_temp;
uint8_t temp_raw;
int8_t  out, er;
/******************************************************************************/
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
/**
	@brief Init the PORTx and DDRx register for the I/O setup
*/
void init(void){
	

	DDRB |= ( 1<< DDB4); // MOSI PB4 direction out

	//Enable SPI ans SPI Interrupt
	//TODOdone
	SPCR |=(1 << SPIE | 1 << SPE);
	
}

/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/


int main(void){

	// Init
	init();
	lcd_init();
	
	lcd_clear();
	lcd_string("Test");	
	
	sei();
	
	//TODOdone
	char disp[16];
	ref_temp = 550;
	
	// Endless loop
	for(;;){	
	temp = (temp_raw * 2) + 150;
	er = temp - ref_temp;	// feedback control 
	out = er * 100;		// gain = 100
	
	if (out >= 255) {
		fan_power = 255;
	}
	else if (out <= 0) {
		fan_power = 0;
	}
	else 
		fan_power = out;
		
	lcd_clear();
	if (temp > 400) {
        sprintf(disp, "Temp C:%d,%d hot", temp / 10, temp % 10);
    	} else {
        sprintf(disp, "Temp C:%d,%d cool", temp / 10, temp % 10);
    	}
	lcd_string(disp);
	_delay_ms(100);
	}	
	
	return 0;
}
/******************************************************************************/
ISR(SPI_STC_vect){
	//TODOdone
	temp_raw = SPDR; 
	SPDR = fan_power;
}
/******************************************************************************/
