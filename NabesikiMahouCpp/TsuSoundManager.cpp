#include "TsuSoundManager.h"

TsuSoundManager::TsuSoundManager()
{
	
}

TsuSoundManager::~TsuSoundManager()
{
	int i = 1;
}


void TsuSoundManager::LoadSoundFile(TCHAR* FileName, TCHAR* key)
{
	sound_handle_datamap[key] = LoadSoundMem(FileName);
}


void TsuSoundManager::PlaySoundFile(TCHAR* key)
{
	PlaySoundMem(sound_handle_datamap[key], DX_PLAYTYPE_BACK);
}

//仮　一斉ロード
void TsuSoundManager::NabeSoundLoad()
{
	LoadSoundFile("Data/sound/magic-ice01.mp3", "ice01");
	LoadSoundFile("Data/sound/arrow01.wav", "arrow");
	LoadSoundFile("Data/sound/beep08.wav", "beep");
	LoadSoundFile("Data/sound/bom34.wav", "bomb34");
	LoadSoundFile("Data/sound/bomb2.mp3", "bomb2");
	LoadSoundFile("Data/sound/coin01.wav", "coin");
	LoadSoundFile("Data/sound/cursor19.wav", "cursor");
	LoadSoundFile("Data/sound/fire_01_pachipachi.mp3", "pachipachi");
	LoadSoundFile("Data/sound/fire_loop.mp3", "fire");
	LoadSoundFile("Data/sound/MegaFIRE4.wav", "fire4");
	LoadSoundFile("Data/sound/SF_feel6.wav", "sf_feel6");
	LoadSoundFile("Data/sound/tm2_bom002.wav", "bomb2t");
	LoadSoundFile("Data/sound/tm2_bone000.wav", "bone");
	LoadSoundFile("Data/sound/tm2_shoot000.wav", "shoot000");
	LoadSoundFile("Data/sound/tm2_shoot002.wav", "shoot");
	LoadSoundFile("Data/sound/water01.mp3", "water01");
	LoadSoundFile("Data/sound/電撃.wav", "thunder");
	LoadBGMFile("Data/sound/BGM026.ogg", "BGM026");
}


int TsuSoundManager::GetSoundHandle(TCHAR* key)
{
	return sound_handle_datamap[key];
}


void TsuSoundManager::AllSoundStop()
{
	map<string, int>::iterator it = sound_handle_datamap.begin();
	while (it != sound_handle_datamap.end())
	{
		StopSoundMem(it->second);
		++it;
	}
}


void TsuSoundManager::PlayBGM026()
{
	PlaySoundMem(bgm_handle_datamap["BGM026"], DX_PLAYTYPE_LOOP);
}


void TsuSoundManager::LoadBGMFile(TCHAR* FileName, TCHAR* key)
{
	bgm_handle_datamap[key] = LoadSoundMem(FileName);
}
