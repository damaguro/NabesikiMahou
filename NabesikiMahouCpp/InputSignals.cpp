#include <mutex>
#include "InputSignals.h"
#include "DxLib.h"


InputSignals::InputSignals()
{
}


InputSignals::~InputSignals()
{
}

//property getter
int InputSignals::GetOneshot_DA()
{
	return oneshot_DA;
}
int InputSignals::GetOneshot_SW()
{
	return oneshot_SW;
}
int InputSignals::GetOneshot_RightLeft()
{
	return oneshot_RightLeft;
}

int InputSignals::GetOneshot_DownUp()
{
	return oneshot_DownUp;
}

int InputSignals::GetOneshot_Space()
{
	return oneshot_space;
}


//public method
void InputSignals::InputCheck()
{
	key_w = CheckHitKey(KEY_INPUT_W);
	key_a = CheckHitKey(KEY_INPUT_A);
	key_s = CheckHitKey(KEY_INPUT_S);
	key_d = CheckHitKey(KEY_INPUT_D);

	key_up = CheckHitKey(KEY_INPUT_UP);
	key_left = CheckHitKey(KEY_INPUT_LEFT);
	key_down = CheckHitKey(KEY_INPUT_DOWN);
	key_right = CheckHitKey(KEY_INPUT_RIGHT);
	backbuf_space = Input_Space;
	Input_Space = CheckHitKey(KEY_INPUT_SPACE);
	Input_P = CheckHitKey(KEY_INPUT_P);

	DecideTwoInput(key_a, key_d, &Input_DA, &oneshot_DA);
	DecideTwoInput(key_w, key_s, &Input_SW, &oneshot_SW);

	DecideTwoInput(key_left, key_right, &Input_RightLeft, &oneshot_RightLeft);
	DecideTwoInput(key_up, key_down, &Input_DownUp, &oneshot_DownUp);

	oneshot_space = CheckOneInputOneshot(Input_Space, oneshot_space, backbuf_space);
}

void InputSignals::ResetAllInputSignal()
{
	Input_DA = 0;
	Input_SW = 0;
	Input_RightLeft = 0;
	Input_DownUp = 0;
	Input_Space = 0;
	Input_P = 0;
	oneshot_DA = 0;
	oneshot_SW = 0;
	oneshot_DownUp = 0;
	oneshot_RightLeft = 0;
	oneshot_space = 0;
}

//private method
// neg and pos are only 0 to 1
void InputSignals::DecideTwoInput(int negative_i, int positive_i, int* input_signal, int* oneshot_signal)
{
	*oneshot_signal = 0;
	int backbuf_signal = *input_signal;
	if (negative_i + positive_i != 2)
	{
		if (negative_i == 1)
		{
			*input_signal = -1;
		}
		else if (positive_i == 1)
		{
			*input_signal = 1;
		}
		else
		{
			*input_signal = 0;
		}
	}
	if (*input_signal != backbuf_signal)
	{
		*oneshot_signal = *input_signal;
	}
}

InputSignals* InputSignals::GetInstance()
{
	static InputSignals _instance;
	return &_instance;
}


int InputSignals::CheckOneInputOneshot(int input, int oneshot, int backbuf)
{/*
http://dixq.net/g/02_09.html
	ÇéQçlÇ…ÇÊÇËå´Ç¢ä÷êîÇçÏÇÈÇ◊Ç´*/
	if (backbuf != input && input == 1)
		oneshot = 1;
	else
		oneshot = 0;
	return oneshot;
}
