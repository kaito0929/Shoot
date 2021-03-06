#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Shot.h"

Shot::Shot()
{

}

Shot::~Shot()
{

}

void Shot::Initialize()
{
	Bullet.Load(_T("Model/Bullet.x"));


	for (int i = 0; i < SHOTNUM; i++)
	{
		BulletPos[i].x = 0.0f;
		BulletPos[i].y = 0.0f;
		BulletPos[i].z = 0.0f;

		BulletAngle[i].x = 0.0f;
		BulletAngle[i].y = 0.0f;
		BulletAngle[i].z = 0.0f;
	}

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	for (int i = 0; i < SHOTNUM; i++)
	{
		bulletObb[i].SetLength(10, 10, 10);
	}

}

void Shot::Draw()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		bulletObb[i].DrawLine();
	}
}

void Shot::Update()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
	}
}

void Shot::BulletShot(bool shotFlag[SHOTNUM])
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (shotFlag[i] == true)
		{
			D3DXMatrixTranslation(&mat_transform, BulletPos[i].x, BulletPos[i].y, BulletPos[i].z);	//座標
			D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, BulletAngle[i].x, BulletAngle[i].y, BulletAngle[i].z);//回転

			Bullet.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}


//弾の発射位置を設定する関数
void Shot::ShotPosSet(D3DXVECTOR3 pPos, D3DXVECTOR3 dir, bool shotFlag[SHOTNUM])
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (shotFlag[i] == true)
		{
			BulletPos[i] += BulletAngle[i]*SHOTSPEED;

			//正面	
			forward.x = cos(-BulletAngle[i].x + (D3DX_PI / 2));
			forward.y = cos(-BulletAngle[i].y + (D3DX_PI / 2));
			forward.z = sin(-BulletAngle[i].z + (D3DX_PI / 2));

			//右側
			right.x = cos(-BulletAngle[i].x);
			right.y = 0;
			right.z = sin(-BulletAngle[i].z);
		}
		else
		{
			BulletAngle[i] = dir;

			BulletPos[i] = pPos + dir*30.0f;
		}
	}
}

