#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Player.h"

class GameState
{
private:

	Player player;

public:
	//コンストラクタ
	GameState();
	//デストラクタ
	~GameState();			

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	
};