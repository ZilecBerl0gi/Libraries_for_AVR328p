/*
 * I2C.h
 *
 * Created: 05.09.2021 15:00:05
 *  Author: Михаил
 */ 


#ifndef I2C_H_
#define I2C_H_
class I2C
{
public:
void Init();//инициализация шины i2c
void Init(int freq___);//инициализация шины i2c
void setBitRate(int Frequency, int Prescaler);// принимает частоту в кгц, частота от 30000 гц до 1000000 гц, значения Prescaler 1,4,16,64 
void sendByteAdress(unsigned char Byte, unsigned char Adress_N);// функция отправляет байт данных на шину I2C
void putBuffer(unsigned char Byte);
void clearBuffer();
void sendByteAdressStream(unsigned char Adress);
unsigned char ReadByte(); // считывает данные
unsigned char ReadEndByte();//считывает последний, ОСОБЕННЫЙ байт
void StartCondition();
void StopCondition();
void sendByte(unsigned char Byte_n);
protected:
private:



};



#endif /* I2C_H_ */