#include "Player.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()�֐��p
#include <time.h>	//time()�֐��p
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
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
	D3DXMatrixRotationYawPitchRoll(&mat_rotate,PlayerAngle.x, PlayerAngle.y, PlayerAngle.z);//��]

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

	//����	
	forward2.x = cos(-BulletAngle.x + (D3DX_PI / 2));
	forward2.y = cos(BulletAngle.y + (D3DX_PI / 2));
	forward2.z = sin(-BulletAngle.z + (D3DX_PI / 2));

	//�E��
	right2.x = cos(-BulletAngle.x);
	right2.y = 0;
	right2.z = sin(-BulletAngle.z);

	bulletObb.UpdateInfo(BulletPos, forward2, right2, up2);

	if (OrientedBoundingBox::Collision(bulletObb, *(stage.GetObb())))
	{
		ShotFlag = false;
	}

}

//�v���C���[�̓����̐���
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	////�v���C���[�̌����Ă�������Ɍ������Ď����őO�i
	PlayerPos.x += sin(PlayerAngle.x)*PLAYER_SPEED;
	PlayerPos.y += sin(-PlayerAngle.y)*PLAYER_SPEED;
	PlayerPos.z += cos(PlayerAngle.z)*PLAYER_SPEED;

	//�����ւ̕����]��
	if (pDi->KeyCount(DIK_UP))
	{
		PlayerAngle.y += PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y >= PLAYERANGLE_DOWNMAX)
		{
			PlayerAngle.y = PLAYERANGLE_DOWNMAX;
		}
	}
	//����ւ̕����ϊ�
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerAngle.y -= PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y <= PLAYERANGLE_UPMAX)
		{
			PlayerAngle.y = PLAYERANGLE_UPMAX;
		}
	}

	//���ւ̕����]��
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

	//�E�ւ̕����ϊ�
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
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	D3DXMatrixTranslation(&mat_transform, BulletPos.x, BulletPos.y, BulletPos.z);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, BulletAngle.x, BulletAngle.y, BulletAngle.z);//��]

	Bullet.Draw(mat_transform, mat_scale, mat_rotate);
}

//�J�����̓����̐���
void Player::CameraControl()
{
	//���@�ɍ��킹���J�����̈ړ�
	CameraPos.x = PlayerPos.x + sin(PlayerAngle.x)*CAMERA_RADIUS_MINUS;
	CameraPos.y = PlayerPos.y + sin(-PlayerAngle.y)*CAMERA_RADIUS_MINUS;
	CameraPos.z = PlayerPos.z + cos(PlayerAngle.z)*CAMERA_RADIUS_MINUS;

	//���@�̕����ɍ��킹���J�����̕����ϊ�
	CameraRel.x = sin(PlayerAngle.x)*CAMERA_RADIUS_PLUS;
	CameraRel.y = sin(-PlayerAngle.y)*CAMERA_RADIUS_PLUS;
	CameraRel.z = cos(PlayerAngle.z)*CAMERA_RADIUS_PLUS;

	camera.SetEyePoint(CameraPos);
	camera.SetRelLookAtPoint(CameraRel);	

	camera.UpdateViewMatrix();
}

//�v���C���[�̓����蔻��̐���
void Player::PlayerObbUpdate()
{
	//����	
	forward.x = cos(-PlayerAngle.x + (D3DX_PI / 2));
	forward.y = cos(PlayerAngle.y + (D3DX_PI / 2));
	forward.z = sin(-PlayerAngle.z + (D3DX_PI / 2));

	//�E��
	right.x = cos(-PlayerAngle.x);
	right.y = 0;
	right.z = sin(-PlayerAngle.z);

	obb.UpdateInfo(PlayerPos, forward, right, up);
}