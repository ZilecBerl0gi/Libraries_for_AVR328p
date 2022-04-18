/*
 * Lcd_I2C_Lib.cpp
 *
 * Created: 10.09.2021 0:09:35
 * Author : Михаил
 */ 
#define F_CPU 12000000UL
#include <util/delay.h>
#include "LCD_I2C_Lib.h"
#include "I2C.h"
#include <stdlib.h>
#include <string.h>
unsigned char portlcd = 0;
unsigned char Adress = 0x27;
I2C Lcd_n;

LCD::LCD(unsigned char Addr, int Freq_CPU)
{
	_delay_ms(100);
	Lcd_n.Init(Freq_CPU);
	Lcd_n.setBitRate(160,1);
	Adress = Addr;
	Adress = Adress << 1;
	_delay_ms(100);
	
	sendhalfbyte(0b00000011);
	_delay_ms(10);
	
	sendhalfbyte(0b00000011);
	_delay_us(10);
	
	sendhalfbyte(0b00000011);
	_delay_ms(10);
	
	sendhalfbyte(0b00000010);
	_delay_ms(10);
	
	sendbyte(0b00101000, 0); //включаем режим работы
	_delay_ms(1);
	
	sendbyte(0b00000001, 0);// очищаем экран
	_delay_ms(100);
	
	sendbyte(0b00000110, 0); //Прячем отображения курсора
	_delay_ms(1);
	
	sendbyte(0b00000010, 0); //ставим курсор в начальное положение
	_delay_ms(1);
	
	sendbyte(0b00001100, 0); //включаем экран
	setled();//включаем светодиод
	setwrite();//Стартовое положение экрана
}
void LCD::e1()
{
//Lcd_n.sendByteAdress(portlcd|=0x04,Adress);
portlcd|=0x04;
}
void LCD::e0()
{
	//Lcd_n.sendByteAdress(portlcd&=~0x04,Adress);
	portlcd&=~0x04;
}
void LCD::rs1()
{
	//Lcd_n.sendByteAdress(portlcd|=0x01,Adress);
	portlcd|=0x01;
}
void LCD::rs0()
{
	//Lcd_n.sendByteAdress(portlcd&=~0x01,Adress);
	portlcd&=~0x01;
}
void LCD::setled()
{
	Lcd_n.sendByteAdress(portlcd|=0x08,Adress);
}
void LCD::setwrite()
{
	Lcd_n.sendByteAdress(portlcd&=~0x02,Adress);
}
void LCD::sendhalfbyte(unsigned char c)
{
	c<<=4;
	e1();
	_delay_us(250);
	Lcd_n.sendByteAdress(portlcd|c,Adress);
	e0();
	Lcd_n.sendByteAdress(portlcd|c,Adress);
	_delay_us(250);
}
void LCD::sendbyte(unsigned char c, unsigned char mode)
{
	if(mode == 0) 
	{
		rs0();
	}
	else 
	{
		rs1();
	}
	unsigned char hc=0;
	hc=c>>4;
	sendhalfbyte(hc); sendhalfbyte(c);
}
void LCD::writeChar(unsigned char c)
{
	sendbyte(c,1);
}
void LCD::clearCommand()
{
	setPos(0,0);
	sendbyte(0b00000001, 0);
	_delay_us(20000);
	
}
void LCD::clearProgramm()
{
	setPos(0,0);
	writeString("                    ");
	setPos(0,1);
	writeString("                    ");
	setPos(0,2);
	writeString("                    ");
	setPos(0,3);
	writeString("                    ");
	setPos(0,0);
}
void LCD::setPos(unsigned char x, unsigned char y)
{
	switch(y)
	{
		case 0:
		sendbyte(x|0x80,0);
		break;
		case 1:
		sendbyte((0x40+x)|0x80,0);
		break;
		case 2:
		sendbyte((0x14+x)|0x80,0);
		break;
		case 3:
		sendbyte((0x54+x)|0x80,0);
		break;
	}
}
void LCD::setCursor(uint8_t Type)
{
	if (Type == 1)
	{
		sendbyte(0b00001101,0);
	}
	else if(Type == 2)
	{
		sendbyte(0b00001110,0);
	}
	else
	{
		sendbyte(0b00001100,0);
	}
}
void LCD::writeCustomChar(uint8_t x, uint8_t y, uint8_t _position_in_memory)
{
	setPos(x,y);
	switch (_position_in_memory)
	{
		case 0:
		writeChar(0x08);
		break;
		case 1:
		writeChar(0x09);
		break;
		case 2:
		writeChar(0x0A);
		break;
		case 3:
		writeChar(0x0B);
		break;
		case 4:
		writeChar(0x0C);
		break;
		case 5:
		writeChar(0x0D);
		break;
		case 6:
		writeChar(0x0E);
		break;
		case 7:
		writeChar(0x0F);
		break;
	}
	
}
void LCD::CreateCustomChar(unsigned char CHAR[8], uint8_t position_in_memory)
{
	switch (position_in_memory)
	{
		case 0:
		sendbyte(0x40 | 0x00,0);
		break;
		case 1:
		sendbyte(0x40 | 0x08,0);
		break;
		case 2:
		sendbyte(0x40 | 0x10,0);
		break;
		case 3:
		sendbyte(0x40 | 0x18,0);
		break;
		case 4:
		sendbyte(0x40 | 0x20,0);
		break;
		case 5:
		sendbyte(0x40 | 0x28,0);
		break;
		case 6:
		sendbyte(0x40 | 0x30,0);
		break;
		case 7:
		sendbyte(0x40 | 0x38,0);
		break;
	}
	for (int i = 0; i < 8;i++)
	{
		writeChar(CHAR[i]);
	}
}
void LCD::writeString(char str1[20])
{
	uint8_t n=0;
	while(str1[n]!='\0')
	{
		writeChar(str1[n]);
		n++;
	}
}
void LCD::SetBacklight(bool Turning)
{
	if (Turning == true)
	{
		Lcd_n.sendByteAdress(portlcd|=0x08,Adress);
	} 
	else if (Turning == false)
	{
		Lcd_n.sendByteAdress(portlcd&=~0x08,Adress);
	}
}
void LCD::writeInt(long int Number)
{
	char numString[15];
	itoa(Number, numString, 10);
	for (unsigned int i = 0; i < strlen(numString); i++)
	{
		writeChar(numString[i]);
		_delay_us(100);
	}
}
void LCD::writeDouble(double Number,int Tochnost)
{
	if (Number > 0)
	{
		int H;
		int L;
		//L = modf(Number, &H);
		H = int(Number);
		L = (Number - H)*pow(10,Tochnost);
		writeInt(H);
		writeChar(',');
		writeInt(L);
	}
	else if(Number < 0)
	{
		int H;
		int L;
		//L = modf(Number, &H);
		H = int(Number*-1);
		L = ((Number*-1) - H)*pow(10,Tochnost);
		writeChar('-');
		writeInt(H);
		writeChar(',');
		writeInt(L);
	}
}
