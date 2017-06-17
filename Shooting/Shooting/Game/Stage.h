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

#define STAGE_COLLNUM 6

class Stage
{
private:

	//背景
	Mesh BackGround;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;


	//ステージのモデルの当たり判定
	OrientedBoundingBox StageObb[STAGE_COLLNUM];

	//各方向のベクトル
	D3DXVECTOR3 forward[STAGE_COLLNUM];
	D3DXVECTOR3 right[STAGE_COLLNUM];
	D3DXVECTOR3 up[STAGE_COLLNUM];

	//当たり判定の場所
	D3DXVECTOR3 pos[STAGE_COLLNUM];

public:

	Stage();
	~Stage();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();


	//ステージとの当たり判定を行う関数
	bool StageCollision(OrientedBoundingBox obb);


};