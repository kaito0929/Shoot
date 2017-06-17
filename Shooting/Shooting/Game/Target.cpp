#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Target.h"

//コンストラクタ
Target::Target()
{

}

//デストラクタ
Target::~Target()
{

}

//初期化関数
void Target::Initialize()
{
	TargetModel.Load("Model/target.x");

	TargetPos[0].x = 0.0f;
	TargetPos[0].y = 50.0f;
	TargetPos[0].z = 0.0f;

	TargetPos[1].x = 0.0f;
	TargetPos[1].y = 140.0f;
	TargetPos[1].z = 30.0f;

	TargetPos[2].x = 50.0f;
	TargetPos[2].y = 75.0f;
	TargetPos[2].z = 60.0f;

	TargetPos[3].x = 40.0f;
	TargetPos[3].y = 30.0f;
	TargetPos[3].z = 70.0f;

	TargetPos[4].x = 30.0f;
	TargetPos[4].y = 90.0f;
	TargetPos[4].z = 0.0f;


	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 1;


	for (int i = 0; i < TARGETNUM; i++)
	{
		TargetObb[i].SetLength(10, 10, 10);
		TargetExistenceFlag[i] = true;
		TargetObb[i].UpdateInfo(TargetPos[i], forward, right, up);
	}

}

//描画関数
void Target::Draw()
{
	for (int i = 0; i < TARGETNUM; i++)
	{
		D3DXMatrixTranslation(&mat_transform, TargetPos[i].x, TargetPos[i].y, TargetPos[i].z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.05f, 0.05f, 0.05f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転
	
	
		if (TargetExistenceFlag[i] == true)
		{
			TargetModel.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}


	
}

void Target::Update()
{

}


//ターゲットとの当たり判定を行う関数
//obbに判定を取りたいモデルの当たり判定を入れる
//当たった際にはターゲットの生存フラグを消すように
bool Target::TargetColl(OrientedBoundingBox obb)
{
	for (int i = 0; i < TARGETNUM; i++)
	{
		if (TargetExistenceFlag[i] == true)
		{
			if (OrientedBoundingBox::Collision(TargetObb[i], obb))
			{
				TargetExistenceFlag[i] = false;
				return true;
			}
		}
	}
}