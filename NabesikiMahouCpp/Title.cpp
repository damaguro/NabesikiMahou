#include "GameSystem.h"


Title* Title::Instance()
{
	static Title title;
	return &title;
}


Title::~Title()
{
}

void Title::Enter(GameMain* gm)
{
	if (gm->title_data_load_flag == false)
	{
		pict_datamap["button_hajimeru"] = LoadGraph("Data/picture/button_hajimeru.png");
		pict_datamap["button_tsuzukeru"] = LoadGraph("Data/picture/button_tsuzukeru.png");
		pict_datamap["button_yameru"] = LoadGraph("Data/picture/button_yameru.png");
		pict_datamap["button_modoru"] = LoadGraph("Data/picture/button_modoru.png");
		pict_datamap["title"] = LoadGraph("Data/picture/title.png");
		pict_datamap["pause_mark"] = LoadGraph("Data/picture/pause_mark.png");
		eff_datamap["button_select"] = LoadEffekseerEffect("Data/effect/button_select.efk");
		eff_datamap["button_selecting"] = LoadEffekseerEffect("Data/effect/button_selecting.efk");
		star_wid = 32; star_hei = 32;
		LoadDivGraph("Data/picture/star_rotate.png", 60, 10, 6, star_wid, star_hei, star_pict_datamap);
		gm->title_data_load_flag = true;
	}
	AddMenuKoumoku("hajimeru", &Title:: Koumoku_Hajimeru, 120, 370, pict_datamap["button_hajimeru"]);
	AddMenuKoumoku("yameru", &Title::Koumoku_Yameru, 120, 450, pict_datamap["button_yameru"]);
	menu["hajimeru"]->down = menu["yameru"];
	menu["hajimeru"]->up = menu["yameru"];
	menu["yameru"]->down = menu["hajimeru"];
	menu["yameru"]->up = menu["hajimeru"];
	current_koumoku = menu["hajimeru"];
	star_deltatime = 0;
}


void Title::Execute(GameMain* gm)
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
		int _eff = PlayEffekseer2DEffect(pict_datamap["button_select"]);
		SetPosPlayingEffekseer2DEffect(_eff, current_koumoku->x, current_koumoku->y, 0.0f);
		float _scale = 10.0f;
		SetScalePlayingEffekseer2DEffect(_eff, _scale, _scale, _scale);
		(this->*(current_koumoku->koumoku_method))(gm);
	}
}


void Title::Exit(GameMain* gm)
{
	ClearMenuKoumoku();
}


void Title::Pict(GameMain* gm)
{
	DrawGraph(0, 0, pict_datamap["title"], true);

	//選択中の項目のエフェクト更新
	if (IsEffekseer2DEffectPlaying(playing_koumoku_eff_no) == -1)
	{
		KoumokuEffectSet();
	}
}


void Title::UIPict(GameMain* gm)
{
	for (auto itr = menu.begin(); itr != menu.end(); ++itr)
	{
		DrawRotaGraph(itr->second->x, itr->second->y, 1.0, 0.0, itr->second->pict_no, true, false);
	}
	if (star_deltatime >= 60) star_deltatime = 0;
	DrawRotaGraph(current_koumoku->x - 90, current_koumoku->y, 1.0, 0.0, star_pict_datamap[star_deltatime], true, false);
	DrawRotaGraph(current_koumoku->x + 90, current_koumoku->y, 1.0, 0.0, star_pict_datamap[star_deltatime], true, false);
	star_deltatime++;
}


void Title::AddMenuKoumoku(string key, void(Title::*koumoku_method)(GameMain* gm), int _x, int _y, int _pict_no)
{
	MenuKoumoku<Title> *_koumoku = new MenuKoumoku<Title>;
	_koumoku->key = key;
	_koumoku->x = _x;
	_koumoku->y = _y;
	_koumoku->koumoku_method = koumoku_method;
	_koumoku->pict_no = _pict_no;
	menu[key] = _koumoku;
}


void Title::ClearMenuKoumoku()
{
	for (auto itr = menu.begin(); itr != menu.end(); ++itr)
	{
		delete itr->second;
	}
	menu.clear();
}

void Title::Koumoku_Hajimeru(GameMain* gm)
{
	gm->ChangeScene(gsHonbanIns);
}


void Title::Koumoku_Yameru(GameMain* gm)
{
	gm->game_end_flag = true;
}



void Title::KoumokuEffectOverwrite()
{
	if (IsEffekseer2DEffectPlaying(playing_koumoku_eff_no) == 0)
		SetScalePlayingEffekseer2DEffect(playing_koumoku_eff_no, 0.0f, 0.0f, 0.0f);
	KoumokuEffectSet();
}


void Title::KoumokuEffectSet()
{
	playing_koumoku_eff_no = PlayEffekseer2DEffect(eff_datamap["button_selecting"]);
	SetPosPlayingEffekseer2DEffect(playing_koumoku_eff_no, current_koumoku->x, current_koumoku->y, 0.0f);
	float _scale = 40.0f;
	SetScalePlayingEffekseer2DEffect(playing_koumoku_eff_no, _scale, _scale, _scale);
}
