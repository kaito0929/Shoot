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
#include "SoundEffect.h"
#include "../Global.h"



class Easy : public BaseScene
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
	Easy::Easy(ISceneChanger* changer);

	//デストラクタ
	~Easy();


	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;


};