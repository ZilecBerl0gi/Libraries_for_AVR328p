/*
 * PWM.h
 *
 * Created: 04.04.2022 20:20:18
 *  Author: Mikhail
 */ 


#ifndef PWM_H_
#define PWM_H_
#include <stdint.h>
#define Timer0 0
#define Timer1 1
#define Timer2 2
#define TimerA 0
#define TimerB 1
#define PhaseCorrect 0
#define FAST_PWM 1
#define PhaseAndFrequencyCorrect 2
#define Res10BIT 2
#define Res9BIT 1
#define Res8BIT 0
#define PreD1 0
#define PreD8 1
#define PreD64 2
#define PreD256 3
#define PreD1024 4
#define ExternalClockRise 5
#define ExternalClockFall 6
class PWM
{
public:
PWM(uint8_t timer, bool Channel, uint8_t Devider, uint8_t Mode, uint8_t Resolution);
PWM(uint8_t timer, bool Channel, uint8_t Mode);
PWM(uint8_t timer, bool Channel, uint8_t Mode, uint8_t Devider);
void SetPreDivider(uint8_t Devider);
void SetMode(uint8_t Mode, uint8_t Resolution);
void SetMode(uint8_t Mode);
void enable();
void disable();
void setPWM(int pwm);
private:
uint8_t timer_;
bool Channel_;
uint8_t mode_;
};


#endif /* PWM_H_ */