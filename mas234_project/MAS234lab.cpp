#define F_CPU 1000000L

#include <avr/io.h>
#include <util/delay.h>

//Anny use of shifting in 0 to any bit by using "or" function is only for increasing understandability,
//and to mark that these bits are deliberately not set, as they are parts of multi-bit setting.
//Using "or" function to set bits to 0 is anyways not possible, and they have to be set to 0 using "and".
//An example of this use is found in setting the prescaler to 16, where the ADPS2 bit in ADCSRA should not be set.

//1.8.4 ADC

int main(void)
{
	//Setting port D0 to be an output, and all the other pins in port D to be inputs
	DDRD = (1 << PD0);
	//Setting port D0 to be low as initial state
	PORTD = 0x00;
	
	//Setup analog read
	//Set prescaler to 16, to read ad 62,5 kHz
	ADCSRA |=  (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	//Since analog voltage reference is AREF, we don't need to set any bits for voltage reference selection
	ADMUX |= (0 << REFS1) | (0 << REFS0);
	//Left adjust result
	ADMUX |= (1 << ADLAR);
	//Since we are converting ADC0 we don't need to set any channel selection bits in ADMUX
	ADMUX |= (0 << MUX3) | (0 << MUX2) | (0 << MUX1) | (0 << MUX0);
	
	//Set ADC in free running mode
	//Setting ADC to auto trigger, trigger source is defined in ADCSRB shown under
	ADCSRA |= (1 << ADATE);
	//Since the trigger source is free running we don't need to set any bits for trigger source
	ADCSRB |= (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);
	
	//Enable analog conversion
	ADCSRA |= (1 << ADEN);
	//Start analog conversion
	ADCSRA |= (1 << ADSC);
		
	while(1)
	{
		//Read analog conversion from ADCL
		uint8_t p = ADCH;
		
		//PWM output on PD0 according to the analog value
		for(int i = 0; i < 256; i++) {
			PORTD = ((p > i) << PD0);
			_delay_us(50);
		}
	}
}
