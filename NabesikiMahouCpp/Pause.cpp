#include "GameSystem.h"

Pause::~Pause()
{
}

Pause* Pause::Instance()
{
	static Pause instance;
	return &instance;
}

void Pause::Enter(GameMain* gm)
{
	AddMenuKoumoku("tsuzukeru", &Pause::Koumoku_Tsuzukeru, 320, 300, gsTitleIns->pict_datamap["button_tsuzukeru"]);
	AddMenuKoumoku("modoru", &Pause::Koumoku_Modoru, 320, 360, gsTitleIns->pict_datamap["button_modoru"]);
	AddMenuKoumoku("yameru", &Pause::Koumoku_Yameru, 320, 420, gsTitleIns->pict_datamap["button_yameru"]);
	menu["tsuzukeru"]->down = menu["modoru"];
	menu["tsuzukeru"]->up = menu["yameru"];
	menu["modoru"]->down = menu["yameru"];
	menu["modoru"]->up = menu["tsuzukeru"];
	menu["yameru"]->down = menu["tsuzukeru"];
	menu["yameru"]->up = menu["modoru"];
	current_koumoku = menu["tsuzukeru"];
	star_deltatime = 0;
	owner_gm = gm;
}
void Pause::Execute(GameMain* gm)
{
	//項目選択
	if (InputSignalsIns->Oneshot_SW == 1)
	{
		gm->SoundManager->PlaySoundFile("cursor");
		current_koumoku = current_koumoku->down;
		KoumokuEffectOverwrite();
	}
	else if (InputSignalsIns->Oneshot_SW == -1)
	{
		gm->SoundManager->PlaySoundFile("cursor");
		current_koumoku = current_koumoku->up;
		KoumokuEffectOverwrite();
	}
	if (InputSignalsIns->Oneshot_Space == 1)
	{
		gm->SoundManager->PlaySoundFile("coin");
		int _eff = owner_gm->PlayEffekseer2DEffectByTemporaryScene(gsTitleIns->pict_datamap["button_select"]);
		SetPosPlayingEffekseer2DEffect(_eff, current_koumoku->x, current_koumoku->y, 0.0f);
		float _scale = 10.0f;
		SetScalePlayingEffekseer2DEffect(_eff, _scale, _scale, _scale);
		(this->*(current_koumoku->koumoku_method))(gm);
	}
}
void Pause::Exit(GameMain* gm)
{
	ClearMenuKoumoku();
}
void Pause::Pict(GameMain* gm)
{
	DrawGraph(0, 0, gsHonbanIns->pict_datamap["haikei_tsukue"], true);
	DrawRotaGraph(320, 130, 1.0, 0.0, gsTitleIns->pict_datamap["pause_mark"], true, false);
	//選択中の項目のエフェクト更新
	if (IsEffekseer2DEffectPlaying(playing_koumoku_eff_no) == -1)
	{
		KoumokuEffectSet();
	}

}
void Pause::UIPict(GameMain* gm)
{
	for (auto itr = menu.begin(); itr != menu.end(); ++itr)
	{
		DrawRotaGraph(itr->second->x, itr->second->y, 1.0, 0.0, itr->second->pict_no, true, false);
	}
	if (star_deltatime >= 60) star_deltatime = 0;
	DrawRotaGraph(current_koumoku->x - 90, current_koumoku->y, 1.0, 0.0, gsTitleIns->star_pict_datamap[star_deltatime], true, false);
	DrawRotaGraph(current_koumoku->x + 90, current_koumoku->y, 1.0, 0.0, gsTitleIns->star_pict_datamap[star_deltatime], true, false);
	star_deltatime++;
}

void Pause::Koumoku_Tsuzukeru(GameMain* gm)
{
	gm->BackFromMenuWithPause();
}


void Pause::Koumoku_Modoru(GameMain* gm)
{
	gm->ReturnTitleWithReset();
}


void Pause::Koumoku_Yameru(GameMain* gm)
{
	gm->game_end_flag = true;
}


void Pause::AddMenuKoumoku(string key, void(Pause::*koumoku_method)(GameMain* gm), int _x, int _y, int _pict_no)
{
	MenuKoumoku<Pause> *_koumoku = new MenuKoumoku<Pause>;
	_koumoku->key = key;
	_koumoku->x = _x;
	_koumoku->y = _y;
	_koumoku->koumoku_method = koumoku_method;
	_koumoku->pict_no = _pict_no;
	menu[key] = _koumoku;
}


void Pause::ClearMenuKoumoku()
{
	for (auto itr = menu.begin(); itr != menu.end(); ++itr)
	{
		delete itr->second;
	}
	menu.clear();
}


void Pause::KoumokuEffectOverwrite()
{
	if (IsEffekseer2DEffectPlaying(playing_koumoku_eff_no) == 0)
		SetScalePlayingEffekseer2DEffect(playing_koumoku_eff_no, 0.0f, 0.0f, 0.0f);
	KoumokuEffectSet();
}


void Pause::KoumokuEffectSet()
{
	playing_koumoku_eff_no = owner_gm->PlayEffekseer2DEffectByTemporaryScene(gsTitleIns->eff_datamap["button_selecting"]);
	SetPosPlayingEffekseer2DEffect(playing_koumoku_eff_no, current_koumoku->x, current_koumoku->y, 0.0f);
	float _scale = 40.0f;
	SetScalePlayingEffekseer2DEffect(playing_koumoku_eff_no, _scale, _scale, _scale);
}

