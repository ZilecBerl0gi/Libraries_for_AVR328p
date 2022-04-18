/*
 * ADC.h
 *
 * Created: 17.04.2022 23:22:46
 *  Author: Mikhail
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#define  TemperatureChannel 8
#define  Division2 0
#define  Division4 1
#define  Division8 2
#define  Division16 3
#define  Division32 4
#define  Division64 5
#define  Division128 6
class ADClib
{
	public:
	ADClib(uint8_t Channel);
	unsigned int Convert ();
	private:
	uint8_t chanel;
};

class ADCsettings
{
	public:
	void setRef(uint8_t Ref);
	void setADPS(uint8_t adps);
	private:
};




#endif /* ADC_H_ */