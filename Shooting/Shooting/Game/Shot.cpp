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


	BulletPos.x = 0.0f;
	BulletPos.y = 0.0f;
	BulletPos.z = 0.0f;

	BulletAngle.x = 0.0f;
	BulletAngle.y = 0.0f;
	BulletAngle.z = 0.0f;

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	bulletObb.SetLength(10, 10, 10);

}

void Shot::Draw()
{
	
}

void Shot::Update()
{

}

void Shot::BulletShot()
{
	D3DXMatrixTranslation(&mat_transform, BulletPos.x, BulletPos.y, BulletPos.z);	//ç¿ïW
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//ägëÂ
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, BulletAngle.x, BulletAngle.y, BulletAngle.z);//âÒì]

	Bullet.Draw(mat_transform, mat_scale, mat_rotate);
}


//íeÇÃî≠éÀà íuÇê›íËÇ∑ÇÈä÷êî
void Shot::ShotPosSet(D3DXVECTOR3 pPos, D3DXVECTOR3 pAngle, bool shotFlag)
{
	if (shotFlag == true)
	{
		BulletPos.x += sin(BulletAngle.x)*SHOTSPEED;
		BulletPos.y += sin(-BulletAngle.y)*SHOTSPEED;
		BulletPos.z += cos(BulletAngle.z)*SHOTSPEED;

		//ê≥ñ 	
		forward.x = cos(-BulletAngle.x + (D3DX_PI / 2));
		forward.y = cos(BulletAngle.y + (D3DX_PI / 2));
		forward.z = sin(-BulletAngle.z + (D3DX_PI / 2));

		//âEë§
		right.x = cos(-BulletAngle.x);
		right.y = 0;
		right.z = sin(-BulletAngle.z);

		bulletObb.UpdateInfo(BulletPos, forward, right, up);
	}
	else
	{
		BulletAngle.x = pAngle.x;
		BulletAngle.y = pAngle.y;
		BulletAngle.z = pAngle.z;


		BulletPos.x = pPos.x + sin(BulletAngle.x)*30.0f;
		BulletPos.y = pPos.y + sin(-BulletAngle.y)*30.0f;
		BulletPos.z = pPos.z + cos(BulletAngle.z)*30.0f;

		bulletObb.UpdateInfo(BulletPos, forward, right, up);

	}
}

