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

#define SHOTSPEED 2.0f
#define SHOTNUM 5

class Shot
{
private:

	//弾のモデル
	Mesh Bullet;

	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;


	//弾の座標
	D3DXVECTOR3 BulletPos[SHOTNUM];

	//弾の発射する方向と進む方向
	D3DXVECTOR3 BulletAngle[SHOTNUM];

	//各方向のベクトル
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

public:

	//コンストラクタ
	Shot();

	//デストラクタ
	~Shot();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	void BulletShot(bool shotFlag[SHOTNUM]);

	void ShotPosSet(D3DXVECTOR3 pPos,D3DXVECTOR3 pAngle,bool shotFlag[SHOTNUM]);


	//弾の当たり判定
	OrientedBoundingBox bulletObb[SHOTNUM];


};