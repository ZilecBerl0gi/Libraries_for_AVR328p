/*
 * BMP280.h
 *
 * Created: 15.09.2021 0:13:37
 *  Author: Михаил
 */ 


#include "BMP280_ForUser_Registers.h"
#ifndef BMP280_H_
#define BMP280_H_
class BMP280
{
public:
void InitPressureSensor(unsigned char Addr, int Freq_Cpu);
void SetSpecialSettings(bool useFilter, uint8_t Frequency, uint8_t PowerMode, uint8_t Resolution, uint8_t ResolutionTemp, uint8_t CoefFilter, int MS);//установка специальных настроек. подробно читать в документации.
void SetFrequencyMeas(uint8_t Freq);
void SetPowerMode(uint8_t PM); // 
void SetResolutionPressure(uint8_t ResolutionPressure);
void SetResolutionTemperature(uint8_t ResolutionTemp);
void SetFilterCoef(uint8_t CoefFilt);
void SetTimeStandby(int MS);
//----------------------------------------------------------------
void ReadData();
void ReadData(int Altitude);
double GetTemperatureC();
double GetTemperatureF();
double GetTemperatureK();
double GetPressurekPa();
double GetPressureAtmosphere();
double GetPressureMM();
double GetAltitude();
private:
#define _Altitude_Compensation 1.016
void ReadClibrationData();
void setSettings();
bool checkStatusRegister();
short readByte(unsigned char Registr);
unsigned char ADDR = 0;
unsigned char Config_reg = 0;//конфигурационный регистр-буфер
unsigned char Ctrl_meas_reg = 0;//контрольно-измерительный регистр-буфер
double Pressure = 0;
double Temperature = 0;
unsigned short Calibration_dig_T1;
short Calibration_dig_T2;
short Calibration_dig_T3;
//калибровочные данные давления
unsigned short Calibration_dig_P1;
short Calibration_dig_P2;
short Calibration_dig_P3;
short Calibration_dig_P4;
short Calibration_dig_P5;
short Calibration_dig_P6;
short Calibration_dig_P7;
short Calibration_dig_P8;
short Calibration_dig_P9;
//переменные для работы с температурой и давлением
int32_t BMP280_Temp,BMP280_Pres;
double var1, var2, T, p, P;
int32_t  t_fine;
int32_t MSB_t,LSB_t,XLSB_t,MSB_p,LSB_p,XLSB_p;
double Compensation;
int Alt_comp;
double Altitude;
int b = 0;
const uint8_t u = 29;//молярная масса воздуха
const double R = 8.31;//Универсальная газовая постоянная
const double g = 9.81;
};
#endif /* BMP280_H_ */