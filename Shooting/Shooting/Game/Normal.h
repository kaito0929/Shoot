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
#include "../Global.h"

class Normal : public BaseScene
{
private:

	Player player;
	Sound sound;

	//フェードアウト用のテクスチャ
	Texture FadeTex;
	Sprite FadeSprite;

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