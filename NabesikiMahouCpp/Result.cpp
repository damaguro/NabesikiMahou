#include "GameSystem.h"

Result::~Result()
{
}

Result* Result::Instance()
{
	static Result result;
	return &result;
}
void Result::Enter(GameMain* gm)
{
	suuji_size_x = 32;
	suuji_size_mini_x = 24;
	suuji_size_y = 48;
	suuji_size_mini_y = 36;
	current_score_x = 500;
	current_score_y = 16;
	score_ranking_right_x = 500;
	score_ranking_y = 100;
	star_deltatime = 0;
	event_time = 60 * 10;
	feed_pic_head == NULL;
	deltatime = 0;
	if (gm->result_data_load_flag == false)
	{
		pict_datamap["nabe_sousa"] = LoadGraph("Data/picture/nabe_sousa.png");
		pict_datamap["ketsumatsu1"] = LoadGraph("Data/picture/ketsumatsu1.png");
		pict_datamap["ketsumatsu2"] = LoadGraph("Data/picture/ketsumatsu2.png");
		pict_datamap["ketsumatsu3"] = LoadGraph("Data/picture/ketsumatsu3.png");
		pict_datamap["ketsumatsu3_hametsu"] = LoadGraph("Data/picture/ketsumatsu3_hametsu.png");
		pict_datamap["door"] = LoadGraph("Data/picture/door.png");
		pict_datamap["mado_front"] = LoadGraph("Data/picture/mado_front.png");
		pict_datamap["mado_side"] = LoadGraph("Data/picture/mado_side.png");
		pict_datamap["hikari"] = LoadGraph("Data/picture/hikari.png");
		pict_datamap["hikari_single"] = LoadGraph("Data/picture/hikari_single.png");
		pict_datamap["great_burst"] = LoadGraph("Data/picture/great_burst.png");
		

		eff_datamap["smoke_burst"] = LoadEffekseerEffect("Data/effect/smoke_burst.efk");
		eff_datamap["smoke_l_single"] = LoadEffekseerEffect("Data/effect/smoke_l_single.efk");
		eff_datamap["smoke_s_single"] = LoadEffekseerEffect("Data/effect/smoke_s_single.efk");
		eff_datamap["hametsu"] = LoadEffekseerEffect("Data/effect/hametsu.efk");
 
		LoadDivGraph("Data/picture/suuji_toga_mini.png", 10, 10, 1, suuji_size_mini_x, suuji_size_mini_y, suuji_pict_datamap);
	}
	//得点検査
	ScoreLoad();
	now_score_ranking_no = -1;
	for (int i = 0; i < 10; i++)
	{
		if (gm->honban_score >= score_nodes[i].score)
		{
			for (int j = 9; j > i; j--)
			{
				score_nodes[j].score = score_nodes[j - 1].score;
			}
			score_nodes[i].score = gm->honban_score;
			now_score_ranking_no = i;
			break;
		}
	}
	ScoreWrite();

	
	if (gm->honban_score < 20000)
		end_pattern = 0;
	else if (gm->honban_score < 30000)
		end_pattern = 1;
	else
		end_pattern = 2;
		
	//end_pattern = 2;
}

void Result::Execute(GameMain* gm)
{
	if (InputSignalsIns->Oneshot_Space == 1)
	{
		gm->SoundManager->PlaySoundFile("coin");
		gm->ChangeScene(gsTitleIns);
	}
}

void Result::Exit(GameMain* gm)
{
	ClearFeedPic();
}

void Result::Pict(GameMain* gm)
{
	//背景エンド描画
	switch (end_pattern)
	{
	case 0:
		if (deltatime < 60)
			DrawGraph(0, 0, pict_datamap["nabe_sousa"], true);
		else
			DrawGraph(0, 0, pict_datamap["ketsumatsu1"], true);

		if (deltatime == 5)
		{
			gm->SoundManager->PlaySoundFile("fire4");
			AddFeedPic(pict_datamap["hikari"], 280, 230, 0.0, 60, 40, 0);
		}
		if (deltatime == 50)
		{
			gm->SoundManager->PlaySoundFile("bomb34");
			SetSmokeBurst(200, 360);
		}
		if (55 < deltatime && deltatime < 300)
		{
			if (deltatime % 5)
				SetSmokeSingle(230 + GetRand(40), 360 + GetRand(10));
		}
		break;

	case 1:
		if (deltatime < 60)
			DrawGraph(0, 0, pict_datamap["nabe_sousa"], true);
		else
			DrawGraph(0, 0, pict_datamap["ketsumatsu2"], true);
		if (deltatime == 60)
		{
			//front_window
			AddFeedPic(pict_datamap["mado_front"], 340, 290, 0.0, 75, 0, 0);
			//door
			AddFeedPic(pict_datamap["door"], 410, 330, 0.0, 75, 0, 0);
			//side_window
			AddFeedPic(pict_datamap["mado_side"], 200, 300, 0.0, 75, 0, 0);
		}
		if (deltatime == 5)
		{
			gm->SoundManager->PlaySoundFile("fire4");
			AddFeedPic(pict_datamap["hikari"], 280, 230, 0.0, 60, 40, 0);
		}

		if (deltatime == 75)
		{
			gm->SoundManager->PlaySoundFile("bomb34");
			gm->SoundManager->PlaySoundFile("bomb2t");
			//front_window
			SetSmokeBurst(340, 290);
			AddFeedPic(pict_datamap["great_burst"], 210, 430, DX_PI * 3 / 4, 180, 0, 60);
			//door
			SetSmokeBurst(410, 330);
			AddFeedPic(pict_datamap["great_burst"], 570, 330, 0.0, 180, 0, 60);

			//side_window
			SetSmokeBurst(180, 280);
			AddFeedPic(pict_datamap["great_burst"], 30, 300, DX_PI, 180, 0, 60);

		}
		if (75 < deltatime && deltatime < 180)
		{
			if (deltatime % 2 == 0)
			{
				//front_window
				SetSmokeSingle(340, 290);
				//door
				SetSmokeSingle(410, 330);
				//side_window
				SetSmokeBurst(180, 280);
			}
		}
		break;

	case 2:
		if (deltatime < 60)
			DrawGraph(0, 0, pict_datamap["nabe_sousa"], true);
		else if (deltatime < 100)
			DrawGraph(0, 0, pict_datamap["ketsumatsu3"], true);
		else
			DrawGraph(0, 0, pict_datamap["ketsumatsu3_hametsu"], true);

		if (deltatime == 5)
		{
			gm->SoundManager->PlaySoundFile("fire4");
			AddFeedPic(pict_datamap["hikari"], 280, 230, 0.0, 60, 40, 0);
		}
		if (60 < deltatime && deltatime < 120)
		{
			if (deltatime % 10 == 0)
			{
				gm->SoundManager->PlaySoundFile("bomb2");
				int _ep_no = PlayEffekseer2DEffect(eff_datamap["hametsu"]);
				float scale = (deltatime - 50) / 2;
				SetScalePlayingEffekseer2DEffect(_ep_no, scale, scale, scale);
				SetPosPlayingEffekseer2DEffect(_ep_no, 300, 320, 0);
			}
		}
		if (deltatime > 100 && deltatime < event_time)
		{
			if (deltatime % 5 == 0)
			{
				SetSmokeSingle(10 + GetRand(620), 10 + GetRand(460));
			}
		}
		break;

	default:;
	}
	UpdateFeedPic();

	//得点描画
	if (star_deltatime >= 60) star_deltatime = 0;
	ColorNumberPict(gm->honban_score, current_score_x, current_score_y);
	for (int i = 0; i < 10; i++)
	{
		MiniNumberPict(score_nodes[i].score, score_ranking_right_x, score_ranking_y + (suuji_size_mini_y + 2) * i);

		if (i == now_score_ranking_no)
		{
			DrawGraph(score_ranking_right_x, score_ranking_y + (suuji_size_mini_y + 2) * i + 2, gsTitleIns->star_pict_datamap[star_deltatime], true);
		}
	}
	star_deltatime++;
	if (deltatime < event_time)
	deltatime++;
}

void Result::UIPict(GameMain* gm)
{

}

void Result::ColorNumberPict(long score, int score_x, int score_y)
{
	int i = 0;
	if (score == 0)
	{
		DrawGraph(score_x - suuji_size_x, score_y, gsHonbanIns->color_number_pict_datamap[0][0], true);
	}
	for (long _score_pict = score; _score_pict > 0; _score_pict /= 10)
	{
		DrawGraph(score_x - suuji_size_x * (i + 1), score_y, gsHonbanIns->color_number_pict_datamap[i % 4][_score_pict % 10], true);
		i++;
	}
}


void Result::MiniNumberPict(long score, int score_x, int score_y)
{
	int i = 0;
	if (score == 0)
	{
		DrawGraph(score_x - suuji_size_mini_x, score_y, suuji_pict_datamap[0], true);
	}
	for (long _score_pict = score; _score_pict > 0; _score_pict /= 10)
	{
		DrawGraph(score_x - suuji_size_mini_x * (i + 1), score_y, suuji_pict_datamap[_score_pict % 10], true);
		i++;
	}
}


void Result::ScoreLoad()
{
	FILE *fp;
	if (fopen_s(&fp, "save.dat", "rb") != 0)
	{
		//ファイルが無い
		for (int i = 0; i < 10; i++)
			score_nodes[i].score = 0;
	}
	else
	{
		string str, strm;
		for (int i = 0; i < 10; i++)
		{
			fread(&(score_nodes[i].score), sizeof(score_nodes[i].score), 1, fp);
		}
		fclose(fp);
	}
}


void Result::ScoreWrite()
{
	FILE *fp;
	if (fopen_s(&fp, "save.dat", "wb")) return;		//ファイルが開けなかった場合何もしない
	for (int i = 0; i < 10; i++)
	{
		fwrite(&(score_nodes[i].score), sizeof(score_nodes[i].score), 1, fp);
	}
	fclose(fp);
}



void Result::AddFeedPic(int _pict_no, int _x, int _y, double _rad, int _limit, int _feedin, int _feedout)
{
	feed_picture* _new_pic = new feed_picture;
	_new_pic->deltatime = 0;
	_new_pic->pict_no = _pict_no;
	_new_pic->x = _x;
	_new_pic->y = _y;
	_new_pic->rad = _rad;
	_new_pic->limittime = _limit;
	_new_pic->feedin_time = _feedin;
	_new_pic->feedout_time = _feedout;
	_new_pic->next = NULL;
	if (feed_pic_head == NULL)
	{
		feed_pic_head = _new_pic;
		_new_pic->prev = NULL;
	}
	else
	{
		feed_picture* _feed;
		for (_feed = feed_pic_head; _feed->next != NULL; _feed = _feed->next);
		_new_pic->prev = _feed;
		_feed->next = _new_pic;
	}
}


void Result::DelFeedPic(feed_picture* del_feed)
{

	if (del_feed->prev != NULL)
		del_feed->prev->next = del_feed->next;
	else
		feed_pic_head = del_feed->next;
	if (del_feed->next != NULL)
	{
		del_feed->next->prev = del_feed->prev;
	}
}


void Result::ClearFeedPic()
{
	feed_picture *_feed, *_feed_next;
	for (_feed = feed_pic_head; _feed != NULL; _feed = _feed_next)
	{
		_feed_next = _feed->next;
		delete _feed;
	}
}


void Result::UpdateFeedPic()
{
	feed_picture *_feed, *_feed_next;
	for (_feed = feed_pic_head; _feed != NULL; _feed = _feed_next)
	{
		_feed_next = _feed->next;
		if (_feed->deltatime > _feed->limittime)
			DelFeedPic(_feed);
		else
		{
			if (_feed->deltatime < _feed->feedin_time)
			{
				if (_feed->feedin_time > 0)
				{
					int _pal = (double)_feed->deltatime / _feed->feedin_time * 255;
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);
				}
			}
			else if (_feed->deltatime > _feed->limittime - _feed->feedout_time)
			{
				if (_feed->feedout_time > 0)
				{
					int _pal = (double)(_feed->limittime - _feed->deltatime) / _feed->feedout_time * 255;
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);
				}
			}
			DrawRotaGraph(_feed->x, _feed->y, 1.0, _feed->rad, _feed->pict_no, true, false);
			_feed->deltatime++;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void Result::SetSmokeSingle(int x, int y)
{
	int _ep_no;
	if (GetRand(9) < 4)
	{
		_ep_no = PlayEffekseer2DEffect(eff_datamap["smoke_l_single"]);
		float scale = 40.0f;
		SetScalePlayingEffekseer2DEffect(_ep_no, scale, scale, scale);
	}
	else
	{
		_ep_no = PlayEffekseer2DEffect(eff_datamap["smoke_s_single"]);
		float scale = 40.0f;
		SetScalePlayingEffekseer2DEffect(_ep_no, scale, scale, scale);
	}
	SetPosPlayingEffekseer2DEffect(_ep_no, x, y, 0);
}


void Result::SetSmokeBurst(int x, int y)
{
	int _ep_no;
	_ep_no = PlayEffekseer2DEffect(eff_datamap["smoke_burst"]);
	float scale = 50.0f;
	SetScalePlayingEffekseer2DEffect(_ep_no, scale, scale, scale);
	SetPosPlayingEffekseer2DEffect(_ep_no, x, y, 0);
}
