#pragma once
#include <map>
#include "DxLib.h"

using namespace std;

#define TsuSoundManagerIns TsuSoundManager::Instance()

class TsuSoundManager
{
public:
	TsuSoundManager();
	~TsuSoundManager();
private:
	map<string, int> sound_handle_datamap;

public:
	void LoadSoundFile(TCHAR* FileName, TCHAR* key);
	void PlaySoundFile(TCHAR* key);
	void NabeSoundLoad();
	int GetSoundHandle(TCHAR* key);
	void AllSoundStop();
	void PlayBGM026();
private:
	map<string, int> bgm_handle_datamap;
public:
	void LoadBGMFile(TCHAR* FileName, TCHAR* key);
};

