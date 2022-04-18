/*
 * DHT12_I2C.h
 *
 * Created: 16.01.2022 1:35:49
 *  Author: Михаил
 */ 

#ifndef DHT12_I2C_H_
#define DHT12_I2C_H_
class DHT12
{
	public:
	DHT12(int _FREQ);
	void Read_Data();
	float GetTemperature();
	float GetHumidity();
	bool CheckSum();
	private:
	unsigned char Temperature,Humidity;
	unsigned char TemperatureScale, HumidityScale;
	unsigned char CHECKSUM;
	int MCU_Freq___;
};
#endif /* DHT12_I2C_H_ */