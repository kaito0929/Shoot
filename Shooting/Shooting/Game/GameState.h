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

class GameState
{
private:

	Mesh Player;

	Camera camera;

	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

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