/*
 * PWM.cpp
 *
 * Created: 04.04.2022 20:20:34
 *  Author: Mikhail
 */ 
#include "PWM.h"
#include <avr\io.h>
PWM::PWM(uint8_t timer, bool Channel, uint8_t Devider, uint8_t Mode, uint8_t Resolution)
{
	PWM::timer_ = timer;
	PWM::Channel_ = Channel;
	PWM::SetPreDivider(Devider);
	PWM::SetMode(Mode, Resolution);
}
PWM::PWM(uint8_t timer, bool Channel, uint8_t Mode)
{
	PWM::timer_ = timer;
	PWM::Channel_ = Channel;
	PWM::SetMode(Mode);
}
PWM::PWM(uint8_t timer, bool Channel, uint8_t Mode, uint8_t Devider)
{
	PWM::timer_ = timer;
	PWM::Channel_ = Channel;
	PWM::SetMode(Mode);
	PWM::SetPreDivider(Devider);
}
void PWM::SetPreDivider(uint8_t Devider)
{
	switch (PWM::timer_)
	{
	case 0:
	switch(Devider)
	{
		case 0:
		TCCR0B |= (1 << CS00);
		TCCR0B &= ~((1 << CS01) | (1 << CS02));
		break;
		case 1:
		TCCR0B |= (1 << CS01);
		TCCR0B &= ~((1 << CS02) | (1 << CS00));
		break;
		case 2:
		TCCR0B |= (1 << CS00) | (1 << CS01);
		TCCR0B &= ~(1 << CS02);
		break;
		case 3:
		TCCR0B &= ~((1 << CS00) | (1 << CS01));
		TCCR0B |= (1 << CS02);
		break;
		case 4:
		TCCR0B |= (1 << CS02) | (1 << CS00);
		TCCR0B &= ~(1 << CS01);
		break;
		case 5:
		TCCR0B |= (1 << CS00) | (1 << CS01) | (1 << CS02);
		break;
		case 6:
		TCCR0B |= (1 << CS02) | (1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	}
    break;
	case 1:
	switch(Devider)
	{
		case 0:
		TCCR1B |= (1 << CS10);
		TCCR1B &= ~((1 << CS11) | (1 << CS12));
		break;
		case 1:
		TCCR1B |= (1 << CS11);
		TCCR1B &= ~((1 << CS12) | (1 << CS10));
		break;
		case 2:
		TCCR0B |= (1 << CS00) | (1 << CS01);
		TCCR0B &= ~(1 << CS02);
		break;
		case 3:
		TCCR1B &= ~((1 << CS10) | (1 << CS11));
		TCCR1B |= (1 << CS12);
		break;
		case 4:
		TCCR1B |= (1 << CS12) | (1 << CS10);
		TCCR1B &= ~(1 << CS11);
		break;
		case 5:
		TCCR1B |= (1 << CS10) | (1 << CS11) | (1 << CS12);
		break;
		case 6:
		TCCR1B |= (1 << CS12) | (1 << CS11);
		TCCR1B &= ~(1 << CS10);
		break;
	}
	break;
	case 0:
	switch(Devider)
	{
		case 0:
		TCCR2B |= (1 << CS20);
		TCCR2B &= ~((1 << CS21) | (1 << CS22));
		break;
		case 1:
		TCCR2B |= (1 << CS21);
		TCCR2B &= ~((1 << CS22) | (1 << CS20));
		break;
		case 2:
		TCCR2B |= (1 << CS20) | (1 << CS21);
		TCCR2B &= ~(1 << CS22);
		break;
		case 3:
		TCCR2B &= ~((1 << CS20) | (1 << CS21));
		TCCR2B |= (1 << CS22);
		break;
		case 4:
		TCCR2B |= (1 << CS22) | (1 << CS20);
		TCCR2B &= ~(1 << CS21);
		break;
		case 5:
		TCCR0B |= (1 << CS20) | (1 << CS21) | (1 << CS22);
		break;
		case 6:
		TCCR0B |= (1 << CS22) | (1 << CS21);
		TCCR0B &= ~(1 << CS20);
		break;
	}
	break;
	}
}
void PWM::SetMode(uint8_t Mode)
{
	switch (PWM::timer_)
	{
		case 0://null timer
		if(Mode)//FastPWM
		{
			TCCR0A |= ((1 << WGM01) | (1 << WGM00));
			TCCR0B &= ~(1 << WGM02);
		}
		else//PhaseCorrect PWM
		{
			TCCR0B &= ~(1 << WGM02);
			TCCR0A &= ~(1 << WGM01);
			TCCR0A |= (1 << WGM00);
		}
		break;
		case 1://one timer
		if(Mode == 1)//Fast PWM
		{
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
		}
		else if(Mode == 0)//PhaseCorrect PWM
		{
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
		}
		else //Phase and Freq correct PWM
		{
			TCCR1A &= ~((1 << WGM10) | (1 << WGM11));
			TCCR1B &= ~(1 << WGM12);
			TCCR1B |= (1 << WGM13);
		}
		break;
		case 2://two timer
		if(Mode)//FastPWM
		{
			TCCR2A |= ((1 << WGM21) | (1 << WGM20));
			TCCR2B &= ~(1 << WGM22);
		}
		else//PhaseCorrect PWM
		{
			TCCR2B &= ~(1 << WGM22);
			TCCR2A &= ~(1 << WGM21);
			TCCR2A |= (1 << WGM20);
		}
		break;
	}
}
void PWM::SetMode(uint8_t Mode, uint8_t Resolution)
{
	switch (PWM::timer_)
	{
	case 1:
	if(Mode == 1)//FastPWM
	{
		switch(Resolution)
		{
			case 0:
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			break;
			case 1:
			TCCR1A |= (1 << WGM11);
			TCCR1A &= ~(1 << WGM10);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			break;
			case 2:
			TCCR1A |= (1 << WGM10) | (1 << WGM11);
			TCCR1B |= (1 << WGM12);
			TCCR1B &= ~(1 << WGM13);
			break;
		}
	}
	else if(Mode == 0) //PhaseCorrect PWM
	{
		switch(Resolution)
		{
			case 0:
			TCCR1A |= (1 << WGM10);
			TCCR1A &= ~(1 << WGM11);
			TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
			break;
			case 1:
			TCCR1A |= (1 << WGM11);
			TCCR1A &= ~(1 << WGM10);
			TCCR1B &= ~((1 << WGM12) | (1 << WGM13));
			break;
			case 2:
			TCCR1A |= (1 << WGM10) | (1 << WGM11);
			TCCR1A &= ~((1 << WGM12) | (1 << WGM13));
			break;
		}
	}
    break;
	}
}
void PWM::enable()
{
	switch (PWM::timer_)
	{
	case 0://null timer
	if (PWM::Channel_ == 0)
	{
		DDRD |= (1 << PORTD6);
		TCCR0A |= (1 << COM0A1);
		TCCR0A &= ~(1 << COM0A0);
	}
	else
	{
		DDRD |= (1 << PORTD5);
		TCCR0A |= (1 << COM0B1);
		TCCR0A &= ~(1 << COM0B0);
	}
	break;
	case 1://timer one
	if (PWM::Channel_ == 0)
	{
		DDRB |= (1 << PORTB1);
		TCCR1A |= (1 << COM1A1);
		TCCR1A &= ~(1 << COM1A0);
	}
	else
	{
	    DDRB |= (1 << PORTB2);
		TCCR1A |= (1 << COM1B1);
		TCCR1A &= ~(1 << COM1B0);
	}
	break;
	case 2:
	if (PWM::Channel_ == 0)
	{
		DDRB |= (1 << PORTB3);
		TCCR2A |= (1 << COM2A1);
		TCCR2A &= ~(1 << COM2A0);
	}
	else
	{
		DDRD |= (1 << PORTB3);
		TCCR2A |= (1 << COM2B1);
		TCCR2A &= ~(1 << COM2B0);
	}
	break;
	}
}
void PWM::disable()
{
	switch (PWM::timer_)
	{
		case 0:
		if (PWM::Channel_ == 0)TCCR0A &= ~((1 << COM0A0) | (1 << COM0A1));
		else TCCR0A &= ~((1 << COM0B0) | (1 << COM0B1));
		break;
		case 1:
		if(PWM::Channel_==0)TCCR1A &= ~((1 << COM1A0) | (1 << COM1A1));
		else TCCR1A &= ~((1 << COM1B0) | (1 << COM1B1));
		break;
		case 2:
		if(PWM::Channel_==0)TCCR2A &= ~((1 << COM2A0) | (1 << COM2A1));
		else TCCR2A &= ~((1 << COM2B0) | (1 << COM2B1));
		break;
	}
}
void PWM::setPWM(int pwm)
{
	switch(PWM::timer_)
	{
		case 0:
		if(PWM::Channel_ == 0)OCR0A = pwm;
		else OCR0B = pwm;
		break;
		case 1:
		if(PWM::Channel_ == 0)OCR1A = pwm;
		else OCR1B = pwm;
		break;
		case 1:
		if(PWM::Channel_ == 0)OCR2A = pwm;
		else OCR2B = pwm;
		break;
	}
}