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

#include "Sound.h"
#include "SoundEffect.h"

//フェードアウト用の数値
#define FADE_OUT_CHANGENUM 1 


class Result : public BaseScene
{
private:

	//1Pが勝利した場合に表示するテクスチャ
	Texture ResultTex;
	Sprite ResultSprite;

	//エンターキーを押してもらう指示のテクスチャ
	Texture EnterTex;
	Sprite EnterSprite;

	//フェードアウト用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

	//フェードアウトを実行するかのフラグ
	//エンターキーを押したならtrueにする
	bool FadeFlag;

	//エンターキーの操作を促すフォントを点滅させるための変数
	int EnterDrawCount;
	int EnterFlashingNum;

	Sound sound;
	SoundEffect se;

public:
	//コンストラクタ
	Result::Result(ISceneChanger* changer);
	//デストラクタ
	~Result();

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;
};