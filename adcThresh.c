#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "LCD.c"


int main(void)
{int i;
	DDRA=0x00;
	DDRB=0xff;
	
	while(1)
	{
		init_LCD();
		_delay_ms(50);
		ADCSRA=0b10000111;
		ADMUX=0b01100010;
		for(i=0;i<3;i++){
			
			ADCSRA=0b11000111;
			while(ADCSRA&(1<<6))
			{
			}
			
			print_integer(ADCH);
			print_string(" ");
			ADMUX++;
		}
		set_DDRAM_address(0x40);
		for(i=0;i<2;i++)
		{
			ADCSRA=0b11000111;
			while(ADCSRA&(1<<6))
			{
			}
			print_integer(ADCH);
			print_string(" ");
			ADMUX++;
		}
		_delay_ms(4000);
	}
}
