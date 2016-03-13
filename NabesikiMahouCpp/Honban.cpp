#include "GameSystem.h"

Honban::~Honban()
{
}

Honban* Honban::Instance()
{
	static Honban instance;
	return &instance;
}

void Honban::Enter(GameMain* gm)
{

	suuji_size_x = 32;
	suuji_size_y = 48;

	suuji_hidetime = 10;
	suuji_deletetime = 20;
	if (gm->honban_data_load_flag == false)
	{
		//画像などロード
		pict_datamap["Rasin"] = LoadGraph("Data/picture/nabeita.png");
		pict_datamap["rotate_arrow_left"] = LoadGraph("Data/picture/rotate_arrow_left.png");
		pict_datamap["rotate_arrow_right"] = LoadGraph("Data/picture/rotate_arrow_right.png");
		pict_datamap["mahoumoto"] = LoadGraph("Data/picture/mahoumoto.png");
		pict_datamap["haikei_tsukue"] = LoadGraph("Data/picture/tsukue.png");
		pict_datamap["orb_fire"] = LoadGraph("Data/picture/orb_fire.png");
		pict_datamap["orb_thunder"] = LoadGraph("Data/picture/orb_thunder.png");
		pict_datamap["orb_ice"] = LoadGraph("Data/picture/orb_ice.png");
		pict_datamap["orb_water"] = LoadGraph("Data/picture/orb_water.png");
		pict_datamap["orb_earth"] = LoadGraph("Data/picture/orb_earth.png");
		pict_datamap["mark_fire"] = LoadGraph("Data/picture/mark_fire.png");
		pict_datamap["mark_thunder"] = LoadGraph("Data/picture/mark_thunder.png");
		pict_datamap["mark_ice"] = LoadGraph("Data/picture/mark_ice.png");
		pict_datamap["mark_water"] = LoadGraph("Data/picture/mark_water.png");
		pict_datamap["mark_earth"] = LoadGraph("Data/picture/mark_earth.png");

		pict_datamap["element_point"] = LoadGraph("Data/picture/element_point.png");
		pict_datamap["handle_A_def"] = LoadGraph("Data/picture/handle_A_def.png");
		pict_datamap["handle_D_def"] = LoadGraph("Data/picture/handle_D_def.png");
		pict_datamap["handle_A_pushed"] = LoadGraph("Data/picture/handle_A_pushed.png");
		pict_datamap["handle_D_pushed"] = LoadGraph("Data/picture/handle_D_pushed.png");
		pict_datamap["space_key_def"] = LoadGraph("Data/picture/space_key_def.png");
		pict_datamap["space_key_pushed"] = LoadGraph("Data/picture/space_key_pushed.png");

		eff_datamap["fire1"] = LoadEffekseerEffect("Data/effect/fire_002.efk");
		eff_datamap["thunder1"] = LoadEffekseerEffect("Data/effect/thunder_001.efk");
		eff_datamap["ice1"] = LoadEffekseerEffect("Data/effect/ice_001.efk");
		eff_datamap["water1"] = LoadEffekseerEffect("Data/effect/water_001.efk");
		eff_datamap["earth1"] = LoadEffekseerEffect("Data/effect/earth_001.efk");
		eff_datamap["magic_ring_small"] = LoadEffekseerEffect("Data/effect/magic_ring_small.efk");
		eff_datamap["magic_ring_big"] = LoadEffekseerEffect("Data/effect/magic_ring_big.efk");
		eff_datamap["magic_burst"] = LoadEffekseerEffect("Data/effect/magic_burst_001.efk");
		eff_datamap["fire_ring_short"] = LoadEffekseerEffect("Data/effect/fire_ring_short.efk");
		eff_datamap["thunder_ring_short"] = LoadEffekseerEffect("Data/effect/thunder_ring_short.efk");
		eff_datamap["ice_ring_short"] = LoadEffekseerEffect("Data/effect/ice_ring_short.efk");
		eff_datamap["water_ring_short"] = LoadEffekseerEffect("Data/effect/water_ring_short.efk");
		eff_datamap["earth_ring_short"] = LoadEffekseerEffect("Data/effect/earth_ring_short.efk");
		eff_datamap["point_marker_red"] = LoadEffekseerEffect("Data/effect/pic_point_marker_red.efk");
		eff_datamap["point_marker_yellow"] = LoadEffekseerEffect("Data/effect/pic_point_marker_yellow.efk");
		eff_datamap["point_marker_green"] = LoadEffekseerEffect("Data/effect/pic_point_marker_green.efk");
		eff_datamap["point_marker_blue"] = LoadEffekseerEffect("Data/effect/pic_point_marker_blue.efk");
		eff_datamap["point_marker_white"] = LoadEffekseerEffect("Data/effect/pic_point_marker_white.efk");

		LoadDivGraph("Data/picture/suuji_toga_blue.png", 10, 10, 1, suuji_size_x, suuji_size_y, color_number_pict_datamap[0]);
		LoadDivGraph("Data/picture/suuji_toga_green.png", 10, 10, 1, suuji_size_x, suuji_size_y, color_number_pict_datamap[1]);
		LoadDivGraph("Data/picture/suuji_toga_yellow.png", 10, 10, 1, suuji_size_x, suuji_size_y, color_number_pict_datamap[2]);
		LoadDivGraph("Data/picture/suuji_toga_red.png", 10, 10, 1, suuji_size_x, suuji_size_y, color_number_pict_datamap[3]);
		pict_datamap["moji_colon"] = LoadGraph("Data/picture/moji_colon.png");
		gm->honban_data_load_flag = true;
	}

	//各オブジェクト作成
	nabe = new gobj_Nabeita(pict_datamap["Rasin"], gm);
	ParamInit();
}


void Honban::Execute(GameMain* gm)
{
	game_deltatime++;
	//制限時間
	if (game_deltatime >= game_limittime)
	{
		gm->honban_score = score;
		gm->ChangeScene(gsResultIns);
		return;
	}
	//ポーズ遷移
	if (InputSignalsIns->Input_P == 1)
	{
		gm->CallMenuWithPause(gsPauseIns);
		return;
	}

	DrawGraph(0, 0, pict_datamap["haikei_tsukue"], false);
	nabe->Update();
}

void Honban::Pict(GameMain* gm)
{
	nabe->Pict();
}

void Honban::UIPict(GameMain* gm)
{
	ColorNumbersPict();
	ScorePict();
	TimePict();
}


void Honban::Exit(GameMain* gm)
{
	delete nabe;
	ColorNumberClear();
}


void Honban::ParamInit()
{
	game_deltatime = 0;
	game_limittime = 2 * 3600;
	//game_limittime = 30;
	time_x = 492;
	time_y = 52;
	score = 0;
	score_right_x = 620;
	score_y = 2;
	ColorNumberClear();
}

void Honban::ScorePict()
{
	int i = 0;
	if (score == 0)
	{
		DrawGraph(score_right_x - suuji_size_x, score_y, color_number_pict_datamap[0][0], true);
	}
	for (long _score_pict = score; _score_pict > 0; _score_pict /= 10)
	{
		DrawGraph(score_right_x - suuji_size_x * (i + 1), score_y, color_number_pict_datamap[i % 4][_score_pict % 10], true);
		i++;
	}
}

void Honban::TimePict()
{
	int _time_min = (game_limittime - game_deltatime) / 3600;
	int _time_color = game_deltatime / (game_limittime / 4);
	if (_time_color > 3) _time_color = 3;
	int _time_sec = (game_limittime - game_deltatime) % 3600 / 60;
	DrawGraph(time_x, time_y, color_number_pict_datamap[_time_color][_time_min % 10], true);
	DrawGraph(time_x + suuji_size_x, time_y, pict_datamap["moji_colon"], true);
	DrawGraph(time_x + suuji_size_x * 2, time_y, color_number_pict_datamap[_time_color][_time_sec / 10], true);
	DrawGraph(time_x + suuji_size_x * 3, time_y, color_number_pict_datamap[_time_color][_time_sec % 10], true);
}


void Honban::ColorNumberSet(int value, int _x, int _y)
{
	int i = 0;
	if (value == 0)
	{
		ColorNumberNodeSet(color_number_pict_datamap[0][0], _x - suuji_size_x, _y, suuji_hidetime, suuji_deletetime);
	}
	else
	{
		for (int i = 0; value != 0; value /= 10)
		{
			ColorNumberNodeSet(color_number_pict_datamap[i % 4][value % 10], _x - suuji_size_x * (i + 1), _y, suuji_hidetime, suuji_deletetime);
			i++;
		}
	}
}

void Honban::ColorNumberNodeSet(int _pict_no, int _x, int _y, int hidetime, int deletetime)
{
	ColorNumber *new_number = new ColorNumber;
	new_number->prev = NULL;
	new_number->next = NULL;
	new_number->pict_no = _pict_no;
	new_number->x = _x;
	new_number->y = _y;
	new_number->hide_time = hidetime;
	new_number->deletetime = deletetime;
	new_number->deltatime = 0;
	new_number->alpha = 255;
	if (color_number_head == NULL)
	{
		color_number_head = new_number;
	}
	else
	{
		ColorNumber *_num;
		for (_num = color_number_head; _num->next != NULL; _num = _num->next);
		new_number->prev = _num;
		_num->next = new_number;
	}
}


void Honban::ColorNumbersPict()
{
	ColorNumber *_num, *_numnext;
	for (_num = color_number_head; _num != NULL; _num = _numnext)
	{
		_numnext = _num->next;
		if (_num->alpha < 255)
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _num->alpha);

		DrawGraph(_num->x, _num->y, _num->pict_no, true);
		_num->deltatime++;
		if (_num->deltatime > _num->deletetime - _num->hide_time)
		{
			_num->alpha -= 255 / _num->hide_time;
		}
		if (_num->deltatime > _num->deletetime)
		{
			if (_num->prev != NULL)
			{
				_num->prev->next = _num->next;
			}
			else
			{
				color_number_head = _num->next;
			}
			if (_num->next != NULL)
			{
				_num->next->prev = _num->prev;
			}
			delete _num;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void Honban::ColorNumberClear()
{
	ColorNumber *_num, *_numnext;
	for (_num = color_number_head; _num != NULL; _num = _numnext)
	{
		_numnext = _num->next;
		delete _num;
	}
	color_number_head = NULL;
}

gobj_Nabeita::gobj_Nabeita(int _pict_no, GameMain* gm)
{
	pict_no = _pict_no;
	owner_gm = gm;
	nabe_enlargement_factor = 0.8;
	rotate_arrows_pict_no[0] = gsHonbanIns->pict_datamap["rotate_arrow_left"];	//1or-1の配列参照のため空けた
	rotate_arrows_pict_no[2] = gsHonbanIns->pict_datamap["rotate_arrow_right"];	//Pictでrotate_arrow_directionを添字に使う
	rotate_arrow_direction = -1;
	rotate_arrow_direction_deltatime = 0;
	rotate_arrow_direction_changetine = 300;
	rotate_rad = 0;
	rotate_velocity = 0;
	rotate_acceleration = 0.005;
	sent_x = 320;
	sent_y = 260;
	radius = 300;
	for (int i = 0; i < 6; i++)
	{
		zokusei[i] = 0.0;
	}
	//仮ね jikuとnabeに使ったよ
	point_pict_no = gsHonbanIns->pict_datamap["element_point"];
	jiku_head = NULL;
	int jiku_magic_invocation_time = 300;

	AddJiku(new gobj_Nabeita_Jiku(0, this, 0, gsHonbanIns->pict_datamap["orb_fire"], gsHonbanIns->pict_datamap["mark_fire"], jiku_magic_invocation_time, gsHonbanIns->eff_datamap["fire_ring_short"],
		gsHonbanIns->eff_datamap["fire1"], gsHonbanIns->eff_datamap["magic_ring_big"], owner_gm->SoundManager->GetSoundHandle("pachipachi")));
	AddJiku(new gobj_Nabeita_Jiku(1, this, DX_TWO_PI / 6.0, gsHonbanIns->pict_datamap["orb_thunder"], gsHonbanIns->pict_datamap["mark_thunder"], jiku_magic_invocation_time, gsHonbanIns->eff_datamap["thunder_ring_short"],
		gsHonbanIns->eff_datamap["thunder1"], gsHonbanIns->eff_datamap["magic_ring_big"], owner_gm->SoundManager->GetSoundHandle("thunder")));
	AddJiku(new gobj_Nabeita_Jiku(2, this, (DX_TWO_PI / 6.0) * 2, gsHonbanIns->pict_datamap["orb_ice"], gsHonbanIns->pict_datamap["mark_ice"], jiku_magic_invocation_time, gsHonbanIns->eff_datamap["ice_ring_short"],
		gsHonbanIns->eff_datamap["ice1"], gsHonbanIns->eff_datamap["magic_ring_big"], owner_gm->SoundManager->GetSoundHandle("ice01")));
	AddJiku(new gobj_Nabeita_Jiku(3, this, (DX_TWO_PI / 6.0) * 3, gsHonbanIns->pict_datamap["orb_water"], gsHonbanIns->pict_datamap["mark_water"], jiku_magic_invocation_time, gsHonbanIns->eff_datamap["water_ring_short"],
		gsHonbanIns->eff_datamap["water1"], gsHonbanIns->eff_datamap["magic_ring_big"], owner_gm->SoundManager->GetSoundHandle("water01")));
	AddJiku(new gobj_Nabeita_Jiku(4, this, (DX_TWO_PI / 6.0) * 5, gsHonbanIns->pict_datamap["orb_earth"], gsHonbanIns->pict_datamap["mark_earth"], jiku_magic_invocation_time, gsHonbanIns->eff_datamap["earth_ring_short"],
		gsHonbanIns->eff_datamap["earth1"], gsHonbanIns->eff_datamap["magic_ring_big"], owner_gm->SoundManager->GetSoundHandle("ice01")));

	mahou_deltatime = 0;
	mahou_limittime = 120;
	mahou_deltavalue = 0.0;
	mahou_limitvalue = 120.0;
	mahou_addvalue = 5.0;

	mahou_inclimittime = 1;
	mahou_inclimitvalue = 0.5;
	mahou_incaddvalue = 0.1;

	emi_magic_delay = 5;
	emi_magic_time = 0;
	push_emi_flag = false;

	mahou_head = NULL;

	magic_ball_head = NULL;
	ball_move_time = 8;
	ball_speed = 7;
	ball_start_pos = 65;
	ball_conf_eff_size = 50.0;

	for (int i = 0; i < 5; i++)
	{
		jiku_mahou_flags[i] = false;
		jiku_mahou_values[i] = 0.0;
	}
	point_marker_eff_nos[0] = gsHonbanIns->eff_datamap["point_marker_white"];
	point_marker_eff_nos[1] = gsHonbanIns->eff_datamap["point_marker_blue"];
	point_marker_eff_nos[2] = gsHonbanIns->eff_datamap["point_marker_green"];
	point_marker_eff_nos[3] = gsHonbanIns->eff_datamap["point_marker_yellow"];
	point_marker_eff_nos[4] = gsHonbanIns->eff_datamap["point_marker_red"];
	handle_A_x = 50;
	handle_A_y = 410;
	handle_D_x = 365;
	handle_D_y = 410;
	space_key_x = 50;
	space_key_y = 70;
	arrow1_x = 100;
	arrow1_y = sent_y;
	arrow2_x = 540;
	arrow2_y = sent_y;
}


gobj_Nabeita::~gobj_Nabeita()
{

	ClearJiku();
	ClearMahou();
	MagicBallClear();
}


void gobj_Nabeita::Update()
{
	//鍋の操作
	rotate_velocity += rotate_acceleration * InputSignalsIns->Input_DA;
	if (rotate_velocity > DX_TWO_PI * 2)
		rotate_velocity = DX_TWO_PI * 2;
	if (rotate_velocity < -DX_TWO_PI * 2)
		rotate_velocity = -DX_TWO_PI * 2;
	rotate_rad += rotate_velocity;
	if (rotate_rad < 0) rotate_rad = rotate_rad - ((int)(rotate_rad / DX_TWO_PI) - 1) * DX_TWO_PI;
	if (rotate_rad > DX_TWO_PI) rotate_rad = rotate_rad - (int)(rotate_rad / DX_TWO_PI) * DX_TWO_PI;
	if (InputSignalsIns->Input_DA == -1)
	{
		handle_A_pict_no = gsHonbanIns->pict_datamap["handle_A_pushed"];
		handle_D_pict_no = gsHonbanIns->pict_datamap["handle_D_def"];
	}
	else if (InputSignalsIns->Input_DA == 1)
	{
		handle_A_pict_no = gsHonbanIns->pict_datamap["handle_A_def"];
		handle_D_pict_no = gsHonbanIns->pict_datamap["handle_D_pushed"];
	} 
	else
	{
		handle_A_pict_no = gsHonbanIns->pict_datamap["handle_A_def"];
		handle_D_pict_no = gsHonbanIns->pict_datamap["handle_D_def"];
	}
	//魔法効果方向の切り替え
	rotate_arrow_direction_deltatime += 1;
	if (rotate_arrow_direction_deltatime > rotate_arrow_direction_changetine)
	{
		owner_gm->SoundManager->PlaySoundFile("arrow");
		rotate_arrow_direction *= -1;
		rotate_arrow_direction_deltatime = 0;
	}

	gobj_Nabeita_Jiku* _jiku;
	gobj_Nabeita_Jiku* _jiku_prev = jiku_head;

	//魔法素投入
	if (emi_magic_time > 0)
	{
		emi_magic_time += 1;
		if (emi_magic_time > emi_magic_delay)
		{
			owner_gm->SoundManager->PlaySoundFile("shoot000");
			magic_ball_Add(ball_move_time);
			emi_magic_time = 0;
		}
	}
	//入力信号作動要求
	if (InputSignalsIns->Input_Space == 1 && emi_magic_time == 0)
	{
		push_emi_flag = true;
	}
	if (InputSignalsIns->Input_Space == 1)
		space_key_pict_no = gsHonbanIns->pict_datamap["space_key_pushed"];
	else
		space_key_pict_no = gsHonbanIns->pict_datamap["space_key_def"];
	//作動中の入力信号無しならカウントスタート
	if (push_emi_flag == true && emi_magic_time == 0)
	{
		emi_magic_time = 1;
		push_emi_flag = false;
	}
	magic_ball_update();

	point_x = 0;
	point_y = 0;
	//属性ポイントの移動(いちいちリセットするパターン
	for (_jiku = jiku_head; _jiku != NULL; _jiku = _jiku->next) {
		point_x += _jiku->zokusei_value * -sin(_jiku->jiku_rad);
		point_y += _jiku->zokusei_value * -cos(_jiku->jiku_rad);
	}

	//魔法の生成
	mahou_deltatime += 1;
	if (mahou_deltatime >= mahou_limittime || mahou_deltavalue >= mahou_limitvalue)
	{
		if (mahou_deltavalue > mahou_limitvalue * 0.01)
		{
			owner_gm->SoundManager->PlaySoundFile("beep");
			AddMahou(new gobj_Mahou(gsHonbanIns->eff_datamap["magic_burst"], gsHonbanIns->eff_datamap["magic_ring_small"],
				point_x, point_y, sqrt(point_x * point_x + point_y * point_y) / 100.0, mahou_deltatime + 120, mahou_limittime / mahou_deltatime, this));
		}
		ResetMahouGenerator();
	}
	//軸の更新
	
	for (gobj_Nabeita_Jiku* _jiku = jiku_head; _jiku != NULL; _jiku = _jiku->next) {
		_jiku->Update();
	}
	CheckJikuMahouSetFlags();

	//魔法のkousinn
	DelMahou();
	UpdateMagics();
	
}


void gobj_Nabeita::Pict()
{	//ハンドル、キー描画
	DrawGraph(handle_A_x, handle_A_y, handle_A_pict_no, true);
	DrawGraph(handle_D_x, handle_D_y, handle_D_pict_no, true);
	DrawGraph(space_key_x, space_key_y, space_key_pict_no, true);

	//鍋と矢印描画
	DrawRotaGraph(sent_x, sent_y, nabe_enlargement_factor, rotate_rad, pict_no, true, false);
	DrawRotaGraph(arrow1_x, arrow1_y, 1.0, DX_PI, rotate_arrows_pict_no[rotate_arrow_direction + 1], true, false);
	DrawRotaGraph(arrow2_x, arrow2_y, 1.0, 0.0, rotate_arrows_pict_no[rotate_arrow_direction + 1], true, false);

	//各軸属性ポイント、軸魔法描画
	for (gobj_Nabeita_Jiku* _jiku = jiku_head; _jiku != NULL; _jiku = _jiku->next) {
		double _x = _jiku->magic_value * -sin(_jiku->jiku_rad);
		double _y = _jiku->magic_value * -cos(_jiku->jiku_rad);
		DrawRotaGraph(sent_x + _x * cos(rotate_rad) - _y * sin(rotate_rad),
			sent_y + _x * sin(rotate_rad) + _y * cos(rotate_rad),
			1.0, 0.0, _jiku->mark_pict_no, true, false);
	}
	for (gobj_Nabeita_Jiku* _jiku = jiku_head; _jiku != NULL; _jiku = _jiku->next) {
		_jiku->Pict(sent_x, sent_y, rotate_rad);
	}
	//属性ポイント描画
	DrawRotaGraph(sent_x + point_x * cos(rotate_rad) - point_y * sin(rotate_rad),
		sent_y + point_x * sin(rotate_rad) + point_y * cos(rotate_rad),
		1.0, 0.0, point_pict_no, true, false);
	//魔法描画
	for (gobj_Mahou* _mahou = mahou_head; _mahou != NULL; _mahou = _mahou->next) {
		_mahou->Pict(sent_x, sent_y, rotate_rad);
	}
	//魔法素描画
	magic_ball_pict();
}

//軸追加　コンストラクタ用
void gobj_Nabeita::AddJiku(gobj_Nabeita_Jiku* new_jiku)
{
	new_jiku->next = NULL;
	if (jiku_head == NULL)
	{
		new_jiku->prev = NULL;
		jiku_head = new_jiku;
	}
	else
	{
		gobj_Nabeita_Jiku* _jiku;
		for (_jiku = jiku_head; _jiku->next != NULL; _jiku = _jiku->next);
		new_jiku->prev = _jiku;
		_jiku->next = new_jiku;
	}
}

//軸全削除　デストラクタ用
void gobj_Nabeita::ClearJiku()
{
	gobj_Nabeita_Jiku *_jiku, *_jiku_next;
	for (_jiku = jiku_head; _jiku != NULL; _jiku = _jiku_next)
	{
		_jiku_next = _jiku->next;
		delete _jiku;
	}
}


//魔法素操作
void gobj_Nabeita::magic_ball_Add(int _time)
{
	magic_ball* new_ball = new magic_ball;
	new_ball->next = NULL;
	new_ball->time = _time;
	new_ball->pict_no = gsHonbanIns->pict_datamap["mahoumoto"];
	if (magic_ball_head == NULL)
	{
		magic_ball_head = new_ball;
		new_ball->prev = NULL;
	}
	else
	{
		magic_ball* _ball;
		for (_ball = magic_ball_head; _ball->next != NULL; _ball = _ball->next);
		new_ball->prev = _ball;
		_ball->next = new_ball;
	}
}

void gobj_Nabeita::magic_ball_update()
{
	magic_ball *_ball, *_ball_next;
	for (_ball = magic_ball_head; _ball != NULL;)
	{
		_ball->time -= 1;
		_ball_next = _ball->next;
		if (_ball->time < 0)
		{
			zokusei_kasan();
			//削除
			owner_gm->SoundManager->PlaySoundFile("shoot");
			if (_ball->prev == NULL)
			{
				magic_ball_head = _ball->next;
			}
			else
			{
				_ball->prev->next = _ball->next;
			}
			if (_ball->next != NULL)
			{
				_ball->next->prev = _ball->prev;
			}

       		delete _ball;
			_ball = NULL;
		}
		_ball = _ball_next;
	}

}

void gobj_Nabeita::magic_ball_pict()
{
	magic_ball* _ball;
	for (_ball = magic_ball_head; _ball != NULL; _ball = _ball->next)
	{
		DrawRotaGraph(sent_x, ball_start_pos - _ball->time * ball_speed, 1.0, 0.0, _ball->pict_no, true, false);
	}
}

void gobj_Nabeita::MagicBallClear()
{
	magic_ball *_ball, *_ball_next;
	for (_ball = magic_ball_head; _ball != NULL; _ball = _ball_next)
	{
		_ball_next = _ball->next;
		delete _ball;
	}
}



void gobj_Nabeita::zokusei_kasan()
{
	//属性値加算
	//先頭の軸がifを満たさないことを前提(jiku_rad==0)
	//rotate_radを超える軸を探す
	gobj_Nabeita_Jiku* _jiku;
	gobj_Nabeita_Jiku* _jiku_prev = jiku_head;
	double hiritu;
	for (_jiku = jiku_head->next; _jiku != NULL; _jiku = _jiku->next)
	{
		if (_jiku->jiku_rad > rotate_rad) break;
		_jiku_prev = _jiku;
	}
	//rotate_radを挟む２つの軸で、魔法の素を分ける
	if (_jiku == NULL) {
		//一周する最後のノードだった場合
		_jiku = jiku_head;
		hiritu = (rotate_rad - _jiku_prev->jiku_rad) / (DX_TWO_PI - _jiku_prev->jiku_rad);
	}
	else
	{
		hiritu = (rotate_rad - _jiku_prev->jiku_rad) / (_jiku->jiku_rad - _jiku_prev->jiku_rad);
	}
	//分配とエフェクト起動
	int _eff_p_handle;
	_jiku->zokusei_value += mahou_addvalue * hiritu;
	_jiku->magic_value += mahou_addvalue * hiritu;
	_eff_p_handle = PlayEffekseer2DEffect(_jiku->conf_eff_no);
	SetScalePlayingEffekseer2DEffect(_eff_p_handle, ball_conf_eff_size * hiritu, ball_conf_eff_size * hiritu, ball_conf_eff_size * hiritu);
	SetPosPlayingEffekseer2DEffect(_eff_p_handle, sent_x, ball_start_pos, 0);
	_jiku_prev->zokusei_value += mahou_addvalue * (1.0 - hiritu);
	_jiku_prev->magic_value += mahou_addvalue * (1.0 - hiritu);
	_eff_p_handle = PlayEffekseer2DEffect(_jiku_prev->conf_eff_no);
	SetScalePlayingEffekseer2DEffect(_eff_p_handle, ball_conf_eff_size * (1.0 - hiritu), ball_conf_eff_size * (1.0 - hiritu), ball_conf_eff_size * (1.0 - hiritu));
	SetPosPlayingEffekseer2DEffect(_eff_p_handle, sent_x, ball_start_pos, 0);

	mahou_deltavalue += mahou_addvalue;
}


//魔法追加
void gobj_Nabeita::AddMahou(gobj_Mahou* new_mahou)
{
	new_mahou->next = NULL;
	if (mahou_head == NULL)
	{
		new_mahou->prev = NULL;
		mahou_head = new_mahou;
	}
	else
	{
		gobj_Mahou* _mahou;
		for (_mahou = mahou_head; _mahou->next != NULL; _mahou = _mahou->next);
		new_mahou->prev = _mahou;
		_mahou->next = new_mahou;
	}
	mahou_limittime += mahou_inclimittime;
	mahou_limitvalue += mahou_inclimitvalue;
	mahou_addvalue += mahou_incaddvalue;
}

//魔法削除
void gobj_Nabeita::DelMahou()
{
	gobj_Mahou *_mahou, *_mahou_next;
	for (_mahou = mahou_head; _mahou != NULL;)
	{
		_mahou_next = _mahou->next;
		if (_mahou->del_order == true)
		{
			if (_mahou->prev != NULL)
				_mahou->prev->next = _mahou->next;
			else
				mahou_head = _mahou->next;

			if (_mahou->next != NULL)
				_mahou->next->prev = _mahou->prev;
			delete _mahou;
		}
		_mahou = _mahou_next;
	}
}

//魔法更新
void gobj_Nabeita::UpdateMagics()
{
	gobj_Mahou* _mahou;

	for (_mahou = mahou_head; _mahou != NULL; _mahou = _mahou->next)
	{
	_mahou->Update();
	}
}

//魔法全削除
void gobj_Nabeita::ClearMahou()
{
	gobj_Mahou *_mahou, *_mahou_next;
	for (_mahou = mahou_head; _mahou != NULL; _mahou = _mahou_next)
	{
		_mahou_next = _mahou->next;
		delete _mahou;
	}
}


//追加魔法ステータスなどリセット
void gobj_Nabeita::ResetMahouGenerator()
{
	mahou_deltatime = 0;
	mahou_deltavalue = 0;
	gobj_Nabeita_Jiku* _jiku;
	for (_jiku = jiku_head; _jiku != NULL; _jiku = _jiku->next)
		_jiku->zokusei_value = 0.0;
}

//軸魔法の確認と一斉スコア加算
void gobj_Nabeita::CheckJikuMahouSetFlags()
{
	gobj_Nabeita_Jiku *_jiku;
	bool checkflags = true;
	for (int i = 0; i < 5; i++)
	{
		checkflags = checkflags && jiku_mahou_flags[i];
	}
	if (checkflags == true)
	{
		double _heikin = 0.0;
		double _hensa = 0.0;
		int i;
		_jiku = jiku_head;
		for (i = 0; i < 5; i++)
		{
			_heikin += jiku_mahou_values[i];
			_jiku = _jiku->next;
		}
		_heikin /= i;
		_jiku = jiku_head;
		for (i = 0; i < 5; i++)
		{
			_hensa += pow(_heikin - jiku_mahou_values[i], 2);
			_jiku = _jiku->next;
		}
		_hensa = sqrt(_hensa / i);

		//得点処理
		double _add_score = _heikin * 10 - _hensa * 10 / 4.0;
		//スコアに加算処理
		gsHonbanIns->score += (long)_add_score;
		gsHonbanIns->ColorNumberSet((int)_add_score, 200, 0);

		for (i = 0; i < 5; i++)
		{
			jiku_mahou_flags[i] = false;
			jiku_mahou_values[i] = 0.0;
		}
	}
}


gobj_Mahou::gobj_Mahou(int _eff_no, int _magic_eff_no, double _x, double _y, double _scale, int _invocationtime, int _remnant_live,  gobj_Nabeita* _owner_nabe)
{
	eff_no = _eff_no;
	magic_eff_no = _magic_eff_no;
	eff_play_no = -1;
	point_eff_play_no = -1;
	point_eff_play_flag = false;
	m_x = _x;
	m_y = _y;
	scale = _scale;
	deltatime = 0;
	invocationtime = _invocationtime;
	remnant_live = _remnant_live;
	owner_nabe = _owner_nabe;
	del_order = false;
	g_rad = atan2(m_x, m_y);
	g_rad = DX_PI + g_rad;
	
}

gobj_Mahou::~gobj_Mahou()
{
}


void gobj_Mahou::Update()
{
	deltatime += 1;
	if (deltatime > invocationtime - 90 && magic_eff_play_flag == false && remnant_live >= 0)
	{
		magic_eff_play_no = PlayEffekseer2DEffect(magic_eff_no);
		SetScalePlayingEffekseer2DEffect(magic_eff_play_no, scale * 23.0f, scale * 23.0f, scale * 23.0f);
		magic_eff_play_flag = true;
	}
	else if (remnant_live >= 0 && point_eff_play_flag == false)
	{
		int _playeffno = remnant_live;
		if (_playeffno > 4) _playeffno = 4;
		point_eff_play_no = PlayEffekseer2DEffect(owner_nabe->point_marker_eff_nos[_playeffno]);
		SetScalePlayingEffekseer2DEffect(point_eff_play_no, scale * 10.0f, scale * 10.0f, scale * 10.0f);
		point_eff_play_flag = true;
	}
	if (deltatime > invocationtime)
	{
		
		if (remnant_live >= 0)
		{
			deltatime = 0;
			remnant_live -= 1;

			owner_nabe->owner_gm->SoundManager->PlaySoundFile("bone");
			owner_nabe->rotate_velocity += scale * 0.01 * abs(sin(g_rad - owner_nabe->rotate_rad)) * owner_nabe->rotate_arrow_direction;
			gsHonbanIns->score += (int)(scale * 50);
			gsHonbanIns->ColorNumberSet((int)(scale * 50),
				m_x * cos(owner_nabe->rotate_rad) - m_y * sin(owner_nabe->rotate_rad) + owner_nabe->sent_x,
				m_x * sin(owner_nabe->rotate_rad) + m_y * cos(owner_nabe->rotate_rad) + owner_nabe->sent_y);

			//ここの使用上、エフェクトの再生時間はinvocationtimeを上回ってはならない
			eff_play_no = PlayEffekseer2DEffect(eff_no);
			SetScalePlayingEffekseer2DEffect(eff_play_no, scale * 10.0f, scale * 10.0f, scale * 10.0f);
			eff_play_flag = true;
		}
	}
}

void gobj_Mahou::Pict(int p_x, int p_y, double p_rotate)
{
	if (magic_eff_play_flag == true)
	{
		SetPosPlayingEffekseer2DEffect(magic_eff_play_no,
			m_x * cos(p_rotate) - m_y * sin(p_rotate) + p_x,
			m_x * sin(p_rotate) + m_y * cos(p_rotate) + p_y,
			0.0);
	}
	if (point_eff_play_flag == true)
	{
		SetPosPlayingEffekseer2DEffect(point_eff_play_no,
			m_x * cos(p_rotate) - m_y * sin(p_rotate) + p_x,
			m_x * sin(p_rotate) + m_y * cos(p_rotate) + p_y,
			0.0);
	}
	if (eff_play_flag == true)
	{
		SetPosPlayingEffekseer2DEffect(eff_play_no,
			m_x * cos(p_rotate) - m_y * sin(p_rotate) + p_x,
			m_x * sin(p_rotate) + m_y * cos(p_rotate) + p_y,
			0.0);
	}
	if (IsEffekseer2DEffectPlaying(eff_play_no) == -1)
	{
		eff_play_flag = false;
		if (remnant_live < 0) del_order = true;
	}
	if (IsEffekseer2DEffectPlaying(magic_eff_play_no) == -1)
	{
		magic_eff_play_flag = false;
	}
	if (IsEffekseer2DEffectPlaying(point_eff_play_no) == -1)
	{
		point_eff_play_flag = false;
	}

}


gobj_Nabeita_Jiku::gobj_Nabeita_Jiku(int _jiku_no, gobj_Nabeita *_owner_nabe, double _jiku_rad, int _pict_no, int _mark_pict_no, int _magic_invocation_time, int _conf_eff_no, int _magic_eff_no, int _magic_ring_eff_no, int _sound_handle)
{
	jiku_rad = _jiku_rad;
	pict_no = _pict_no;
	mark_pict_no = _mark_pict_no;
	zokusei_value = 0.0;
	conf_eff_no = _conf_eff_no;
	magic_value = 0.0;
	magic_eff_no = _magic_eff_no;
	magic_eff_play_flag = false;
	magic_ring_eff_no = _magic_ring_eff_no;
	magic_ring_eff_play_flag = false;
	magic_invocation_time = _magic_invocation_time;
	magic_delta_time = 0;
	magic_pos_x = 0;
	magic_pos_y = 190;
	jiku_no = _jiku_no;
	owner_nabe = _owner_nabe;
	sound_handle = _sound_handle;
}


gobj_Nabeita_Jiku::~gobj_Nabeita_Jiku()
{
}

void gobj_Nabeita_Jiku::Pict(int p_x, int p_y, double rotate_rad)
{
	double _x = zokusei_value * -sin(jiku_rad);
	double _y = zokusei_value * -cos(jiku_rad);
	DrawRotaGraph(p_x + _x * cos(rotate_rad) - _y * sin(rotate_rad),
		p_y + _x * sin(rotate_rad) + _y * cos(rotate_rad),
		1.0, 0.0, pict_no, true, false);

	_x = magic_pos_y * -sin(jiku_rad);
	_y = magic_pos_y * -cos(jiku_rad);
	if (magic_eff_play_flag == true)
	{
		if (IsEffekseer2DEffectPlaying(magic_eff_play_no) == -1)
		{
			magic_eff_play_flag = false;
			
		}
		else
		{
			SetPosPlayingEffekseer2DEffect(magic_eff_play_no, p_x + _x * cos(rotate_rad) - _y * sin(rotate_rad),
				p_y + _x * sin(rotate_rad) + _y * cos(rotate_rad), 0);
		}
	}
	if (magic_ring_eff_play_flag == true)
	{
		if (IsEffekseer2DEffectPlaying(magic_ring_eff_play_no) == -1)
		{
			magic_ring_eff_play_flag = false;

		}
		else
		{
			SetPosPlayingEffekseer2DEffect(magic_ring_eff_play_no, p_x +_x * cos(rotate_rad) - _y * sin(rotate_rad),
				p_y + _x * sin(rotate_rad) + _y * cos(rotate_rad), 0);
		}
	}
}


void gobj_Nabeita_Jiku::Update()
{
	magic_delta_time += 1;
	if (magic_delta_time > magic_invocation_time - 90 && magic_ring_eff_play_flag == false)
	{
		owner_nabe->owner_gm->SoundManager->PlaySoundFile("sf_feel6");
		magic_ring_eff_play_flag = true;
		magic_ring_eff_play_no = PlayEffekseer2DEffect(magic_ring_eff_no);
		float eff_scale = 5.0f;
		SetScalePlayingEffekseer2DEffect(magic_ring_eff_play_no, eff_scale, eff_scale, eff_scale);
	}
	if (magic_delta_time > magic_invocation_time)
	{
		PlaySoundMem(sound_handle, MIM_BACKGROUND);
		magic_eff_play_flag = true;
		magic_eff_play_no = PlayEffekseer2DEffect(magic_eff_no);
		float eff_scale = 10.0f;
		SetScalePlayingEffekseer2DEffect(magic_eff_play_no, eff_scale, eff_scale, eff_scale);
		magic_delta_time = 0;
		owner_nabe->jiku_mahou_flags[jiku_no] = true;
		owner_nabe->jiku_mahou_values[jiku_no] = magic_value;
		magic_value = 0.0;
	}
}

