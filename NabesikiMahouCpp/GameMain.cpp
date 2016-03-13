#include "GameSystem.h"

GameMain::GameMain(gmScene* init_scene)
{
	honban_data_load_flag = false;
	title_data_load_flag = false;
	result_data_load_flag = false;
	gmCurrentScene = init_scene;
	gmCurrentScene->Enter(this);
	scene_fadeout_deltatime = -1;
	scene_fadeout_limittime = 30;
	scene_fadein_deltatime = -1;
	scene_fadein_limittime = 10;
	game_end_flag = false;
	ChangeAllEffectPictMode();
	SoundManager = new TsuSoundManager();
	SoundManager->NabeSoundLoad();
	SoundManager->PlayBGM026();
}


GameMain::~GameMain()
{
}


void GameMain::Update()
{
	if (scene_fadeout_deltatime == -1)
	{
		InputSignalsIns->InputCheck();
		gmCurrentScene->Execute(this);
	}
	else
	{
		scene_fadeout_deltatime++;
		int _bright = 255 - (double)scene_fadeout_deltatime / scene_fadein_limittime * 255;
		SetDrawBright(_bright, _bright, _bright);
		if (scene_fadeout_deltatime > scene_fadeout_limittime)
		{
			scene_fadeout_deltatime = -1;
			GotoNextScene();
		}
	}
	if (scene_fadein_deltatime >= 0)
	{
		scene_fadein_deltatime++;
		int _bright = (double)scene_fadein_deltatime / scene_fadein_limittime * 255;
		SetDrawBright(_bright, _bright, _bright);
	}
	if (scene_fadein_deltatime > scene_fadein_limittime)
	{
		SetDrawBright(255, 255, 255);
		scene_fadein_deltatime = -1;
	}
}

void GameMain::Pict()
{
	gmCurrentScene->Pict(this);
	EffectPict();
	gmCurrentScene->UIPict(this);
}


void GameMain::ChangeScene(gmScene* _new_scene)
{
	gmNextScene = _new_scene;
	gmNextScene->Enter(this);
	scene_fadeout_deltatime = 0;
}


void GameMain::CallMenuWithPause(gmScene* _new_menu_scene)
{
	SoundManager->AllSoundStop();
	ChangeDesignationEffectPictMode();
	gmPauseScene = gmCurrentScene;
	gmCurrentScene = _new_menu_scene;
	gmCurrentScene->Enter(this);
}


void GameMain::BackFromMenuWithPause()
{
	CrearTemporarySceneEffect();
	ChangeAllEffectPictMode();
	gmCurrentScene->Exit(this);
	gmCurrentScene = gmPauseScene;
	gmPauseScene = nullptr;
	gmCurrentScene->Execute(this);
}


void GameMain::GotoNextScene()
{
	scene_fadein_deltatime = 0;
	gmCurrentScene->Exit(this);
	eff_manager_2D = GetEffekseer2DManager();
	eff_manager_2D->StopAllEffects();
	SoundManager->AllSoundStop();
	gmCurrentScene = gmNextScene;
}


void GameMain::ReturnTitleWithReset()
{
	//CrearTemporarySceneEffect();
	eff_manager_2D = GetEffekseer2DManager();
	eff_manager_2D->StopAllEffects();
	SoundManager->AllSoundStop();
	ChangeAllEffectPictMode();
	gmPauseScene->Exit(this);
	ChangeScene(gsTitleIns);
}

void GameMain::EffectPict()
{
	(this->*(effect_pict_method))();
}


void GameMain::ChangeAllEffectPictMode()
{
	effect_pict_method = &GameMain::AllEffectPict;
}

//�ꎞ�V�[���p�̃G�t�F�N�g�`�惂�[�h�ɐ؂�ւ�
void GameMain::ChangeDesignationEffectPictMode()
{
	effect_pict_method = &GameMain::TemporarySceneEffectPict;
	eff_manager_2D = GetEffekseer2DManager();	//�r����Manager���������肷��ւ��Ȃ����Ƃ�M���āc
}


void GameMain::AllEffectPict()
{
	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer2D();
	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer2D();
}

//���̈ꎞ�V�[���̃G�t�F�N�g��`��@�Վ��V�[���̃G�t�F�N�g�n���h����temporary...��GameMain������
void GameMain::TemporarySceneEffectPict()
{
	eff_manager_2D->BeginUpdate();
	DrawEffekseer2D_Begin();
	const EffekseerEffectHandle_fList::const_iterator itEnd = temporary_scene_play_eff_handle_list.end();
	for (EffekseerEffectHandle_fList::const_iterator it = temporary_scene_play_eff_handle_list.begin();
		it != itEnd;)
	{
		if (IsEffekseer2DEffectPlaying(*it) != 0)
		{
			it = temporary_scene_play_eff_handle_list.erase(it);
			continue;
		}
		else
		{
			eff_manager_2D->UpdateHandle(*it);

			DrawEffekseer2D_Draw(*it);
			++it;
		}
	}
	eff_manager_2D->EndUpdate();
	DrawEffekseer2D_End();
}

//�ꎞ�V�[����������G�t�F�N�g��S�폜
void GameMain::CrearTemporarySceneEffect()
{
	const EffekseerEffectHandle_fList::const_iterator itEnd = temporary_scene_play_eff_handle_list.end();
	for (EffekseerEffectHandle_fList::const_iterator it = temporary_scene_play_eff_handle_list.begin();
		it != itEnd; ++it)
	{
		eff_manager_2D->StopEffect(*it);
	}
	temporary_scene_play_eff_handle_list.clear();
}

/**
@brief	�ꎞ�V�[���p�ɃG�t�F�N�g���Đ����X�g��manager�ɓo�^����
@param	effectHandle	�G�t�F�N�g�̃n���h��
@return	-1�ȊO:�Đ����̃G�t�F�N�g�̃n���h���A-1:���s
*/
int GameMain::PlayEffekseer2DEffectByTemporaryScene(int effectHandle)
{
	int eff_play_handle;
	if ((eff_play_handle = PlayEffekseer2DEffect(effectHandle)) != -1)
		temporary_scene_play_eff_handle_list.push_front(eff_play_handle);
	return eff_play_handle;
}
