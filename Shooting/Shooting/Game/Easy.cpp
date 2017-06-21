#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Easy.h"

Easy::Easy(ISceneChanger* changer) : BaseScene(changer)
{

}

Easy::~Easy()
{

}

//初期化関数
void Easy::Initialize()
{
	player.Initialize();
	player.EasyInitialize();
	sound.Initialize();
	se.Initialize();

	StartTexPosX = 1400;
	StartCount = 0;

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(1);

	StartTex.Load("Material/start.png");
	StartSprite.SetPos(StartTexPosX,300);
	StartSprite.SetSize(400, 200);

	playState = FADE_IN;
}

//描画関数
void Easy::Draw()
{
	StartSprite.SetPos(StartTexPosX, 300);

	player.Draw();
	player.EasyDraw();

	Direct3D::DrawSprite(StartSprite, StartTex);

	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Easy::Update()
{

	switch (playState)
	{
	case FADE_IN:		//フェードイン開始

		//フェードインを実行
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_IN_CHANGENUM));

		//完全に画面が暗くなったならシーンを遷移
		if (FadeSprite.GetAlpha() == FADE_IN_END)
		{
			playState = START_SIGNAL;
		}

		break;
	case START_SIGNAL:		//ゲームスタートの合図

		//スタートのテクスチャを画面中央まで移動
		if (StartTexPosX != SCREEN_CENTERX)
		{
			StartTexPosX -= STARTTEX_MOVE;
		}
		else
		{
			//画面中央に移動したらSEを再生
			se.StartSEPlay();
			//プレイヤーの操作が可能になるまでのカウントを加算
			StartCount++;
		}

		//カウントが10を超えたらプレイヤーの操作を可能に
		if (StartCount >= START_COUNT_MAX)
		{
			playState = MAIN;
		}

		break;
	case MAIN:		//プレイヤーの操作

		player.Update();
		player.EasyUpdate();
		sound.MainSoundPlay();

		//プレイヤーが何かと衝突したら処理
		//フェードアウトを開始し、ゲームオーバー画面へ遷移する
		if (player.GetAliveFlag() == false)
		{
			FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_OUT_CHANGENUM));

			//完全に画面が暗くなったならシーンを遷移
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.MainSoundStop();
				mSceneChanger->ChangeScene(STATE_GAMEOVER);
			}
		}

		if (player.GetOllBreakFlag() == true && player.GetAliveFlag() == true)
		{
			FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_OUT_CHANGENUM));

			//完全に画面が暗くなったならシーンを遷移
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.MainSoundStop();
				mSceneChanger->ChangeScene(STATE_RESULT);
			}
		}

		//スタートのテクスチャを画面外に移動
		if (StartTexPosX != SCREEN_OUT)
		{
			StartTexPosX -= STARTTEX_MOVE;
		}

		break;
	}


	
}