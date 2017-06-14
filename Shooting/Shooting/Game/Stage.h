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


class Stage
{
private:

	//背景
	Mesh BackGround;
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;


	//各方向のベクトル
	D3DXVECTOR3 forward[6];
	D3DXVECTOR3 right[6];
	D3DXVECTOR3 up[6];

	D3DXVECTOR3 pos[6];

public:

	Stage();
	~Stage();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();


	OrientedBoundingBox obb[6];


};