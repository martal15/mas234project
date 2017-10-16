#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRD = (1 << PD0);
	PORTD = 0x00;
	
	while(1)
	{
		PORTD = (1 << PD0);
		_delay_ms(500);
		PORTD = (0 << PD0);
		_delay_ms(500);
	}
}
