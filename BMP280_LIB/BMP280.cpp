#include <avr/io.h>
#include <util/delay.h>
#include "BMP280.h"
#include "I2C.h"
#include "BMP280_Registers.h"
I2C BMP280_n;
//калибровочные данные температуры
void BMP280::InitPressureSensor(unsigned char Addr,int Freq_Cpu)
{
	ADDR = Addr;                     
    BMP280_n.Init(Freq_Cpu);
    BMP280_n.setBitRate(400,1);
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	BMP280_n.sendByte(config_addr);
	BMP280_n.sendByte(Config_reg);
	BMP280_n.sendByte(ctrl_meas_addr);
	BMP280_n.sendByte(Ctrl_meas_reg);
	BMP280_n.StopCondition();
	BMP280::ReadClibrationData();
}

void BMP280::ReadData(int Altitude)
{
		BMP280_n.StartCondition();
		BMP280_n.sendByte(ADDR);
		BMP280_n.sendByte(press_msb_addr);
		ADDR |= (1 << Read_Write);
		BMP280_n.StartCondition();
		BMP280_n.sendByte(ADDR);
		MSB_p = BMP280_n.ReadByte();
		LSB_p = BMP280_n.ReadByte();
		XLSB_p = BMP280_n.ReadByte();
		MSB_t = BMP280_n.ReadByte();
		LSB_t = BMP280_n.ReadByte();
		XLSB_t = BMP280_n.ReadEndByte();
		BMP280_n.StopCondition();
		ADDR &= ~(1 << Read_Write);
		MSB_t = MSB_t << 16;
		LSB_t = LSB_t << 8;
		MSB_p = MSB_p << 16;
		LSB_p = LSB_p << 8;
		BMP280_Pres = MSB_p | LSB_p;
		BMP280_Pres = BMP280_Pres | XLSB_p;
		BMP280_Pres = BMP280_Pres >> 4;
		BMP280_Temp = MSB_t | LSB_t;
		BMP280_Temp = BMP280_Temp | XLSB_t;
		BMP280_Temp = BMP280_Temp >> 4;
		var1 = (BMP280_Temp / 16384.0 - Calibration_dig_T1/1024) * Calibration_dig_T2;
		var2 = ((BMP280_Temp / 131072.0 - Calibration_dig_T1 / 8192.0) * (BMP280_Temp / 131072.0 - Calibration_dig_T1 / 8192.0)) * Calibration_dig_T3;
		t_fine = (var1 + var2);
		T = (t_fine / 5120.0);
		var1 = 0; var2 = 0; p = 0;
		var1 = (t_fine / 2.0) - 64000.0;
		var2 = var1 * var1 * Calibration_dig_P6 / 32768.0;
		var2 = var2 + var1 * Calibration_dig_P5 * 2.0;
		var2 = (var2 / 4.0) + (Calibration_dig_P4 * 65536.0);
		var1 = (dig_P3 * var1 * var1 / 524288.0 + Calibration_dig_P2 * var1) / 524288.0;
		var1 = (1.0 + var1 / 32768.0) * Calibration_dig_P1;
		p = 1048576.0 - BMP280_Pres;
		p = (p - (var2 / 4096.0)) * 6250.0 / var1;
		var1 = Calibration_dig_P9 * p * p / 2147483648.0;
		var2 = p * Calibration_dig_P8 / 32768.0;
		P = p + (var1 + var2 + Calibration_dig_P7) / 16;
		P = P * _Altitude_Compensation;
}

void BMP280::ReadData()
{
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	BMP280_n.sendByte(press_msb_addr);
	ADDR |= (1 << Read_Write);
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	MSB_p = BMP280_n.ReadByte();
	LSB_p = BMP280_n.ReadByte();
	XLSB_p = BMP280_n.ReadByte();
	MSB_t = BMP280_n.ReadByte();
	LSB_t = BMP280_n.ReadByte();
	XLSB_t = BMP280_n.ReadEndByte();
	BMP280_n.StopCondition();
	ADDR &= ~(1 << Read_Write);
	MSB_t = MSB_t << 16;
	LSB_t = LSB_t << 8;
	MSB_p = MSB_p << 16;
	LSB_p = LSB_p << 8;
	BMP280_Pres = MSB_p | LSB_p;
	BMP280_Pres = BMP280_Pres | XLSB_p;
	BMP280_Pres = BMP280_Pres >> 4;
	BMP280_Temp = MSB_t | LSB_t;
	BMP280_Temp = BMP280_Temp | XLSB_t;
	BMP280_Temp = BMP280_Temp >> 4;
	var1 = (BMP280_Temp / 16384.0 - Calibration_dig_T1/1024) * Calibration_dig_T2;
	var2 = ((BMP280_Temp / 131072.0 - Calibration_dig_T1 / 8192.0) * (BMP280_Temp / 131072.0 - Calibration_dig_T1 / 8192.0)) * Calibration_dig_T3;
	t_fine = (var1 + var2);
	T = (t_fine / 5120.0);
	var1 = 0; var2 = 0; p = 0;
	var1 = (t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * Calibration_dig_P6 / 32768.0;
	var2 = var2 + var1 * Calibration_dig_P5 * 2.0;
	var2 = (var2 / 4.0) + (Calibration_dig_P4 * 65536.0);
	var1 = (dig_P3 * var1 * var1 / 524288.0 + Calibration_dig_P2 * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * Calibration_dig_P1;
	p = 1048576.0 - BMP280_Pres;
	p = (p - (var2 / 4096.0)) * 6250.0 / var1;
	var1 = Calibration_dig_P9 * p * p / 2147483648.0;
	var2 = p * Calibration_dig_P8 / 32768.0;
	P = p + (var1 + var2 + Calibration_dig_P7) / 16;
	P += Compensation_Pressure;
}

void BMP280::ReadClibrationData()
{
	short LSB_cal,MSB_cal,var;
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	BMP280_n.sendByte(dig_T1);
	ADDR |= (1 << 0);
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	Calibration_dig_T1 = (MSB_cal << 8) | LSB_cal;
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_T2 = -((65535 - var) + 1);
	} 
	else
	{
		Calibration_dig_T2 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_T3 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_T3 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	Calibration_dig_P1 = (MSB_cal << 8) | LSB_cal;
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P2 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P2 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P3 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P3 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P4 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P4 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P5 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P5 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P6 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P6 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P7 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P7 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P8 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P8 = var;
	}
	LSB_cal = BMP280_n.ReadByte();
	MSB_cal= BMP280_n.ReadByte();
	var = (MSB_cal << 8) | LSB_cal;
	if (var - 1 >= 0x7FFF)
	{
		Calibration_dig_P9 = -((65535 - var) + 1);
	}
	else
	{
		Calibration_dig_P9 = var;
	}
}

double BMP280::GetTemperatureC()
{ 
    return T;
}

double BMP280::GetTemperatureF()
{
	return T * 33.8;
}

double BMP280::GetTemperatureK()
{
	return T * 274.15;
}

double BMP280::GetPressurekPa()
{
	return P / 1000;
}

double BMP280::GetPressureAtmosphere()
{
	return P / 98066;
}

double BMP280::GetPressureMM()
{
	return P / 133.3224;
}

double BMP280::GetAltitude()
{
	double Temp;
	Temp = P / 101325;
	Temp = 1 - pow(Temp, 0.19029);
	Altitude = 44330 * Temp;
	return Altitude;
}

short BMP280::readByte(unsigned char Registr)
{
	short Val; 
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	BMP280_n.sendByte(Registr);
	BMP280_n.StartCondition();
	ADDR |= (1 << Read_Write);
	BMP280_n.sendByte(ADDR);
	Val	= BMP280_n.ReadEndByte();
	BMP280_n.StopCondition();
	ADDR &= ~(1 << Read_Write);
	return Val;
}

bool BMP280::checkStatusRegister()
{
	switch (BMP280::readByte(status_addr))
	{
	case 0:
	return true;
	break;
	case 1:
	return true;
	break;
	case 8:
	return true;
	break;
	case 9:
	return true;
	break;
	default:
	return false;
	break;
	}
}

void BMP280::setSettings()
{
	BMP280_n.StartCondition();
	BMP280_n.sendByte(ADDR);
	BMP280_n.sendByte(config_addr);
	BMP280_n.sendByte(Config_reg);
	BMP280_n.sendByte(ctrl_meas_addr);
	BMP280_n.sendByte(Ctrl_meas_reg);
}

void BMP280::SetFrequencyMeas(uint8_t Freq)
{
	switch (Freq)
	{
	case 0:
	Config_reg &= ~((1 << Config_t_sb_0) | (1 << Config_t_sb_1) | (1 << Config_t_sb_2));
    break;
	case 1:
	Config_reg &= ~((1 << Config_t_sb_2) | (1 << Config_t_sb_1));
	Config_reg |= (1 << Config_t_sb_0);
	break;
	case 2:
	Config_reg &= ~((1 << Config_t_sb_2) | (1 << Config_t_sb_0));
	Config_reg |= (1 << Config_t_sb_1);
	break;
	case 3:
	Config_reg &= ~(1 << Config_t_sb_2);
	Config_reg |= (1 << Config_t_sb_0) | (1 << Config_t_sb_1);
	break;
	case 4:
	Config_reg |= (1 << Config_t_sb_2);
	Config_reg &= ~((1 << Config_t_sb_1) | (1 << Config_t_sb_0));
	break;
	case 5: 
	Config_reg |= (1 << Config_t_sb_2) | (1 << Config_t_sb_0);
	Config_reg &= (1 << Config_t_sb_1);
	break;
	case 6:
	Config_reg |= (1 << Config_t_sb_2) | (1 << Config_t_sb_1);
	Config_reg &= ~(1 << Config_t_sb_0);
	break;
	case 7:
	Config_reg |= (1 << Config_t_sb_0) | (1 << Config_t_sb_1) | (1 << Config_t_sb_2);
	break;
	}
	BMP280::setSettings();
}

void BMP280::SetPowerMode(uint8_t PM)
{
	switch (PM)
	{
	case 0:
	Ctrl_meas_reg &= ~((1 << Ctrl_Meas_mode_1) | (1 << Ctrl_Meas_mode_0));
	break;
	case 1:
	Ctrl_meas_reg |= (1 << Ctrl_Meas_mode_0);
	Ctrl_meas_reg &= ~(1 << Ctrl_Meas_mode_1);
	break;
	case 2:
	Ctrl_meas_reg |= ((1 << Ctrl_Meas_mode_0) | (1 <<  Ctrl_Meas_mode_1));
	break;
	}
	BMP280::setSettings();
}

void BMP280::SetResolutionPressure(uint8_t ResolutionPressure)
{
	switch (ResolutionPressure)
	{
	case 0:
	Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_p_2) | (1 << Ctrl_Meas_osrs_p_1) | (1 << Ctrl_Meas_osrs_p_0));
    break;
	case 1:
	Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_p_2) | (1 << Ctrl_Meas_osrs_p_1));
	Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_p_0);
	break;
	case 2:
	Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_p_2) | (1 << Ctrl_Meas_osrs_p_0));
	Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_p_1);
	break;
	case 3:
	Ctrl_meas_reg &= ~(1 << Ctrl_Meas_osrs_p_2);
	Ctrl_meas_reg |= ((1 << Ctrl_Meas_osrs_p_1) | (1 << Ctrl_Meas_osrs_p_0));
	break;
	case 4:
	Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_p_1) | (1 << Ctrl_Meas_osrs_p_0));
	Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_p_2);
	break;
	case 5:
	Ctrl_meas_reg &= ~(1 << Ctrl_Meas_osrs_p_1);
	Ctrl_meas_reg |= ((1 << Ctrl_Meas_osrs_p_2) | (1 << Ctrl_Meas_osrs_p_0));
	break;
	}
	BMP280::setSettings();
}

void BMP280::SetResolutionTemperature(uint8_t ResolutionTemp)
{
	switch (ResolutionTemp)
	{
		case 0:
		Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_t_2) | (1 << Ctrl_Meas_osrs_t_1) | (1 << Ctrl_Meas_osrs_t_0));
		break;
		case 1:
		Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_t_2) | (1 << Ctrl_Meas_osrs_t_1));
		Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_t_0);
		break;
		case 2:
		Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_t_2) | (1 << Ctrl_Meas_osrs_t_0));
		Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_t_1);
		break;
		case 3:
		Ctrl_meas_reg &= ~(1 << Ctrl_Meas_osrs_t_2);
		Ctrl_meas_reg |= ((1 << Ctrl_Meas_osrs_t_1) | (1 << Ctrl_Meas_osrs_t_0));
		break;
		case 4:
		Ctrl_meas_reg &= ~((1 << Ctrl_Meas_osrs_t_1) | (1 << Ctrl_Meas_osrs_t_0));
		Ctrl_meas_reg |= (1 << Ctrl_Meas_osrs_t_2);
		break;
		case 5:
		Ctrl_meas_reg &= ~(1 << Ctrl_Meas_osrs_t_1);
		Ctrl_meas_reg |= ((1 << Ctrl_Meas_osrs_t_2) | (1 << Ctrl_Meas_osrs_t_0));
		break;
	}
	BMP280::setSettings();
}

void BMP280::SetFilterCoef(uint8_t CoefFilt)
{
	switch (CoefFilt)
	{
	case 0:
	Config_reg &= ~((1 << Config_filter_2) | (1 << Config_filter_1) | (Config_filter_0));
	break;
	case 1:
	Config_reg &= ~((1 << Config_filter_2) | (1 << Config_filter_0));
	Config_reg |= (1 << Config_filter_1);
	break;
	case 2:
	Config_reg &= ~(1 << Config_filter_2);
	Config_reg |= ((1 << Config_filter_1) | (1 << Config_filter_0));
	break;
	case 3:
	Config_reg &= ~((1 << Config_filter_1) | (1 << Config_filter_0));
	Config_reg |= (1 << Config_filter_2);
	break;
	case 4:
	Config_reg |= ((1 << Config_filter_2) | (1 << Config_filter_1) | (1 << Config_filter_0));
	break;
	}
	BMP280::setSettings();
}