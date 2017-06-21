#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

#include "Result.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//リザルト画面のテクスチャ
	ResultTex.Load("Material/result.png");
	ResultSprite.SetPos(600, 450);
	ResultSprite.SetSize(1200, 1000);

	//スペースキーを押すように指示するテクスチャ
	EnterTex.Load("Material/pushspace.png");
	EnterSprite.SetPos(600, 700);
	EnterSprite.SetSize(650, 450);

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

	sound.Initialize();
	se.Initialize();
}

void Result::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	Direct3D::DrawSprite(ResultSprite, ResultTex);

	if (DrawFlag == true)
	{
		//スペースキーを押すように指示
		Direct3D::DrawSprite(EnterSprite, EnterTex);
	}

	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

void Result::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.ClearSoundPlay();

	//エンターキーを押したならフラグをtrueにしてフェードアウト開始
	if (pDi->KeyJustPressed(DIK_SPACE))
	{
		if (FadeFlag == false)
		{
			se.DecisionSEPlay();
		}
		FadeFlag = true;
	}

	//FadeFlagがtrueなら実行するように
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}

	//完全に画面が暗くなったならシーンをメインゲームに変更
	if (FadeSprite.GetAlpha() == FADE_OUT_END)
	{
		sound.ClearSoundStop();
		mSceneChanger->ChangeScene(STATE_TITLE);
	}

	TextureFlashing();
}

void Result::TextureFlashing()
{
	//カウントをプラス
	DrawCount++;

	//フラグのtrue,falseを切り替えることによって
	//テクスチャの表示非表示を切り替える
	if (DrawFlag == false)
	{
		if (DrawCount % TEXTURE_DARW_SPEED == TEXTURE_DARW_TIMING)
		{
			DrawFlag = true;
		}
	}
	else
	{
		if (DrawCount % TEXTURE_DARW_SPEED == TEXTURE_DARW_TIMING)
		{
			DrawFlag = false;
		}
	}

}