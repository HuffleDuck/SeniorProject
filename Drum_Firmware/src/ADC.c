/*
 * ADC.c
 *
 * Created: 1/19/2016 10:44:52 PM
 *  Author: B-Chan
 */ 
#include "ADC.h"

void InitADC(void)
{
	ADCSRA |= _BV(ADPS1) | _BV(ADPS2); // set ADC sample rate to - 125kHz @ 8Mhz (div 64 prescaler)
	
	ADMUX |= _BV(ADLAR); // Left adjust ADC
	
	DIDR0 |= _BV(ADC1D); //disabling digital input for pin A1
	DIDR0 |= _BV(ADC2D); //disabling digital input for pin A2
	
	ADCSRA |= _BV(ADEN);//enable ADC
	PRR &= ~(_BV(PRADC)); // Disable the power reduction ADC bit
}

void ChannelOne(void)
{
	ADMUX |= _BV(REFS0); // 3.3v refrece voltage
	ADMUX &= ~ (_BV(REFS1)); // negate REFS1 or else it's left high
	
	ADMUX &= 0b11110000; //clear the pin selection
	ADMUX |= _BV(MUX0); // a1 is input
	
	ADCSRA |= _BV(ADSC); // start conversion, use this when ADC is in free running mode to start conversion
	//otherwise it is triggered by something
	
}
