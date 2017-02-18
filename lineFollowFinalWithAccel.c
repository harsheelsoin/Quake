#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
void forward()
{
	PORTC |=(1<<2) ;
	PORTC |=(1<<5);
	PORTC &=(~(1<<3));
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
}
void backward()
{
	PORTC |=(1<<3) ;
	PORTC |=(1<<4);
	PORTC &=(~(1<<2));
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
	
}
void left_forward()
{
	PORTC &=(~(1<<2)) ;
	PORTC |=(1<<4);
	PORTC &=(~(1<<3));
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
}
void right_forward()
{
	
	PORTC &=(~(1<<5)) ;
	PORTC |=(1<<2);
	PORTC &=(~(1<<4));
	PORTC &=(~(1<<3));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
}
void extreme_left()
{
	
	PORTC &=(~(1<<2)) ;
	PORTC |=(1<<4);
	PORTC |=(1<<3);
	PORTC &=(~(1<<5));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
}

void extreme_right()
{
	
	PORTC &=(~(1<<3)) ;
	PORTC |=(1<<2);
	PORTC |=(1<<5);
	PORTC &=(~(1<<4));
	TCCR1A=0b10100001;
	TCCR1B=0b00001001;
	OCR1AL=127;
	OCR1BL=127;
}

int main(void)
{
	DDRC=0xFF;
	DDRD=0xFF;
	int i,x,sensor[5],th;
float thres[5]={210,190,170,220,165};
	//LDR	float thres[5]={182,125.5,132,150.5,135};
	DDRB=0b11111111;
	DDRA=0b00000000;
	while(1)
	
		{
			int a[15],maxa=0,mina=32167,difference=0;
			DDRA=0x00;
			ADMUX=0b01100010;
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
			if(difference>th)
			PORTC|=(1<<6);
			if(difference<th)
			PORTC&=(~(1<<6));
- hide quoted text -
			
		
		ADMUX=0b01100011;
	    for(i=0;i<5;i++)
	    {
		   
		    ADCSRA=0b11000111;
		    while (ADCSRA & (1<<ADSC))
				{}
			if(ADCH>thres[i])
			{
				sensor[i]=1;
			}
			else
			{
				sensor[i]=0;
			}
			ADMUX++;
		}
		x=((sensor[0]*16)+(sensor[1]*8)+(sensor[2]*4)+(sensor[3]*2)+(sensor[4]*1));
		switch(x)
		{
			case 4:
			case 14:forward();
					break;
		
			case 1:
			case 3:
			case 7:
			case 15:  extreme_right ();
				break;
		
			case 16:
			case 24:
			case 28:
			case 30: extreme_left();
				break;
		
			case 2:
			case 6:  right_forward();
				break;
		
			case 8: 
			case 12:  left_forward();
				break;
		
			default:  backward();
			break;
		}
	}
}
