#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"
#include "../BoundingBox.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"

#include "Title.h"

//フェードアウト用の数値
#define FADE_OUT_CHANGENUM 1 
#define FADE_OUT_END 1
//フェードイン用の数値
#define FADE_IN_CHANGENUM -1 
#define FADE_IN_END 0

//フェードイン、アウトのスピード
#define FADE_SPEED 0.01f

#define BUTTON_DRAW_SPEED 30
#define BUTTON_DRAW_TIMING 0


enum GAMEOVERSTATE
{
	FADE,
	RETRY,
	TITLEGO,
};

class GameOver : public BaseScene
{
private:

	//ゲームオーバー画面のテクスチャ
	Texture GameOverTex;
	Sprite GameOverSprite;

	//リトライのテクスチャ
	Texture RetryTex;
	Sprite RetrySptite;

	//タイトルへのテクスチャ
	Texture TitleGoTex;
	Sprite TitleGoSprite;

	//フェードイン、アウト用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

	GAMEOVERSTATE gameoverState;

	int ButtonDrawCount;
	bool ButtonDrawFlag;

	//フェードアウトを実行するかのフラグ
	//スペースキーを押したならtrueにする
	bool FadeFlag;


	Sound sound;
	SoundEffect se;

public:

	//コンストラクタ
	GameOver::GameOver(ISceneChanger* changer);

	//デストラクタ
	~GameOver();

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	void ButtonDrawSet();

};