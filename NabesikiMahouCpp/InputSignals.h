#pragma once

#define InputSignalsIns InputSignals::GetInstance()
class InputSignals
{
public:

	~InputSignals(); 
	//property
	int Input_DA, Input_SW;
	int Input_RightLeft, Input_DownUp;
	int Input_Space;
	int Input_P;
	__declspec(property(get = GetOneshot_DA)) int Oneshot_DA;
	__declspec(property(get = GetOneshot_SW)) int Oneshot_SW;
	__declspec(property(get = GetOneshot_RightLeft)) int Oneshot_RightLeft;
	__declspec(property(get = GetInput_DownUp)) int Oneshot_DownUp;
	__declspec(property(get = GetOneshot_Space)) int Oneshot_Space;
	static InputSignals* GetInstance();
	int GetOneshot_DA();
	int GetOneshot_SW();
	int GetOneshot_RightLeft();
	int GetOneshot_DownUp();

	//method
	void InputCheck();
	void ResetAllInputSignal();
	
private:
	InputSignals();

	int key_w, key_a, key_s, key_d;
	int key_up, key_left, key_down, key_right;
	int oneshot_DA, oneshot_SW;
	int oneshot_RightLeft, oneshot_DownUp;
	int oneshot_space;
	int backbuf_space;

	//method
	// neg and pos are only 0 to 1
	void DecideTwoInput(int negative_i, int positive_i, int* input_signal, int* oneshot_signal);

	InputSignals(const InputSignals &);
	InputSignals& operator=(const InputSignals &);
public:
	int GetOneshot_Space();
	int CheckOneInputOneshot(int input, int oneshot, int backbuf);
};

