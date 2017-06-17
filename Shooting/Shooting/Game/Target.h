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

#define TARGETNUM 5

class Target
{
private:

	Mesh TargetModel;

	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//ターゲットの座標
	D3DXVECTOR3 TargetPos[TARGETNUM];

	//ターゲットの当たり判定
	OrientedBoundingBox TargetObb[TARGETNUM];

	//各方向のベクトル
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//ターゲットの存在しているかのフラグ
	bool TargetExistenceFlag[TARGETNUM];

public:
	
	//コンストラクタ
	Target();

	//デストラクタ
	~Target();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();


	bool TargetColl(OrientedBoundingBox obb);


};