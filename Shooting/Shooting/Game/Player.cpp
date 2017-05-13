#include "Player.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()関数用
#include <time.h>	//time()関数用

Player::Player()
{

}

Player::~Player()
{

}

void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));
	Bullet.Load(_T("Model/Bullet.x"));

	PlayerPos.x = 0.0f;
	PlayerPos.y = 0.0f;
	PlayerPos.z = 0.0f;
	CameraPos.x = 0.0f;
	CameraPos.y = 60.0f;
	CameraPos.z = -60.0f;

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(0.0f, -10.0f, 1.0f);
}

void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, 0.0f, PlayerPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);		//拡大
	D3DXMatrixRotationY(&mat_rotate, 0);					//回転　（y軸中心）

	D3DXMatrixTranslation(&mat_transform2, 0.0f, 0.0f, 0.0f);	//座標
	D3DXMatrixScaling(&mat_scale2, 0.1f, 0.1f, 0.1f);		//拡大
	D3DXMatrixRotationY(&mat_rotate2, 0);					//回転　（y軸中心）

	PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	Bullet.Draw(mat_transform2, mat_scale2, mat_rotate2);
}

void Player::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	CameraPos.x = PlayerPos.x;
	CameraPos.z = PlayerPos.z - 60.0f;


	if (pDi->KeyCount(DIK_UP))
	{
		PlayerPos.z += 1.0;
	}
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerPos.z -= 1.0;
	}
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerPos.x += 1.0;
	}
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerPos.x -= 1.0;
	}

	camera.SetEyePoint(CameraPos);

	camera.Move(0.0f, 0.0f);
	camera.Rotate(0.0f, 0.0f);
	camera.UpdateViewMatrix();
}

void Player::BulletShot()
{
	DirectInput* pDi = DirectInput::GetInstance();
}