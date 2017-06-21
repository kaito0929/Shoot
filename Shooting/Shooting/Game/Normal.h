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

#include "Player.h"
#include "Sound.h"
#include "Easy.h"
#include "../Global.h"

class Normal : public BaseScene
{
private:

	Player player;
	Sound sound;
	SoundEffect se;

	//フェードアウト用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

	//ゲーム開始の合図を行うテクスチャ
	Texture StartTex;
	Sprite StartSprite;

	//スタートのテクスチャのx座標
	int StartTexPosX;
	//スタートの合図がしてからのインターバル
	int StartCount;

	PLAYSTATE playState;


public:

	//コンストラクタ
	Normal::Normal(ISceneChanger* changer);

	//デストラクタ
	~Normal();


	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;


};