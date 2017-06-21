#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "../Global.h"
#include "Sound.h"
#include "SoundEffect.h"


#define BUTTON_MOVE_SPEED 20
#define DIFFICULTY_NUM 3

//難易度
enum DIFFICULTY
{
	EASY,
	NORMAL,
	HARD,
};

//タイトルのフロー
enum TITLESTATE
{
	START,
	BUTTONMOVE,
	SELECT,
};

extern DIFFICULTY dif;

class Title : public BaseScene
{
private:

	//タイトルのテクスチャ
	Texture TitleTex;
	Sprite TitleSprite;

	//エンターキーを押してもらう指示のテクスチャ
	Texture EnterTex;
	Sprite EnterSprite;

	//難易度選択用のテクスチャ（Easy）
	Texture EasyTex;
	Sprite EasySptite;

	//難易度選択用のテクスチャ（Normal）
	Texture NormalTex;
	Sprite NormalSptite;

	//難易度選択用のテクスチャ（Hard）
	Texture HardTex;
	Sprite HardSptite;


	//フェードアウト用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

	//フェードアウトを実行するかのフラグ
	//スペースキーを押したならtrueにする
	bool FadeFlag;

	//操作を促すフォントを点滅させるための変数
	int DrawCount;
	bool DrawFlag;

	//ボタンのx座標
	int ButtonMoveNum[DIFFICULTY_NUM];
	//ボタン移動開始のフラグ
	bool ButtonMoveFlag;

	//選択してある難易度
	DIFFICULTY difficulty;
	//タイトル画面でのフロー
	TITLESTATE titleState;

	//代入用の変数
	DIFFICULTY difficultySelect[DIFFICULTY_NUM];

	Sound sound;
	SoundEffect se;

	//ボタンのサイズの標準
	int ButtonSizeStandardX;
	int ButtonSizeStandardY;
	//ボタンのサイズの最大値
	int ButtonSizeMaxX;
	int ButtonSizeMaxY;

public:
	//コンストラクタ
	Title::Title(ISceneChanger* changer);
	//デストラクタ
	~Title();

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	void DifficultySelect(DIFFICULTY dif1, DIFFICULTY dif2);

	void PushKeyDraw();

};