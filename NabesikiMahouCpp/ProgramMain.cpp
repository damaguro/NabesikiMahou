
#include <Windows.h>
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "GameSystem.h"
#include "InputSignals.h"
#include "resource.h"

const TCHAR SOFT_TITLE[64] = "�i�x�V�L�}�z�E ver 1.2";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h
	ChangeWindowMode(true);

	//Effekseer�ׂ̈�DirectX9���w�肵�g�p�ł���悤�ɂ���
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DX���C�u����������
	if (DxLib_Init() == -1) return -1;

	//�A�C�R���A�^�C�g���Z�b�g
	SetWindowText(SOFT_TITLE);
	SetWindowIconID(IDI_ICON1);

	//����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//Effekseer�������@�����ɍő�p�[�e�B�N�����w��
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//�t���X�N���[���E�B���h�E�̐؂�ւ��Ń��\�[�X��������̂�h��
	//Effekseer�̂��ߕK�{
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��
	//�E�B���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Effekseer��2D�`��̐ݒ�
	Effekseer_Set2DSetting(640, 480);

	//���ł������̂ŉ摜��ǂݍ���
	int grBackgroundHandle = LoadGraph("Data/effect/eff_texture/Particle01.png");
	int grFrontHandle = LoadGraph("Data/effect/eff_texture/Particle02.png");

	//���Ԃ�����������(����I�ɃG�t�F�N�g���Đ����邽��
	int time = 0;

	// �t���X�N���[���؂�ւ��p�t���O��ݒ肷��B(F1�AF2�ŃE�C���h�E�A�t���X�N���[����؂�ւ����悤�ɂ���B)
	bool isFullScreen = false;

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

	//GameMain�쐬
	GameMain* nabe_gm = new GameMain(gsTitleIns);

	while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE) && !nabe_gm->game_end_flag)
	{
		// ���ł������̂ŉ摜��`�悷��B
		// �������ĕ`�悵����łȂ��ƁAEffekseer�͕`��ł��Ȃ��B
		DrawGraph(0, 450, grBackgroundHandle, TRUE);

		//�Q�[���X�V
		nabe_gm->Update();
		nabe_gm->Pict();

		// �X�N���[�������ւ���B
		ScreenFlip();

		// ���Ԃ��o�߂�����B
		time++;

		// �t���X�N���[���̐؂�ւ����s���B
		if (CheckHitKey(KEY_INPUT_F1) && !isFullScreen)
		{
			ChangeWindowMode(FALSE);
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = true;
		}
		if (CheckHitKey(KEY_INPUT_F2) && isFullScreen)
		{
			ChangeWindowMode(TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			isFullScreen = false;
		}
	}
	//GameMain�̍폜
	delete nabe_gm;

	// Effekseer���I������B
	Effkseer_End();

	// DX���C�u�������I������B
	DxLib_End();

	return 0;
}