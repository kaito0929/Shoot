#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Normal.h"

Normal::Normal(ISceneChanger* changer) : BaseScene(changer)
{

}

Normal::~Normal()
{

}

//初期化関数
void Normal::Initialize()
{
	player.Initialize();
	player.NormalInitialize();
	sound.Initialize();
}

//描画関数
void Normal::Draw()
{
	player.Draw();
	player.NormalDraw();
}

void Normal::Update()
{
	player.Update();
	player.NormalUpdate();
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