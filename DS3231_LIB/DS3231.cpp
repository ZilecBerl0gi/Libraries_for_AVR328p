#include "DS3231.h"
#include "I2C.h"
#include <avr/io.h>
#include <util/delay.h>
I2C ds3231_n;
DS3231::DS3231(int _FREQ)
{
	ds3231_n.Init(_FREQ);
	ds3231_n.setBitRate(400,1);
}

unsigned char DS3231::byte_for_DS3231(int data)
{
	uint8_t count = 0;
	while(data > 9)
	{
		data -= 10;
		count++;
	}
	return(data | (count << 4));
}

void DS3231::SetTime(int Seconds, int Minutes, int Hours)
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x00);
	ds3231_n.sendByte(DS3231::byte_for_DS3231(Hours));
	ds3231_n.sendByte(DS3231::byte_for_DS3231(Minutes));
	ds3231_n.sendByte(DS3231::byte_for_DS3231(Seconds));
	ds3231_n.StopCondition();
}

void DS3231::SetDate(int Day_Of_Week, int Day_Of_Month, int Month, int Year)
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x03);
		ds3231_n.sendByte(DS3231::byte_for_DS3231(Day_Of_Week));
		ds3231_n.sendByte(DS3231::byte_for_DS3231(Day_Of_Month));
		ds3231_n.sendByte(DS3231::byte_for_DS3231(Month));
		ds3231_n.sendByte(DS3231::byte_for_DS3231(Year));
		ds3231_n.StopCondition();
}

int DS3231::ReadSeconds()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x00);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadMinutes()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x01);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadHours()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x02);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadDayOfTheWeek()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x03);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadDayOfMonth()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x04);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadMonth()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x05);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}

int DS3231::ReadYear()
{
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD0);
	ds3231_n.sendByte(0x06);
	ds3231_n.StartCondition();
	ds3231_n.sendByte(0xD1);
	unsigned char secb = ds3231_n.ReadEndByte();
	ds3231_n.StopCondition();
	int sec = ((secb&0x0F) + ((secb >> 4) * 10));
	return sec;
}