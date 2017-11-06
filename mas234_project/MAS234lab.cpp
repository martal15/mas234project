#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//1.7.6 Button and LED w/interrupt

long minimumClickDtMs = 50;
long lastClickDtMs = minimumClickDtMs;

int main(void)
{
	//Setting port D0 to be an output, and all the other pins in port D to be inputs
	DDRD = (1 << PD0);
	
	//Setting port D0 to be low as initial state
	PORTD = 0x00;
	
	//Pin Change Mask Register 2
	//Enabling PinChangeInterrupt on PD5(PCINT21)
	PCMSK2 |= (1 << PCINT21);
	//Pin Change Interrupt Flag Register
	//Enabling PCINT[23:16] pins to trigger an interrupt request
	PCICR |= (1 << PCIE2);
	
	//Enable interrupt by setting global interrupt mask
	sei();
	
	while(1)
	{
		//Count up milliseconds from last time button was pressed
		_delay_ms(1);
		lastClickDtMs++;
	}
}

//The interupt function for PinChangeInteruptor2 vector
ISR (PCINT2_vect)
{
	//If the minimum time between button presses is exceeded and button is pressed
	if(!(PIND & (1 << PD5)) && lastClickDtMs > minimumClickDtMs) {
		//Toggle the LED output pin
		PORTD = (PORTD ^ 0x01);
		//Reset the timer for last button press
		lastClickDtMs = 0;
	}
}
