/*
 * ADC.cpp
 *
 * Created: 17.04.2022 23:25:10
 *  Author: Mikhail
 */ 
#include "ADC.h"

ADClib::ADClib(uint8_t Channel)
{
	ADClib::chanel = Channel;
}

void ADCsettings::setRef(uint8_t Ref)
{
	ADCSRA |= (1<<ADEN);//основные настройки
	if (Ref == 0)                             //AVCC with external capacitor at AREF pin
	{
		ADMUX |= (1<<REFS0);
		ADMUX &= ~(1 << REFS1);
	}
	else if(Ref == 1){                        //AREF, Internal Vref turned off
		ADMUX &= ~((1 << REFS1)|(1 << REFS0));
	}
	else if(Ref == 2){
		ADMUX |= (1 << REFS1) | (1 << REFS0); //Internal 1.1V Voltage Reference with external capacitor at AREF pin
	}
}

void ADCsettings::setADPS(uint8_t adps)
{
	switch(adps)
	{
		case 0:
		ADCSRA |= (1 << ADPS0);
		ADCSRA &= ~((1 << ADPS1) | (1 << ADPS2));
		break;
		case 1:
		ADCSRA |= (1 << ADPS1);
		ADCSRA &= ~((1 << ADPS0) | (1 << ADPS2));
		break;
		case 2:
		ADCSRA &= ~(1 << ADPS2);
		ADCSRA |= (1 << ADPS1) | (1 << ADPS0);
		break;
		case 3:
		ADCSRA |= (1 << ADPS2);
		ADCSRA &= ~((1 << ADPS1) | (1 << ADPS0));
		break;
		case 4:
		ADCSRA &= ~(1 << ADPS1);
		ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
		break;
		case 5:
		ADCSRA &= ~(1 << ADPS0);
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
		break;
		case 6:
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
		break;
	}
}

unsigned int ADClib::Convert()
{
	switch (ADClib::chanel)
	{
		case 0:
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
		break;
		case 1:
		ADMUX |= (1 << MUX0);
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1));
		break;
		case 2:
		ADMUX |= (1 << MUX1);
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX0));
		break;
		case 3:
		ADMUX |= (1 << MUX1) | (1 << MUX0);
		ADMUX &= ~((1 << MUX3) | (1 << MUX2));
		break;
		case 4:
		ADMUX |= (1 << MUX2);
		ADMUX &= ~((1 << MUX3) | (1 << MUX1) | (1 << MUX0));
		break;
		case 5:
		ADMUX |= (1 << MUX2) | (1 << MUX0);
		ADMUX &= ~((1 << MUX3) | (1 << MUX1));
		break;
		case 6:
		ADMUX |= (1 << MUX2) | (1 << MUX1);
		ADMUX &= ~((1 << MUX3) | (1 << MUX0));
		break;
		case 7:
		ADMUX |= (1 << MUX2) | (1 << MUX1) | (1 << MUX0);
		ADMUX &= ~(1 << MUX3);
		break;
		case 8:
		ADMUX |= (1 << MUX3);
		ADMUX &= ~((1 << MUX2) | (1 << MUX1) | (1 << MUX0));
		break;
	}
	ADCSRA |= (1<<ADSC); //Начинаем преобразование
	while((ADCSRA & (1<<ADSC))); //проверим закончилось ли аналого-цифровое преобразование
	return (unsigned int) ADC;
}
