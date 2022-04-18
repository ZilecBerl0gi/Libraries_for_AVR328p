/*
 * Encoder.h
 *
 * Created: 17.01.2022 22:39:54
 *  Author: Михаил
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_
#define B 0
#define C 1
#define D 2
#define ONE_TICK_ENCODER 1
#define TWO_TICK_ENCODER 2
class ENCODER
{
	public:
	ENCODER(int CLK, int DT, int SW, int PORT, int TYPE_OF_ENCODER, int _DEBOUNCE,  int BUTTON_DEBOUNCE, int NORMAL_TURN, int FAST_TURN, int HOLD_DEBOUNCE);//
	ENCODER(int CLK, int DT, int SW, int CLK_PORT, int DT_PORT, int SW_PORT, int TYPE_OF_ENCODER, int _DEBOUNCE,   int BUTTON_DEBOUNCE, int NORMAL_TURN, int FAST_TURN, int HOLD_DEBOUNCE);
	void tick();
	bool Button();
	bool ButtonHold();
	bool TurnHold();
	int  Turn();
	private:
		bool read_clk();
		bool read_sw();
		bool read_dt();
};
#endif /* ENCODER_H_ */