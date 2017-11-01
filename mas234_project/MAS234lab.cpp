#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	//Setting port D0 to be an output
	DDRD = (1 << PD0);
	
	//Setting port D0 to be low as initial state
	PORTD = 0x00;
	
	//
	while(1)
	{
		//A for loop that incrementally increases how much of the time the LED should stay on
		for(int p = 0; p < 100; p++)
		{
			//A for loop that acts as a counter in an DAC
			for(int i = 0; i < 100; i++)
			{
				//If the counter "i" is more than "p", turn on port D0. If not turn it off
				PORTD = ((p < i) << PD0);
				//Delay for 100us, this should give a frequency of 50Hz
				_delay_us(100);
			}
		}
		
		//A for loop that incrementally decreases how much of the time the LED should stay on
		for(int p = 100; p > 0; p--)
		{
			//A for loop that acts as a counter in an ADC
			for(int i = 0; i < 100; i++)
			{
				//If the counter "i" is more than "p", turn on port D0. If not turn it off
				PORTD = ((p < i) << PD0);
				//Delay for 100us, this should give a frequency of 50Hz
				_delay_us(100);
			}
		}
	}
}
