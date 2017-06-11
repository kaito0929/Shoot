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
#include <math.h>


Player::Player()
{		

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = 0;
	up.y = 1;
	up.z = 0;


	obb.SetLength(20, 10, 10);
	obb.UpdateInfo(PlayerPos, forward, right, up);

	bulletObb.SetLength(10, 10, 10);
}

Player::~Player()
{

}

void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));

	Bullet.Load(_T("Model/Bullet.x"));

	PlayerPos.x = 0.0f;
	PlayerPos.y = 30.0f;
	PlayerPos.z = 0.0f;

	PlayerAngle.x = 0.0f;
	PlayerAngle.y = 0.0f;
	PlayerAngle.z = 0.0f;

	CameraPos.x = 0.0f;
	CameraPos.y = 40.0f;
	CameraPos.z = -60.0f;

	CameraRel.x = 0.0f;
	CameraRel.y = -2.0f;
	CameraRel.z = 10.0f;


	BulletPos.x = 0.0f;
	BulletPos.y = 0.0f;
	BulletPos.z = 0.0f;

	BulletAngle.x = 0.0f;
	BulletAngle.y = 0.0f;
	BulletAngle.z = 0.0f;

	ShotFlag = false;

	right2.x = cos(0);
	right2.y = 0;
	right2.z = sin(0);

	up2.x = 0;
	up2.y = 1;
	up2.z = 0;

	stage.Initialize();
}

void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
	D3DXMatrixRotationYawPitchRoll(&mat_rotate,PlayerAngle.x, PlayerAngle.y, PlayerAngle.z);//回転

	PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);

	if (ShotFlag == true)
	{
		BulletShot();
	}

	obb.DrawLine();

	bulletObb.DrawLine();
	stage.Draw();
}

void Player::Update()
{
	stage.Update();

	PlayerMoveControl();
	CameraControl();
	PlayerObbUpdate();

	if (ShotFlag == true)
	{
		BulletPos.x += sin(BulletAngle.x)*0.5f;
		BulletPos.y += sin(-BulletAngle.y)*0.5f;
		BulletPos.z += cos(BulletAngle.z)*0.5f;
	}
	else
	{
		BulletAngle.x = PlayerAngle.x;
		BulletAngle.y = PlayerAngle.y;
		BulletAngle.z = PlayerAngle.z;


		BulletPos.x = PlayerPos.x + sin(BulletAngle.x)*30.0f;
		BulletPos.y = PlayerPos.y + sin(-BulletAngle.y)*30.0f;
		BulletPos.z = PlayerPos.z + cos(BulletAngle.z)*30.0f;
	}

	//正面	
	forward2.x = cos(-BulletAngle.x + (D3DX_PI / 2));
	forward2.y = cos(BulletAngle.y + (D3DX_PI / 2));
	forward2.z = sin(-BulletAngle.z + (D3DX_PI / 2));

	//右側
	right2.x = cos(-BulletAngle.x);
	right2.y = 0;
	right2.z = sin(-BulletAngle.z);

	bulletObb.UpdateInfo(BulletPos, forward2, right2, up2);

	if (OrientedBoundingBox::Collision(bulletObb, *(stage.GetObb())))
	{
		ShotFlag = false;
	}

}

//プレイヤーの動きの制御
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	////プレイヤーの向いている方向に向かって自動で前進
	PlayerPos.x += sin(PlayerAngle.x)*PLAYER_SPEED;
	PlayerPos.y += sin(-PlayerAngle.y)*PLAYER_SPEED;
	PlayerPos.z += cos(PlayerAngle.z)*PLAYER_SPEED;

	//下方への方向転換
	if (pDi->KeyCount(DIK_UP))
	{
		PlayerAngle.y += PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y >= PLAYERANGLE_DOWNMAX)
		{
			PlayerAngle.y = PLAYERANGLE_DOWNMAX;
		}
	}
	//上方への方向変換
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerAngle.y -= PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y <= PLAYERANGLE_UPMAX)
		{
			PlayerAngle.y = PLAYERANGLE_UPMAX;
		}
	}

	//左への方向転換
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerAngle.z -= PLAYERANGLE_CHANGENUM;
		PlayerAngle.x -= PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.z <= PLAYERANGLE_LEFTMAX&&PlayerAngle.x <= PLAYERANGLE_LEFTMAX)
		{
			PlayerAngle.z = PLAYERANGLE_LEFTMAX;
			PlayerAngle.x = PLAYERANGLE_LEFTMAX;
		}
	}

	//右への方向変換
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerAngle.z += PLAYERANGLE_CHANGENUM;
		PlayerAngle.x += PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.z >= PLAYERANGLE_RIGHTMAX&&PlayerAngle.x >= PLAYERANGLE_RIGHTMAX)
		{
			PlayerAngle.z = PLAYERANGLE_RIGHTMAX;
			PlayerAngle.x = PLAYERANGLE_RIGHTMAX;
		}
	}

	if (pDi->KeyCount(DIK_RETURN))
	{
		ShotFlag = true;
	}

}

void Player::BulletShot()
{
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	D3DXMatrixTranslation(&mat_transform, BulletPos.x, BulletPos.y, BulletPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, BulletAngle.x, BulletAngle.y, BulletAngle.z);//回転

	Bullet.Draw(mat_transform, mat_scale, mat_rotate);
}

//カメラの動きの制御
void Player::CameraControl()
{
	//自機に合わせたカメラの移動
	CameraPos.x = PlayerPos.x + sin(PlayerAngle.x)*CAMERA_RADIUS_MINUS;
	CameraPos.y = PlayerPos.y + sin(-PlayerAngle.y)*CAMERA_RADIUS_MINUS;
	CameraPos.z = PlayerPos.z + cos(PlayerAngle.z)*CAMERA_RADIUS_MINUS;

	//自機の方向に合わせたカメラの方向変換
	CameraRel.x = sin(PlayerAngle.x)*CAMERA_RADIUS_PLUS;
	CameraRel.y = sin(-PlayerAngle.y)*CAMERA_RADIUS_PLUS;
	CameraRel.z = cos(PlayerAngle.z)*CAMERA_RADIUS_PLUS;

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(CameraRel);	

	camera.UpdateViewMatrix();
}

//プレイヤーの当たり判定の制御
void Player::PlayerObbUpdate()
{
	//正面	
	forward.x = cos(-PlayerAngle.x + (D3DX_PI / 2));
	forward.y = cos(PlayerAngle.y + (D3DX_PI / 2));
	forward.z = sin(-PlayerAngle.z + (D3DX_PI / 2));

	//右側
	right.x = cos(-PlayerAngle.x);
	right.y = 0;
	right.z = sin(-PlayerAngle.z);

	obb.UpdateInfo(PlayerPos, forward, right, up);
}