
#include <Windows.h>
#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "GameSystem.h"
#include "InputSignals.h"
#include "resource.h"

const TCHAR SOFT_TITLE[64] = "ナベシキマホウ ver 1.2";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウモード
	ChangeWindowMode(true);

	//Effekseerの為にDirectX9を指定し使用できるようにする
	SetUseDirect3DVersion(DX_DIRECT3D_9);

	//DXライブラリ初期化
	if (DxLib_Init() == -1) return -1;

	//アイコン、タイトルセット
	SetWindowText(SOFT_TITLE);
	SetWindowIconID(IDI_ICON1);

	//裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	//Effekseer初期化　引数に最大パーティクル数指定
	if (Effkseer_Init(2000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//フルスクリーンウィンドウの切り替えでリソースが消えるのを防ぐ
	//Effekseerのため必須
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	//DXライブラリのデバイスロストした時のコールバックを設定する
	//ウィンドウとフルスクリーンの切り替えが発生する場合は必ず実行する
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	//Effekseerに2D描画の設定
	Effekseer_Set2DSetting(640, 480);

	//何でもいいので画像を読み込む
	int grBackgroundHandle = LoadGraph("Data/effect/eff_texture/Particle01.png");
	int grFrontHandle = LoadGraph("Data/effect/eff_texture/Particle02.png");

	//時間を初期化する(定期的にエフェクトを再生するため
	int time = 0;

	// フルスクリーン切り替え用フラグを設定する。(F1、F2でウインドウ、フルスクリーンを切り替えれるようにする。)
	bool isFullScreen = false;

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	//GameMain作成
	GameMain* nabe_gm = new GameMain(gsTitleIns);

	while (!ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE) && !nabe_gm->game_end_flag)
	{
		// 何でもいいので画像を描画する。
		// こうして描画した後でないと、Effekseerは描画できない。
		DrawGraph(0, 450, grBackgroundHandle, TRUE);

		//ゲーム更新
		nabe_gm->Update();
		nabe_gm->Pict();

		// スクリーンを入れ替える。
		ScreenFlip();

		// 時間を経過させる。
		time++;

		// フルスクリーンの切り替えを行う。
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
	//GameMainの削除
	delete nabe_gm;

	// Effekseerを終了する。
	Effkseer_End();

	// DXライブラリを終了する。
	DxLib_End();

	return 0;
}