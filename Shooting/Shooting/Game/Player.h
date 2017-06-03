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

class Player
{
private:

	//プレイヤーのモデル
	Mesh PlayerModel;
	
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//プレイヤーの位置
	D3DXVECTOR3 PlayerPos;
	//プレイヤーの向き
	D3DXVECTOR3 PlayerAngle;
	//プレイヤーの速さ
	D3DXVECTOR3 PlayerSpeed;

	//各方向のベクトル
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	D3DXVECTOR3 rotate;

	//カメラ操作
	Camera camera;
	//カメラの位置
	D3DXVECTOR3 CameraPos;
	//カメラの位置
	D3DXVECTOR3 CameraRel;


	//当たり判定
	OrientedBoundingBox obb;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();


	void CameraControl();

	OrientedBoundingBox* GetObb() { return &obb; }


};