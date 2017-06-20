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

}

void Shot::Update()
{

}

void Shot::BulletShot(bool shotFlag[SHOTNUM])
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (shotFlag[i] == true)
		{
			D3DXMatrixTranslation(&mat_transform, BulletPos[i].x, BulletPos[i].y, BulletPos[i].z);	//À•W
			D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//Šg‘å
			D3DXMatrixRotationYawPitchRoll(&mat_rotate, BulletAngle[i].x, BulletAngle[i].y, BulletAngle[i].z);//‰ñ“]

			Bullet.Draw(mat_transform, mat_scale, mat_rotate);
		}
	}
}


//’e‚Ì”­ŽËˆÊ’u‚ðÝ’è‚·‚éŠÖ”
void Shot::ShotPosSet(D3DXVECTOR3 pPos, float yaw, float pitch, bool shotFlag[SHOTNUM])
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (shotFlag[i] == true)
		{
			BulletPos[i].x += sin(BulletAngle[i].x)*SHOTSPEED;
			BulletPos[i].y += sin(BulletAngle[i].y)*SHOTSPEED;
			BulletPos[i].z += cos(BulletAngle[i].z)*SHOTSPEED;

			//³–Ê	
			forward.x = cos(-BulletAngle[i].x + (D3DX_PI / 2));
			forward.y = cos(-BulletAngle[i].y + (D3DX_PI / 2));
			forward.z = sin(-BulletAngle[i].z + (D3DX_PI / 2));

			//‰E‘¤
			right.x = cos(-BulletAngle[i].x);
			right.y = 0;
			right.z = sin(-BulletAngle[i].z);

			bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);
		}
		else
		{
			BulletAngle[i].x = yaw;
			BulletAngle[i].y = pitch;
			BulletAngle[i].z = yaw;


			BulletPos[i].x = pPos.x + sin(BulletAngle[i].x)*30.0f;
			BulletPos[i].y = pPos.y + sin(BulletAngle[i].y)*50.0f;
			BulletPos[i].z = pPos.z + cos(BulletAngle[i].z)*30.0f;

			bulletObb[i].UpdateInfo(BulletPos[i], forward, right, up);

		}
	}
}

