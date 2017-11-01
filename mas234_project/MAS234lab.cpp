#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

//1.7.4 Button and LED wo/interrupt

int main(void)
{
	//Setting port D0 to be an output, and all the other pins in port D to be inputs
	DDRD = (1 << PD0);
	
	//Setting port D0 to be low as initial state
	PORTD = 0x00;
	
	while(1)
	{
		//If PD5 is high, the button is not pressed
		if((PIND & (1 << PD5)))
		{
			//Set PD0 low
			PORTD &= ~(1 << PD0);
		}
		//Else if PD5 is low, the button is pressed
		else
		{
			//Set PD0 high
			PORTD |= (1 << PD0);
		}
	}
}
