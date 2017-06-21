#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../directInput.h"

#include "GameOver.h"
#include "Title.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer)
{

}

GameOver::~GameOver()
{

}

//初期化関数
void GameOver::Initialize()
{
	GameOverTex.Load("Material/gameover.png");
	GameOverSprite.SetPos(600, 450);
	GameOverSprite.SetSize(1200, 1000);

	RetryTex.Load("Material/retry.png");
	RetrySptite.SetPos(300, 700);
	RetrySptite.SetSize(300, 200);

	TitleGoTex.Load("Material/titlego.png");
	TitleGoSprite.SetPos(900, 700);
	TitleGoSprite.SetSize(300, 200);

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(1);

	FadeFlag = false;

	gameoverState = FADE;

	sound.Initialize();
	se.Initialize();
}

//描画関数
void GameOver::Draw()
{
	Direct3D::DrawSprite(GameOverSprite, GameOverTex);

	Direct3D::DrawSprite(RetrySptite, RetryTex);
	Direct3D::DrawSprite(TitleGoSprite, TitleGoTex);

	//フェードイン、アウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

//メインの動作
void GameOver::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.GameOverSoundPlay();

	switch (gameoverState)
	{
	case FADE:	//フェードイン

		//フェードイン開始
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_IN_CHANGENUM));

		//フェードインが終了したタイミングでStateを切り替える
		if (FadeSprite.GetAlpha() == FADE_IN_END)
		{
			gameoverState = RETRY;
		}

		break;

	case RETRY:	//同じ難易度で再開

		//ボタンのサイズを変更
		RetrySptite.SetSize(350, 250);
		TitleGoSprite.SetSize(300, 200);

		//再開か、タイトルへ移動か決定してなければ処理
		//どちらにするか選択するか決定したりする
		if (FadeFlag == false)
		{
			//タイトルへを選ぶ
			if (pDi->KeyJustPressed(DIK_RIGHT) || pDi->KeyJustPressed(DIK_LEFT))
			{
				gameoverState = TITLEGO;
				se.ChoiceSEPlay();
			}

			//同じ難易度で再開
			if (pDi->KeyJustPressed(DIK_SPACE))
			{
				se.DecisionSEPlay();
				//フェードアウト開始
				FadeFlag = true;
			}
		}

		//テクスチャのα値が1になったらBGMを止めて遷移開始
		if (FadeSprite.GetAlpha() == FADE_OUT_END)
		{
			sound.GameOverSoundStop();
			switch (dif)
			{
			case EASY:
				mSceneChanger->ChangeScene(STATE_EASY);
				break;
			case NORMAL:
				mSceneChanger->ChangeScene(STATE_NORMAL);
				break;
			case HARD:
				mSceneChanger->ChangeScene(STATE_HARD);
				break;
			}
		}

		break;

	case TITLEGO:	//タイトルへ遷移

		//基本的な流れは上記と一緒の為
		//コメントは上記を参照してください

		RetrySptite.SetSize(300, 200);
		TitleGoSprite.SetSize(350, 250);

		if (FadeFlag == false)
		{
			if (pDi->KeyJustPressed(DIK_RIGHT) || pDi->KeyJustPressed(DIK_LEFT))
			{
				gameoverState = RETRY;
				se.ChoiceSEPlay();
			}

			if (pDi->KeyJustPressed(DIK_SPACE))
			{
				se.DecisionSEPlay();
				FadeFlag = true;
			}
		}

		if (FadeSprite.GetAlpha() == FADE_OUT_END)
		{
			sound.GameOverSoundStop();
			mSceneChanger->ChangeScene(STATE_TITLE);
		}

		break;
	}



	//FadeFlagがtrueなら実行するように
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}


}

