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

	//エンターキーの操作を促すフォントを点滅させるための変数
	int EnterDrawCount;
	int EnterFlashingNum;

	int ButtonMoveNum[3];


	Sound sound;
	SoundEffect se;

	DIFFICULTY difficulty;
	TITLESTATE titleState;

	DIFFICULTY difficultySelect[3];
	bool ButtonMoveFlag;

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

};