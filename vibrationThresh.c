#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
#include "lcd.h"
#include "lcd.c"
int main(void)
{
    for(int l=0;l<10;l++)
    {
        int a[15],maxa=0,mina=32167,difference=0;
		DDRA=0x00;
		ADMUX=0b01100111;
		for(int j=0;j<15;j++)
		{
			ADCSRA=0b11000111;
			while(ADCSRA&(1<<ADSC))
			{
			}
			a[j]=ADCH;
			
		}
		for(int i=0;i<15;i++)
		{ if(a[i]>maxa)
			maxa=a[i];}
			for(int m=0;m<15;m++)
			{if(a[m]<mina)
				mina=a[m];
			}
			difference=maxa-mina;
			DDRB=0xFF;
			init_LCD();
			_delay_ms(50);
			print_integer(difference);
			_delay_ms(2000);
			clear_display();
			_delay_ms(50);				 
    }
}
