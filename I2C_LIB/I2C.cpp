/*
 * I2C_Library.cpp
 *
 * Created: 05.09.2021 14:32:53
 * Author : Михаил
 */ 

#include <avr/io.h>
#include "I2C.h"
#include <util/delay.h>
int CpuFreq = 8000;
uint8_t Buffer[64];
uint8_t counter = 0;
void I2C::Init()
{
	CpuFreq = F_CPU/1000;
}
void I2C::Init(int freq___)
{
    CpuFreq = freq___;
}
void I2C::setBitRate(int Frequency, int Prescaler)
{
	int Freq;
	switch (Prescaler)//установка делителя
	{
		case 1: TWSR  &= ~(1 << TWPS0);TWSR  &= ~(1 << TWPS1); break;
		case 4: TWSR |= (1 << TWPS0);TWSR  &= ~(1 << TWPS1); break;
		case 16: TWSR  &= ~(1 << TWPS0);TWSR |= (1 << TWPS1); break;
		case 64: TWSR |= (1 << TWPS0);TWSR |= (1 << TWPS1); break;
	}
	Freq = ((CpuFreq / Frequency)-16)/2;//установка частоты для шины
	if (Freq > 255) // ограничение диапазона
	{
		Freq = 255;
	}
	else if (Freq < 0)
	{
		Freq = 0;
	}
	TWBR = Freq;//запись частоты в регистр
}
void I2C::StartCondition()
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTA);//отправляем условие старта
	while (!(TWCR&(1 << TWINT))){;}//ждём пока передача старта закончится
}
void I2C::StopCondition()
{
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWSTO);//отправляем условие стопа
}
void I2C::sendByte(unsigned char Byte_n){
	TWDR = Byte_n;
	TWCR = (1 << TWEN) | (1 << TWINT);
	int16_t counterACK = 0;
	while (!(TWCR&(1 << TWINT))){counterACK++; if (counterACK > 1000000) break;}
}
void I2C::sendByteAdress(unsigned char Byte, unsigned char Adress_N)
{
	I2C::StartCondition();//отправляем условие старта
	I2C::sendByte(Adress_N);//отправляем адресс
	I2C::sendByte(Byte);//отправляем нужный байт
	I2C::StopCondition();//останавливаем передачу
}
void I2C::putBuffer(unsigned char Byte)
{
	Buffer[counter] = Byte;
	counter++;
	if(counter > 63) counter = 63;
}
void I2C::clearBuffer()
{
	for (int i = 0; i < 63; i++)
	{
		Buffer[i] = 0x00;
	}
	counter = 0;
}
void I2C::sendByteAdressStream(unsigned char Adress)
{
	I2C::StartCondition();
	I2C::sendByte(Adress);
	if(counter < 2)
	{
		I2C::sendByte(Buffer[0]);
		I2C::sendByte(Buffer[1]);
	}
	else
	{
	for (int i = 0; i < counter; i++)I2C::sendByte(Buffer[i]);
	}
	I2C::StopCondition();
}
unsigned char I2C::ReadByte()
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA)| (1 << TWIE);//включим прием данных
		while (!(TWCR&(1 << TWINT)))
		{
			
		}
	return TWDR;
}
unsigned char I2C::ReadEndByte()
{
	TWCR = (1 << TWEN) | (1 << TWINT);//подрубаем приём
while (!(TWCR&(1 << TWINT)))
{
	
}
	return TWDR;//возвращаем значения
}