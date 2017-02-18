#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "lcd.h"
#include "lcd.c"
void forward()
{
	PORTC |=(1<<2) ;
	PORTC |=(1<<4);
	PORTC &=(~(1<<3));
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
}
void backward()
{
	PORTC |=(1<<3) ;
	PORTC |=(1<<5);
	PORTC &=(~(1<<2));
	PORTC &=(~(1<<4));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
	
	
}
void left_forward()
{
	PORTC &=(~(1<<2)) ;
	PORTC |=(1<<4);
	PORTC &=(~(1<<3));
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
}
void right_forward()
{
	
	PORTC &=(~(1<<5)) ;
	PORTC |=(1<<2);
	PORTC &=(~(1<<4));
	PORTC &=(~(1<<3));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
}
void extreme_left()
{
	
	PORTC &=(~(1<<2)) ;
	PORTC |=(1<<4);
	PORTC |=(1<<3);
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
}

void extreme_right()
{
	
	PORTC &=(~(1<<3)) ;
	PORTC |=(1<<2);
	PORTC |=(1<<5);
	PORTC &=(~(1<<4));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=145;
	OCR1BL=145;
}

int main(void)
{
	DDRB = 0xff;
	DDRC=0xFF;
	DDRD=0xFF;
	TCNT1=0;
	init_LCD();
	_delay_ms(50);
	int i,x,sensor[5];
		char thres[5]={186,123,123,154,116};
		DDRB=0b11111111;
		DDRA=0b00000000;
		while(1)
		{
			x = 0;
			clear_display();
			ADMUX=0b01100010;
			for(i=0;i<5;i++)
			{
				ADCSRA=0b11000111;
				while (ADCSRA & (1<<ADSC));
				if(ADCH>thres[i])
				{
					x|=(1<<i);
					LCD_write('1');
				}
				else
				LCD_write('0');
				/*if(i==4)
				{set_DDRAM_address(0x40);}
				print_integer(ADCH);
				print_string(" ");*/
				ADMUX++;
			}
			_delay_ms(100);
			//x=((sensor[0]*16)+(sensor[1]*8)+(sensor[2]*4)+(sensor[3]*2)+(sensor[4]*1));
			switch(x)
			{
				case 4:
				case 14:
				case 12:
				case 6:
				case 2:
				case 8:
				forward();
				
				break;
				
				case 7:
				case 15: 
				 extreme_right ();
				 
				break;
				
				case 28:
				case 30: 
				extreme_left();
				break;
				
				case 1:
				case 3: 
				right_forward();
				break;
				
				case 24:
				case 16: 
				 left_forward();
				break;
				
				default:  backward();
				break;
			}
		}
	}
