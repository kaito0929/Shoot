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
#include "Stage.h"

class GameState : public BaseScene
{
private:

	Player player;

	Stage stage;

public:
	//コンストラクタ
	GameState::GameState(ISceneChanger* changer);
	//デストラクタ
	~GameState();			

	//初期化
	void Initialize() override;
	//実際の動き
	void Update() override;
	//描画
	void Draw() override;

	
};