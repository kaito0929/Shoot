#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Target.h"

//=====================================================
//■Targetクラス■
//=====================================================
//コンストラクタ
Target::Target()
{

}

//デストラクタ
Target::~Target()
{

}

//=====================================================
//■EasyTargetクラス■
//=====================================================
//コンストラクタ
EasyTarget::EasyTarget()
{

}
//デストラクタ
EasyTarget::~EasyTarget()
{

}

//イージーモードでの初期化関数
void EasyTarget::EasyTargetInitialize()
{
	TargetModel.Load("Model/target.x");

	EasyTargetPos[0].x = -30.0f;
	EasyTargetPos[0].y = 50.0f;
	EasyTargetPos[0].z = 0.0f;

	EasyTargetPos[1].x = 0.0f;
	EasyTargetPos[1].y = 140.0f;
	EasyTargetPos[1].z = -30.0f;

	EasyTargetPos[2].x = 50.0f;
	EasyTargetPos[2].y = 75.0f;
	EasyTargetPos[2].z = 60.0f;

	EasyTargetPos[3].x = 40.0f;
	EasyTargetPos[3].y = 30.0f;
	EasyTargetPos[3].z = -70.0f;

	EasyTargetPos[4].x = 30.0f;
	EasyTargetPos[4].y = 90.0f;
	EasyTargetPos[4].z = 0.0f;


	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 1;


	for (int i = 0; i < EASYTARGETNUM; i++)
	{
		EasyTargetObb[i].SetLength(10, 10, 10);
		EasyTargetExistenceFlag[i] = true;
		EasyTargetObb[i].UpdateInfo(EasyTargetPos[i], forward, right, up);
	}
}

//イージーモードでの描画関数
void EasyTarget::EasyTargetDraw()
{
	for (int i = 0; i < EASYTARGETNUM; i++)
	{
		D3DXMatrixTranslation(&mat_transform, EasyTargetPos[i].x, EasyTargetPos[i].y, EasyTargetPos[i].z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.05f, 0.05f, 0.05f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転

		if (EasyTargetExistenceFlag[i] == true)
		{
			TargetModel.Draw(mat_transform, mat_scale, mat_rotate);
		}

		EasyTargetObb[i].DrawLine();
	}

	
}

//ターゲットとの当たり判定を行う関数
//obbに判定を取りたいモデルの当たり判定を入れる
//当たった際にはターゲットの生存フラグを消すように
bool EasyTarget::EasyTargetColl(OrientedBoundingBox obb)
{
	for (int i = 0; i < EASYTARGETNUM; i++)
	{
		if (EasyTargetExistenceFlag[i] == true)
		{
			if (OrientedBoundingBox::Collision(EasyTargetObb[i], obb))
			{
				EasyTargetExistenceFlag[i] = false;
				return true;
			}
		}
	}
}

//=====================================================
//■NormalTargetクラス■
//=====================================================
//コンストラクタ
NormalTarget::NormalTarget()
{

}
//デストラクタ
NormalTarget::~NormalTarget()
{

}

//ノーマルモードでの初期化関数
void NormalTarget::NormalTargetInitialize()
{
	TargetModel.Load("Model/target.x");

	NormalTargetPos[0].x = -70.0f;
	NormalTargetPos[0].y = 50.0f;
	NormalTargetPos[0].z = 0.0f;

	NormalTargetPos[1].x = 40.0f;
	NormalTargetPos[1].y = 150.0f;
	NormalTargetPos[1].z = 20.0f;

	NormalTargetPos[2].x = 70.0f;
	NormalTargetPos[2].y = 75.0f;
	NormalTargetPos[2].z = -60.0f;

	NormalTargetPos[3].x = -40.0f;
	NormalTargetPos[3].y = 80.0f;
	NormalTargetPos[3].z = 80.0f;

	NormalTargetPos[4].x = 60.0f;
	NormalTargetPos[4].y = 120.0f;
	NormalTargetPos[4].z = 10.0f;

	NormalTargetPos[5].x = 0.0f;
	NormalTargetPos[5].y = 65.0f;
	NormalTargetPos[5].z = -50.0f;

	NormalTargetPos[6].x = 30.0f;
	NormalTargetPos[6].y = 140.0f;
	NormalTargetPos[6].z = -30.0f;

	NormalTargetPos[7].x = -20.0f;
	NormalTargetPos[7].y = 110.0f;
	NormalTargetPos[7].z = -60.0f;

	NormalTargetPos[8].x = -20.0f;
	NormalTargetPos[8].y = 40.0f;
	NormalTargetPos[8].z = 20.0f;

	NormalTargetPos[9].x = 30.0f;
	NormalTargetPos[9].y = 90.0f;
	NormalTargetPos[9].z = 0.0f;


	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 1;


	for (int i = 0; i < NORMALTARGETNUM; i++)
	{
		NormalTargetObb[i].SetLength(10, 10, 10);
		NormalTargetExistenceFlag[i] = true;
		NormalTargetObb[i].UpdateInfo(NormalTargetPos[i], forward, right, up);
	}
}

//ノーマルモードでの描画関数
void NormalTarget::NormalTargetDraw()
{
	for (int i = 0; i < NORMALTARGETNUM; i++)
	{
		D3DXMatrixTranslation(&mat_transform, NormalTargetPos[i].x, NormalTargetPos[i].y, NormalTargetPos[i].z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.05f, 0.05f, 0.05f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転

		if (NormalTargetExistenceFlag[i] == true)
		{
			TargetModel.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//ターゲットとの当たり判定を行う関数
//obbに判定を取りたいモデルの当たり判定を入れる
//当たった際にはターゲットの生存フラグを消すように
bool NormalTarget::NormalTargetColl(OrientedBoundingBox obb)
{
	for (int i = 0; i < NORMALTARGETNUM; i++)
	{
		if (NormalTargetExistenceFlag[i] == true)
		{
			if (OrientedBoundingBox::Collision(NormalTargetObb[i], obb))
			{
				NormalTargetExistenceFlag[i] = false;
				return true;
			}
		}
	}
}

//=====================================================
//■HardTargetクラス■
//=====================================================
//コンストラクタ
HardTarget::HardTarget()
{

}
//デストラクタ
HardTarget::~HardTarget()
{

}

//ハードモードでの初期化関数
void HardTarget::HardTargetInitialize()
{
	TargetModel.Load("Model/target.x");

	HardTargetPos[0].x = 50.0f;
	HardTargetPos[0].y = 30.0f;
	HardTargetPos[0].z = -30.0f;

	HardTargetPos[1].x = 0.0f;
	HardTargetPos[1].y = 140.0f;
	HardTargetPos[1].z = -30.0f;

	HardTargetPos[2].x = -20.0f;
	HardTargetPos[2].y = 85.0f;
	HardTargetPos[2].z = 60.0f;

	HardTargetPos[3].x = -60.0f;
	HardTargetPos[3].y = 30.0f;
	HardTargetPos[3].z = -70.0f;

	HardTargetPos[4].x = -30.0f;
	HardTargetPos[4].y = 115.0f;
	HardTargetPos[4].z = 0.0f;

	HardTargetPos[5].x = 30.0f;
	HardTargetPos[5].y = 50.0f;
	HardTargetPos[5].z = 50.0f;

	HardTargetPos[6].x = -40.0f;
	HardTargetPos[6].y = 80.0f;
	HardTargetPos[6].z = 30.0f;

	HardTargetPos[7].x = 50.0f;
	HardTargetPos[7].y = 95.0f;
	HardTargetPos[7].z = -60.0f;

	HardTargetPos[8].x = -20.0f;
	HardTargetPos[8].y = 60.0f;
	HardTargetPos[8].z = 70.0f;

	HardTargetPos[9].x = 0.0f;
	HardTargetPos[9].y = 120.0f;
	HardTargetPos[9].z = 0.0f;

	HardTargetPos[10].x = -50.0f;
	HardTargetPos[10].y = 70.0f;
	HardTargetPos[10].z = -50.0f;

	HardTargetPos[11].x = 60.0f;
	HardTargetPos[11].y = 40.0f;
	HardTargetPos[11].z = -60.0f;

	HardTargetPos[12].x = -80.0f;
	HardTargetPos[12].y = 100.0f;
	HardTargetPos[12].z = 60.0f;

	HardTargetPos[13].x = 80.0f;
	HardTargetPos[13].y = 40.0f;
	HardTargetPos[13].z = -60.0f;

	HardTargetPos[14].x = 0.0f;
	HardTargetPos[14].y = 90.0f;
	HardTargetPos[14].z = 30.0f;


	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.y = 0;
	up.z = 1;


	for (int i = 0; i < HARDTARGETNUM; i++)
	{
		HardTargetObb[i].SetLength(10, 10, 10);
		HardTargetExistenceFlag[i] = true;
		HardTargetObb[i].UpdateInfo(HardTargetPos[i], forward, right, up);
	}
}

//ハードモードでの描画関数
void HardTarget::HardTargetDraw()
{
	for (int i = 0; i < HARDTARGETNUM; i++)
	{
		D3DXMatrixTranslation(&mat_transform, HardTargetPos[i].x, HardTargetPos[i].y, HardTargetPos[i].z);	//座標
		D3DXMatrixScaling(&mat_scale, 0.05f, 0.05f, 0.05f);								//拡大
		D3DXMatrixRotationYawPitchRoll(&mat_rotate, 0.0f, 0.0f, 0.0f);//回転

		if (HardTargetExistenceFlag[i] == true)
		{
			TargetModel.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}

//ターゲットとの当たり判定を行う関数
//obbに判定を取りたいモデルの当たり判定を入れる
//当たった際にはターゲットの生存フラグを消すように
bool HardTarget::HardTargetColl(OrientedBoundingBox obb)
{
	for (int i = 0; i < HARDTARGETNUM; i++)
	{
		if (HardTargetExistenceFlag[i] == true)
		{
			if (OrientedBoundingBox::Collision(HardTargetObb[i], obb))
			{
				HardTargetExistenceFlag[i] = false;
				return true;
			}
		}
	}
}