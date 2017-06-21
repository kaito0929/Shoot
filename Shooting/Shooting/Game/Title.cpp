#include "Title.h"
#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

//ゲームオーバー画面でのリトライを選んだ際に
//遷移するシーンを決定するグローバル変数
DIFFICULTY dif;

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

Title::~Title()
{

}

void Title::Initialize()
{
	//タイトルロゴ
	TitleTex.Load("Material/title.png");
	TitleSprite.SetPos(600, 450);
	TitleSprite.SetSize(1200, 1000);

	//エンターを押すように指示するテクスチャ
	EnterTex.Load("Material/pushspace.png");
	EnterSprite.SetPos(600, 800);
	EnterSprite.SetSize(600, 400);

	//フェードアウト用のテクスチャ
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

	//イージー
	EasyTex.Load("Material/easy.png");
	EasySptite.SetPos(1400, 400);
	EasySptite.SetSize(400, 130);

	//ノーマル
	NormalTex.Load("Material/normal.png");
	NormalSptite.SetPos(1600, 600);
	NormalSptite.SetSize(400, 130);

	//ハード
	HardTex.Load("Material/hard.png");
	HardSptite.SetPos(1800, 800);
	HardSptite.SetSize(400, 130);

	ButtonMoveNum[0] = 1400;
	ButtonMoveNum[1] = 1600;
	ButtonMoveNum[2] = 1800;

	ButtonSizeStandardX = 400;
	ButtonSizeStandardY = 130;
	ButtonSizeMaxX = 450;
	ButtonSizeMaxY = 180;

	sound.Initialize();
	se.Initialize();

	difficulty = EASY;
	titleState = START;

	difficultySelect[0] = EASY;
	difficultySelect[1] = NORMAL;
	difficultySelect[2] = HARD;


	DrawCount = 0;
	DrawFlag = true;

	ButtonMoveFlag = false;
}


void Title::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	//タイトル画面の描画
	Direct3D::DrawSprite(TitleSprite, TitleTex);

	if (titleState == START)
	{
		if (DrawFlag == true)
		{
			//エンターキーを押すように指示
			Direct3D::DrawSprite(EnterSprite, EnterTex);
		}
	}

	EasySptite.SetPos(ButtonMoveNum[0], 400);
	NormalSptite.SetPos(ButtonMoveNum[1], 600);
	HardSptite.SetPos(ButtonMoveNum[2], 800);


	Direct3D::DrawSprite(EasySptite, EasyTex);
	Direct3D::DrawSprite(NormalSptite, NormalTex);
	Direct3D::DrawSprite(HardSptite, HardTex);

	//フェードアウト用の画像を描画
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Title::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.TitleSoundPlay();

	switch (titleState)
	{
	case START:		//スペースキーを押すように指示

		PushKeyDraw();

		//スペースキーを押したら処理
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			titleState = BUTTONMOVE;
			se.DecisionSEPlay();
		}

		break;
	case BUTTONMOVE:	//ボタンを移動させる

		//三つのボタンの位置が画面中央に移動するように処理
		for (int i = 0; i < DIFFICULTY_NUM; i++)
		{
			if (ButtonMoveNum[i] != SCREEN_CENTERX)
			{
				ButtonMoveNum[i] -= BUTTON_MOVE_SPEED;
				ButtonMoveFlag = false;
			}
			else
			{
				//ボタンの移動が完了したフラグ
				ButtonMoveFlag = true;
			}
		}

		//ボタンの移動が完了したフラグがtrueになれば処理
		if (ButtonMoveFlag == true)
		{
			//難易度選択へ
			titleState = SELECT;
		}

		break;
	case SELECT:	//難易度選択

		//選択している難易度によってボタンのサイズを変えたり
		//遷移するシーンを変更する
		switch (difficulty)
		{
		case EASY:		//イージーモード

			//イージーモードを選択しているボタンのサイズを大きく
			EasySptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//他のボタンは標準サイズの変更しておく
			NormalSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			HardSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);

			DifficultySelect(difficultySelect[2], difficultySelect[1]);
			dif = EASY;

			//完全に画面が暗くなったならシーンをメインゲームに変更
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_EASY);
			}

			break;
		case NORMAL:		//ノーマルモード

			//ノーマルモードを選択しているボタンのサイズを大きく
			NormalSptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//他のボタンは標準サイズの変更しておく
			EasySptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			HardSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);

			DifficultySelect(difficultySelect[0], difficultySelect[2]);
			dif = NORMAL;

			//完全に画面が暗くなったならシーンをメインゲームに変更
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_NORMAL);
			}

			break;
		case HARD:		//ハードモード

			//ハードモードを選択しているボタンのサイズを大きく
			HardSptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//他のボタンは標準サイズの変更しておく
			EasySptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			NormalSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			
			DifficultySelect(difficultySelect[1], difficultySelect[0]);
			dif = HARD;

			//完全に画面が暗くなったならシーンをメインゲームに変更
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_HARD);
			}
			break;
		}

		//難易度選択してスペースキーを押したらフェードアウト開始
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				FadeFlag = true;
				se.DecisionSEPlay();
			}
		}


		break;
	}

	//FadeFlagがtrueなら実行するように
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}

	
}


//難易度選択を処理する関数
void Title::DifficultySelect(DIFFICULTY dif1, DIFFICULTY dif2)
{
	DirectInput* pDi = DirectInput::GetInstance();

	//フェードアウトが開始していなければ処理
	if (FadeFlag == false)
	{
		//上キーを押したらその上の難易度に代入
		if (pDi->KeyJustPressed(DIK_UP))
		{
			difficulty = dif1;
			se.ChoiceSEPlay();
		}

		//下キーを押したらその下の難易度に代入
		if (pDi->KeyJustPressed(DIK_DOWN))
		{
			difficulty = dif2;
			se.ChoiceSEPlay();
		}
	}
}

//テクスチャを点滅させるための処理
void Title::PushKeyDraw()
{
	//カウントをプラス
	DrawCount++;

	//フラグをtrueとfalseに切り替えることによって
	//テクスチャの表示非表示を切り替えていく
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