/*
 * Registers.h
 *
 * Created: 15.09.2021 13:51:15
 *  Author: Михаил
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_
#define Read_Write 0
//биты смещения для конфигурации
#define Config_t_sb_2 7
#define Config_t_sb_1 6
#define Config_t_sb_0 5
#define Config_filter_2 4
#define Config_filter_1 3
#define Config_filter_0 2
#define Config_no_use 1
#define Config_spi3w_en 0
//биты смещения для контрольно-измеретильного регистра
#define Ctrl_Meas_osrs_t_2 7
#define Ctrl_Meas_osrs_t_1 6
#define Ctrl_Meas_osrs_t_0 5
#define Ctrl_Meas_osrs_p_2 4
#define Ctrl_Meas_osrs_p_1 3
#define Ctrl_Meas_osrs_p_0 2
#define Ctrl_Meas_mode_1 1
#define Ctrl_Meas_mode_0 0
//адреса глобальной карты памяти
#define temp_xlsb_addr 0xFC
#define temp_lsb_addr 0xFB
#define temp_msb_addr 0xFA
#define press_xlsb_addr 0xF9
#define press_lsb_addr 0xF8
#define press_msb_addr 0xF7
#define config_addr 0xF5
#define ctrl_meas_addr 0xF4
#define status_addr 0xF3
#define reset_addr 0xE0
#define id_addr 0xD0
//адреса калибровочных значений
#define dig_T1 0x88
#define dig_T2 0x8A
#define dig_T3 0x8C
#define dig_P1 0x8E
#define dig_P2 0x90
#define dig_P3 0x92
#define dig_P4 0x94
#define dig_P5 0x96
#define dig_P6 0x98
#define dig_P7 0x9A
#define dig_P8 0x9C
#define dig_P9 0x9E

#endif /* REGISTERS_H_ */