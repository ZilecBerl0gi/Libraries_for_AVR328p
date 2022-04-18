/*
 * DS3231.h
 *
 * Created: 16.01.2022 21:24:26
 *  Author: Михаил
 */ 


#ifndef DS3231_H_
#define DS3231_H_

class DS3231
{
public:
DS3231(int Freq);
void SetTime(int Seconds, int Minutes, int Hours);
int ReadSeconds();
int ReadMinutes();
int ReadHours();
void SetDate(int Day_Of_Week, int Day_Of_Month, int Month, int Year);
int ReadDayOfTheWeek();
int ReadDayOfMonth();
int ReadMonth();
int ReadYear();
private:	
unsigned char byte_for_DS3231(int data);
};




#endif /* DS3231_H_ */