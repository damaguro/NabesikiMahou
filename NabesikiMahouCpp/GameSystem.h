#pragma once
#include <map>
#include <list>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "InputSignals.h"
#include "TsuSoundManager.h"
#include "PictTestText.h"

using namespace std;

#define gmScene Scene<GameMain>
#define gsHonbanIns Honban::Instance()
#define gsPauseIns Pause::Instance()
#define gsTitleIns Title::Instance()
#define gsResultIns Result::Instance()

template <class entry_class>
class Scene
{
public:

	virtual void Enter(entry_class*) = 0;
	virtual void Execute(entry_class*) = 0;
	virtual void Pict(entry_class*) = 0;
	virtual void UIPict(entry_class*) = 0;
	virtual void Exit(entry_class*) = 0;
	virtual ~Scene(){}
};

typedef list<int> EffekseerEffectHandle_fList;
class GameMain
{
public:
	GameMain(gmScene* init_scene);
	~GameMain();
	gmScene* gmCurrentScene;
	gmScene* gmPauseScene;

	void Update();
	void ChangeScene(gmScene* _new_scene);
	void CallMenuWithPause(gmScene* _new_menu_scene);
	void BackFromMenuWithPause();
	void Pict();

	bool honban_data_load_flag;
	int honban_score;
	bool title_data_load_flag;
	bool result_data_load_flag;
	bool game_end_flag;

private:
	int scene_fadeout_deltatime;
	int scene_fadeout_limittime;
	int scene_fadein_deltatime;
	int scene_fadein_limittime;
	gmScene* gmNextScene;
	
	void GotoNextScene();
public:
	void ReturnTitleWithReset();
	void EffectPict();
	void ChangeAllEffectPictMode();
	void ChangeDesignationEffectPictMode();
private:
	void(GameMain::*effect_pict_method)();
	Effekseer::Manager* eff_manager_2D;
	EffekseerEffectHandle_fList temporary_scene_play_eff_handle_list;
	void AllEffectPict();
	void TemporarySceneEffectPict();
public:

	void CrearTemporarySceneEffect();
	int PlayEffekseer2DEffectByTemporaryScene(int effectHandle);
	TsuSoundManager* SoundManager;
};

//ゲームオブジェクト前方宣言
class gobj_Nabeita;

//各属性の軸
class gobj_Nabeita_Jiku
{
public:
	gobj_Nabeita_Jiku(int _jiku_no, gobj_Nabeita *_owner_nabe, double _jiku_rad, int _pict_no, int _mark_pict_no, int _magic_invocation_time, int _conf_eff_no, int _magic_eff_no, int _magic_ring_eff_no, int _sound_handle);
	~gobj_Nabeita_Jiku();
	double jiku_rad;
	double zokusei_value;
	gobj_Nabeita_Jiku* prev;
	gobj_Nabeita_Jiku* next;
	int conf_eff_no;
	double magic_value;
	int magic_invocation_time;
	int magic_delta_time;
	int magic_pos_x;
	int magic_pos_y;
	int jiku_no;
	gobj_Nabeita* owner_nabe;
	int sound_handle;
	int mark_pict_no;
private:
	int pict_no;

	int magic_eff_no;
	int magic_eff_play_no;
	bool magic_eff_play_flag;
	int magic_ring_eff_no;
	int magic_ring_eff_play_no;
	bool magic_ring_eff_play_flag;
public:

	void Pict(int p_x, int p_y, double rotate_rad);
	void Update();
};



//魔法オブジェクト
class gobj_Mahou
{
public:
	gobj_Mahou(int _eff_no, int _magic_eff_no, double _x, double _y, double _scale, int _invocationtime, int _remnant_live, gobj_Nabeita* _owner_nabe);
	~gobj_Mahou();
	void Update();
	void Pict(int p_x, int p_y, double p_rotate);
	gobj_Mahou* prev;
	gobj_Mahou* next;
	double m_x, m_y;
	double scale;
	int deltatime;
	int invocationtime;
	int remnant_live;
	bool del_order;
	double g_rad;
private:
	int eff_no;
	int eff_play_no;
	bool eff_play_flag;
	int magic_eff_no;
	int magic_eff_play_no;
	bool magic_eff_play_flag;
	int point_eff_play_no;
	bool point_eff_play_flag;
	gobj_Nabeita* owner_nabe;
};

struct magic_ball
{
	int time;
	int pict_no;
	magic_ball* prev;
	magic_ball* next;
};

//鍋板
class gobj_Nabeita
{
public:
	gobj_Nabeita(int _pict_no, GameMain* gm);
	~gobj_Nabeita();
	void Update();
	void Pict();

	double rotate_rad;
	double rotate_velocity;
	double rotate_acceleration;
	int sent_x, sent_y, radius;
	int rotate_arrow_direction;
	double jiku_mahou_values[5];
	int jiku_mahou_flags[5];
	int point_marker_eff_nos[5];
private:
	int pict_no;
	double nabe_enlargement_factor;
	int rotate_arrows_pict_no[3];
	int rotate_arrow_direction_deltatime;
	int rotate_arrow_direction_changetine;
	double zokusei[6];

	int mahou_deltatime;
	int mahou_limittime;
	double mahou_deltavalue;
	double mahou_limitvalue;
	double mahou_addvalue;
	int mahou_inclimittime;
	double mahou_inclimitvalue;
	double mahou_incaddvalue;
	void ResetMahouGenerator();

	int point_pict_no;
	double point_x, point_y;

	gobj_Nabeita_Jiku* jiku_head;
	gobj_Mahou* mahou_head;

	void AddJiku(gobj_Nabeita_Jiku* new_jiku);
	void AddMahou(gobj_Mahou* new_mahou);

	int emi_magic_delay;
	int emi_magic_time;
	bool push_emi_flag;

	magic_ball* magic_ball_head;
	int ball_move_time;
	int ball_speed;
	int ball_start_pos;
	double ball_conf_eff_size;
	void magic_ball_Add(int _time);
	void magic_ball_update();
	void zokusei_kasan();

	int handle_A_x, handle_A_y;
	int handle_A_pict_no;
	int handle_D_x, handle_D_y;
	int handle_D_pict_no;
	int space_key_x, space_key_y;
	int space_key_pict_no;
	int arrow1_x, arrow1_y;
	int arrow2_x, arrow2_y;
public:
	void DelMahou();
	void UpdateMagics();
	void magic_ball_pict();
	void CheckJikuMahouSetFlags();
private:
	void ClearJiku();
	void MagicBallClear();
public:
	void ClearMahou();
	GameMain* owner_gm;
};

//UI用
struct ColorNumber
{
	int x, y;
	int pict_no;
	int deltatime;
	int deletetime;
	int hide_time;
	int alpha;
	ColorNumber *prev;
	ColorNumber *next;
};

class Honban : public gmScene
{
public:
	~Honban();

	static Honban* Instance();
	//画像などをEnterでロード
	virtual void Enter(GameMain* gm);
	virtual void Execute(GameMain* gm);
	virtual void Exit(GameMain* gm);
	map<string, int> pict_datamap;
	map<string, int> eff_datamap;
	int color_number_pict_datamap[4][10];
	long score;
private:
	Honban(){}
	Honban(const Honban &);
	Honban& operator=(const Honban &);

	gobj_Nabeita *nabe;
	int suuji_size_x;
	int suuji_size_y;
	int suuji_hidetime;
	int suuji_deletetime;
	int score_right_x;
	int score_y;
	int game_deltatime;
	int game_limittime;
	int time_x, time_y;

	ColorNumber *color_number_head;
	int color_number_limit_time;
	int color_number_hide_time;

	void ParamInit();
public:
	void ScorePict();
	void ColorNumberSet(int value, int _x, int _y);
	void ColorNumbersPict();
	void ColorNumberClear();
	void ColorNumberNodeSet(int _pict_no, int _x, int _y, int hidetime, int deletetime);
	virtual void Pict(GameMain* gm);
	virtual void UIPict(GameMain* gm);
private:
	void TimePict();
};

template <class entry_class>
struct MenuKoumoku
{
	int x, y;
	int pict_no;
	string key;
	void(entry_class::*koumoku_method)(GameMain* gm);
	MenuKoumoku *down, *up;
};

class Pause : public gmScene
{
public:
	~Pause();
	static Pause* Instance();
	virtual void Enter(GameMain* gm);
	virtual void Execute(GameMain* gm);
	virtual void Exit(GameMain* gm);
	virtual void Pict(GameMain* gm);
	virtual void UIPict(GameMain* gm);

private:
	Pause(){}
	Pause(const Pause &);
	Pause& operator = (const Pause &);
	void Koumoku_Tsuzukeru(GameMain* gm);
	void Koumoku_Yameru(GameMain* gm);
	map<string, MenuKoumoku<Pause>*> menu;
	MenuKoumoku<Pause> *current_koumoku;
	int playing_koumoku_eff_no;
	int star_deltatime;
public:
	void AddMenuKoumoku(string key, void(Pause::*koumoku_method)(GameMain* gm), int _x, int _y, int _pict_no);
	void ClearMenuKoumoku();
	void KoumokuEffectOverwrite();
	void KoumokuEffectSet();
private:
	void Koumoku_Modoru(GameMain* gm);
	GameMain* owner_gm;
};

class Title :
	public gmScene
{
public:

	~Title();
	static Title* Instance();
	virtual void Enter(GameMain* gm);
	virtual void Execute(GameMain* gm);
	virtual void Exit(GameMain* gm);
	virtual void Pict(GameMain* gm);
	virtual void UIPict(GameMain* gm);
	map<string, int> pict_datamap;
	map<string, int> eff_datamap;
	int star_pict_datamap[60];
	int star_wid, star_hei;
	int star_deltatime;
private:
	Title(){}
	Title(const Title &);
	Title& operator = (const Title &);
	map<string, MenuKoumoku<Title>*> menu;
	MenuKoumoku<Title> *current_koumoku;
	int playing_koumoku_eff_no;
public:
	void AddMenuKoumoku(string key, void(Title::*koumoku_method)(GameMain* gm), int _x, int _y, int _pict_no);
	void ClearMenuKoumoku();
private:
	void Koumoku_Hajimeru(GameMain* gm);
	void Koumoku_Yameru(GameMain* gm);
	void KoumokuEffectOverwrite();
	void KoumokuEffectSet();

};

struct ScoreNode
{
	string name;
	long score;
};

struct feed_picture
{
	feed_picture* prev;
	feed_picture* next;
	int pict_no;
	int x, y;
	double rad;
	int deltatime;
	int limittime;
	int feedin_time;
	int feedout_time;
};

class Result :
	public gmScene
{
public:
	~Result();
	static Result* Instance();
	virtual void Enter(GameMain* gm);
	virtual void Execute(GameMain* gm);
	virtual void Exit(GameMain* gm);
	virtual void Pict(GameMain* gm);
	virtual void UIPict(GameMain* gm);
	map<string, int> pict_datamap;
	map<string, int> eff_datamap;
	int suuji_pict_datamap[10];
private:
	Result(){}
	Result(const Result &);
	Result& operator = (const Result &);
	int suuji_size_x, suuji_size_y;
	int suuji_size_mini_x, suuji_size_mini_y;
	void ColorNumberPict(long score, int score_x, int score_y);
	ScoreNode score_nodes[10];
	int now_score_ranking_no;
	int score_ranking_right_x;
	int score_ranking_y;
	int star_deltatime;
	int current_score_x;
	int current_score_y;
	int end_pattern;
	feed_picture* feed_pic_head;
	int deltatime;
	int event_time;

public:
	void ScoreLoad();
	void ScoreWrite();
	void MiniNumberPict(long score, int score_x, int score_y);
private:
	void AddFeedPic(int _pict_no, int _x, int _y, double _rad, int _limit, int _feedin, int _feedout);
	void DelFeedPic(feed_picture* del_feed);
	void ClearFeedPic();
	void UpdateFeedPic();
public:
	void SetSmokeSingle(int x, int y);
private:
	void SetSmokeBurst(int x, int y);
};
