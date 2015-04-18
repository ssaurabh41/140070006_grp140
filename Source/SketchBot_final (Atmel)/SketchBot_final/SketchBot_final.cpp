/*
 * SketchBot_final.cpp
 *
 * Created: 07-03-2015 09:56:32
 * 
 */



//!!!during initializing of devices, keep interrupts cleared!!!
#define F_CPU 14745600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <math.h>
//#include "ADC.h"
#include "Motion(And its related PWM).h"
//#include "lcd.h"
#include "XBee.h"
#include "servo.h"

void buzzer_on (void)	//Turn on buzzer
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore | 0x08;
	PORTC = port_restore;
}

void buzzer_off (void)	//turn off buzzer
{
	unsigned char port_restore = 0;
	port_restore = PINC;
	port_restore = port_restore & 0xF7;
	PORTC = port_restore;
}

char data;
volatile float x1=0,y1=0, x_base=0, y_base=0;		//store the corrent coordinates and previous coordinates respectively
int state=0;
int proceed=0;
float current_angle=90.0;
Point A={x_base,y_base};
Point B={x1,y1};
char angle;


SIGNAL(SIG_USART0_RECV) 		// ISR for receive complete interrupt
{
	data = UDR0; 				//making copy of data from UDR0 in 'command' variable

	if(state==0)
	{
		state=1;
		buzzer_on();
		_delay_ms(100);
		buzzer_off();
	}
	
	else if(state==1)                        //receive command
	{
		
		if(data==0)
		{
			state=2;
		}

		else if(data==1)
		{
			sei();
			//penup
			penUp();
			state=2;
			cli();
		}

		else if(data==2)
		{
			sei();
			//pendown
			penDown();
			state=2;
			cli();
		}
	}

	else if(state==2)                  //receive x-coordinate
	{
		x1=data;
		state=3;
	}	
	
	else if(state==3)                 //sign of x-coordinate
	{
		
		if(data==1)
		{
			x1 = -(255 - x1);
		}
		state=4;
	}

	else if(state==4)                //receive y-coordinate
	{
		
		y1=data;
		state=5;
	}

	else if(state==5)               //sign of y-coordinate and move
	{
		buzzer_on();
		_delay_ms(100);
		buzzer_off();
		if(data==1)
		{
			y1 = -(255 - y1);
		}

		A.x=x_base; A.y=y_base;
		B.x=x1; B.y=y1;

		sei();

		move(A,B,current_angle);
		update_current_angle(A,B,current_angle);

		state=1;
		
		UDR0=data;			//send status data back to XBee
		_delay_ms(100);
		
	}

	UDR0=data;				//send status data back to XBee
	_delay_ms(100);

}

int main()
{
	cli();
	DDRC = DDRC | 0x08;		//Setting PORTC 3 as output
	PORTC = PORTC & 0xF7;		//Setting PORTC 3 logic low to turnoff buzzer
	motion_pin_config();		
	position_encoder_init();
	uart0_init();
	timer1_init();
	servo1_pin_config();
	sei();
	penUp();

	while(1);
}

