#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"

class Player
{
private:

	//プレイヤーのモデル
	Mesh PlayerModel;
	//弾のモデル
	Mesh Bullet;

	Camera camera;

	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform2, mat_scale2, mat_rotate2;

	//プレイヤーの位置
	D3DXVECTOR3 PlayerPos;
	//カメラの位置
	D3DXVECTOR3 CameraPos;


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

	//プレイヤーの弾の発射
	void BulletShot();

};