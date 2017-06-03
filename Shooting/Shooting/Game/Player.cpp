#include "Player.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()ä÷êîóp
#include <time.h>	//time()ä÷êîóp
#include <math.h>


Player::Player()
{
	rotate.x = rotate.y = rotate.z;
		
	forward.x = cos(D3DX_PI / 2);
	forward.z = sin(D3DX_PI / 2);
	forward.y = 0;

	right.x = cos(0);
	right.z = sin(0);
	right.y = 0;

	up.x = 0;
	up.z = 0;
	up.y = 1;


	obb.SetLength(20, 10, 10);
	obb.UpdateInfo(PlayerPos, forward, right, up);
}

Player::~Player()
{

}

void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	PlayerPos.x = 0.0f;
	PlayerPos.y = 30.0f;
	PlayerPos.z = 0.0f;

	PlayerAngle.x = 0.0f;
	PlayerAngle.y = 0.0f;
	PlayerAngle.z = 0.0f;

	PlayerSpeed.x = 0.5f;
	PlayerSpeed.y = 0.5f;
	PlayerSpeed.z = 0.5f;

	CameraPos.x = 0.0f;
	CameraPos.y = 40.0f;
	CameraPos.z = -60.0f;

	CameraRel.x = 0.0f;
	CameraRel.y = -2.0f;
	CameraRel.z = 10.0f;

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(CameraRel);

}

void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//ç¿ïW
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//ägëÂ
	D3DXMatrixRotationYawPitchRoll(&mat_rotate,PlayerAngle.x, PlayerAngle.y, PlayerAngle.z);//âÒì]

	PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);

	obb.DrawLine();
}

void Player::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();


	obb.UpdateInfo(PlayerPos, forward, right, up);

	PlayerPos.x += sin(PlayerAngle.x)*PlayerSpeed.x;
	PlayerPos.y += sin(-PlayerAngle.y)*PlayerSpeed.y;
	PlayerPos.z += cos(PlayerAngle.z)*PlayerSpeed.z;


	if (pDi->KeyCount(DIK_UP))
	{
		PlayerAngle.y += 0.1f;

		if (PlayerAngle.y >= 1.0f)
		{
			PlayerAngle.y = 1.0f;
		}
	}
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerAngle.y -= 0.1f;
		if (PlayerAngle.y <= -1.0f)
		{
			PlayerAngle.y = -1.0f;
		}
	}

	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerAngle.z -= 0.1f;
		PlayerAngle.x -= 0.1f;
		if (PlayerAngle.z <= -3.0f&&PlayerAngle.x <= -3.0f)
		{
			PlayerAngle.z = -3.0f;
			PlayerAngle.x = -3.0f;
		}
	}
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerAngle.z += 0.1f;
		PlayerAngle.x += 0.1f;
		if (PlayerAngle.z >= 3.0f&&PlayerAngle.x >= 3.0f)
		{
			PlayerAngle.z = 3.0f;
			PlayerAngle.x = 3.0f;
		}
	}

	CameraControl();

}

void Player::CameraControl()
{
	CameraPos.x = PlayerPos.x + sin(PlayerAngle.x)*-60.0f;
	CameraPos.y = PlayerPos.y + sin(-PlayerAngle.y)*-60.0f;
	CameraPos.z = PlayerPos.z + cos(PlayerAngle.z)*-60.0f;
	

	CameraRel.x = sin(PlayerAngle.x)*60.0f;
	CameraRel.y = sin(-PlayerAngle.y)*60.0f;
	CameraRel.z = cos(PlayerAngle.z)*60.0f;

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(CameraRel);	

	camera.UpdateViewMatrix();
}