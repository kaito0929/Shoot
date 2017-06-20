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

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

}

//描画関数
void Easy::Draw()
{
	player.Draw();
	player.EasyDraw();

	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Easy::Update()
{
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
}