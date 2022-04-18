#include <avr/io.h>
#include <util/delay.h>
#include "DHT12_I2C.h"
#include "I2C.h"
I2C DHT12_n;

DHT12::DHT12(int _FREQ)
{
	DHT12_n.Init(_FREQ);
	DHT12_n.setBitRate(200,1);
}

void DHT12::Read_Data()
{
			DHT12_n.StartCondition();
			DHT12_n.sendByte(0xB8);
			DHT12_n.sendByte(0x00);
			DHT12_n.StartCondition();
			DHT12_n.sendByte(0xB9);
			DHT12::Humidity = DHT12_n.ReadByte();
			DHT12::HumidityScale = DHT12_n.ReadByte();
			DHT12::Temperature = DHT12_n.ReadByte();
			DHT12::TemperatureScale = DHT12_n.ReadByte();
			DHT12::CHECKSUM = DHT12_n.ReadEndByte();
			DHT12_n.StopCondition();
}

float DHT12::GetHumidity()
{
	float i = DHT12::Humidity;
	i += (float)DHT12::HumidityScale / 10;
	return i;
}

float DHT12::GetTemperature()
{
	float i = DHT12::Temperature;
	i += (float)DHT12::TemperatureScale / 10;
	return i;
}

bool DHT12::CheckSum()
{
	if (DHT12::CHECKSUM == (DHT12::Humidity + DHT12::HumidityScale + DHT12::Temperature + DHT12::TemperatureScale))return true;
	else return false;	
}
