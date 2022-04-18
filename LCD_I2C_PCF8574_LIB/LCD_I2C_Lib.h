/*
 * LCD_I2C_Lib.h
 *
 * Created: 10.09.2021 8:01:45
 *  Author: Михаил
 */ 


#ifndef LCD_I2C_LIB_H_
#define LCD_I2C_LIB_H_

class LCD
{
	
public:
LCD(unsigned char Addr, int Freq_CPU);
void writeChar(unsigned char c);//записать байт в дисплей
void clearCommand();//очистить дисплей коммандой на контроллер
void clearProgramm();//очистить дисплей программно
void setCursor(uint8_t Type);//установить тип крусора 0 - нет 1 - мегающий 2 - статичное нижнее подчёркивание 
void writeCustomChar(uint8_t x, uint8_t y, uint8_t _position_in_memory);//записать свой байт
void writeString(char str1[]);//записать строку
void setPos(unsigned char x, unsigned char y);//установить позицию буквы
void writeInt(long int Number);//записывает int 
void writeDouble(double Number,int Tochnost);//записывает вещественное число
void SetBacklight(bool Turning);//включить выключить подсветку
void CreateCustomChar(unsigned char CHAR[8], uint8_t position_in_memory);
private:
void e1();
void e0();
void rs1();
void rs0();
void setled();
void setwrite();
void sendhalfbyte(unsigned char c);
void sendbyte(unsigned char c, unsigned char mode);
};




#endif /* LCD_I2C_LIB_H_ */