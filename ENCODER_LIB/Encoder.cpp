#include "Encoder.h"
#include <avr/io.h>
int _clk,_sw,_dt,_clk_port,_dt_port,_sw_port;
int encoder_value_, DEBOUNCE, nt_, ft_;
int hd_, bd_;
bool encoder_switch_;
bool encoder_switch_hold;
bool th_;
int toe_;
ENCODER::ENCODER(int CLK, int DT, int SW, int PORT, int TYPE_OF_ENCODER, int _DEBOUNCE,  int BUTTON_DEBOUNCE, int NORMAL_TURN, int FAST_TURN, int HOLD_DEBOUNCE)
{
	switch (PORT)
	{
	case 0:
	PORTB &= ~((1 << CLK) | (1 << DT) | (1 << SW));
	break;
	case 1:
	PORTC &= ~((1 << CLK) | (1 << DT) | (1 << SW));
	break;
	case 2:
	PORTD &= ~((1 << CLK) | (1 << DT) | (1 << SW));
	break;
	}
	_clk = CLK; _dt = DT; _sw = SW; _clk_port = PORT; _dt_port = PORT; _sw_port = PORT;
	DEBOUNCE = _DEBOUNCE;
	nt_ = NORMAL_TURN;
	ft_ = FAST_TURN;
	hd_ = HOLD_DEBOUNCE;
	bd_ = BUTTON_DEBOUNCE;
	toe_ = TYPE_OF_ENCODER;
}

ENCODER::ENCODER(int CLK, int DT, int SW, int CLK_PORT, int DT_PORT, int SW_PORT, int TYPE_OF_ENCODER, int _DEBOUNCE,   int BUTTON_DEBOUNCE, int NORMAL_TURN, int FAST_TURN, int HOLD_DEBOUNCE)
{
	switch (CLK_PORT)
	{
		case 0:
		PORTB &= ~(1 << CLK);
		break;
		case 1:
		PORTC &= ~(1 << CLK);
		break;
		case 2:
		PORTD &= ~(1 << CLK);
		break;
	}
	switch (DT_PORT)
	{
		case 0:
		PORTB &= ~(1 << DT);
		break;
		case 1:
		PORTC &= ~(1 <<  DT);
		break;
		case 2:
		PORTD &= ~(1 <<  DT);
		break;
	}
	switch (SW_PORT)
	{
		case 0:
		PORTB &= ~(1 << SW);
		break;
		case 1:
		PORTC &= ~(1 << SW);
		break;
		case 2:
		PORTD &= ~(1 << SW);
		break;
	}
	DEBOUNCE = _DEBOUNCE;
	_clk = CLK; _dt = DT; _sw = SW; _clk_port = CLK_PORT; _dt_port = DT_PORT; _sw_port = SW_PORT;
	nt_ = NORMAL_TURN;
	ft_ = FAST_TURN;
	hd_ = HOLD_DEBOUNCE;
	bd_ = BUTTON_DEBOUNCE;
	toe_ = TYPE_OF_ENCODER;
}

bool ENCODER::read_clk()
{
	switch (_clk_port)
	{
	case B:
	return PINB & (1 << _clk);
	break;
	case C:
	return PINC & (1 << _clk);
	break;
	case D:
	return PIND & (1 << _clk);
	break;
	}
}

bool ENCODER::read_dt()
{
	switch (_dt_port)
	{
		case B:
		return PINB & (1 << _dt);
		break;
		case C:
		return PINC & (1 << _dt);
		break;
		case D:
		return PIND & (1 << _dt);
		break;
	}
}

bool ENCODER::read_sw()
{
	switch (_sw_port)
	{
		case B:
		return PINB & (1 << _sw);
		break;
		case C:
		return PINC & (1 << _sw);
		break;
		case D:
		return PIND & (1 << _sw);
		break;
	}
}

void ENCODER::tick()
{
	int _val_clk = 0, _val_dt = 0;
	int _val_sw = 0;
    while (ENCODER::read_clk())
	{
	_val_clk += ENCODER::read_clk();
	for (int i = 0; i < 50 ;i++)asm("nop");
	}
	if(_val_clk > 0)
	{
		while(ENCODER::read_dt())_val_dt += ENCODER::read_dt();
	}
	if(_val_dt > DEBOUNCE * toe_ && _val_clk > DEBOUNCE * toe_)encoder_value_ = nt_;
	else if(_val_dt == 0 && _val_clk > DEBOUNCE * toe_)encoder_value_ = (-1) * nt_;
	else if(_val_dt > DEBOUNCE * toe_ && _val_clk > (DEBOUNCE - (DEBOUNCE - (DEBOUNCE / 1.6))) * toe_)encoder_value_ = ft_;
	else if(_val_dt == 0 && _val_clk > (DEBOUNCE - (DEBOUNCE - (DEBOUNCE / 1.6))) * toe_)encoder_value_ = (-1) * ft_;
	else encoder_value_ = 0;
	bool error = 0;
	while (ENCODER::read_sw() && _val_sw <= hd_)
	{
		_val_sw += ENCODER::read_sw();
		for (int i = 0; i < 150 ;i++)
		{
			asm("nop");
			if(ENCODER::read_clk() || ENCODER::read_dt())error = true;
			}
		    if(ENCODER::read_clk() || ENCODER::read_dt() || error)break;
		}
	if(_val_sw >= hd_ && error == false && encoder_value_ == 0)encoder_switch_hold = 1;
	else encoder_switch_hold = 0;
	if(_val_sw >= bd_ && _val_sw < hd_ && error == false && encoder_value_ == 0)encoder_switch_ = 1;
	else encoder_switch_ = 0;
	if(_val_sw > 0 && (encoder_value_ != 0))th_ = true;
	else th_ = false;
}

bool ENCODER::Button()
{
	return encoder_switch_;
}

bool ENCODER::ButtonHold()
{
	return encoder_switch_hold;
}

int ENCODER::Turn()
{
	return encoder_value_;
}

bool ENCODER::TurnHold()
{
	return th_;
}