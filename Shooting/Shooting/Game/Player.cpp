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

}

Player::~Player()
{

}

//�������֐�
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));


	PlayerPos.x = 0.0f;
	PlayerPos.y = 30.0f;
	PlayerPos.z = 0.0f;

	PlayerYaw = PlayerPitch = 0.0f;

	CameraPos.x = 0.0f;
	CameraPos.y = 0.0f;
	CameraPos.z = 0.0f;

	CameraRel.x = 0.0f;
	CameraRel.y = 0.0f;
	CameraRel.z = 0.0f;


	Direction.x = sin(PlayerYaw);
	Direction.y = sin(PlayerPitch);
	Direction.z = cos(PlayerYaw);

	//���@�ɍ��킹���J�����̈ړ�
	CameraPos.x = PlayerPos.x + (Direction.x*-0.6 * 100);
	CameraPos.y = (PlayerPos.y+20.0f) + (Direction.y*-0.6 * 100);
	CameraPos.z = PlayerPos.z + (Direction.z*-0.6 * 100);

	//���@�̕����ɍ��킹���J�����̕����ϊ�
	CameraRel = Direction;

	//���W�̍X�V
	camera.SetEyePoint(CameraPos);
	//�����̍X�V
	camera.SetRelLookAtPoint(CameraRel);

	camera.UpdateViewMatrix();

	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	PlayerObb.SetLength(20, 10, 10);

	PlayerAliveFlag = true;

	for (int i = 0;i < SHOTNUM; i++)
	{
		ShotFlag[i] = false;
	}

	stage.Initialize();
	shot.Initialize();
	se.Initialize();
}

//�`��֐�
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//�g��
	D3DXMatrixRotationYawPitchRoll(&mat_rotate, PlayerYaw, -PlayerPitch,0.0f);//��]	

	if (PlayerAliveFlag == true)
	{
		//�v���C���[�i���@�j�̕`��
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	for (int i = 0; i < SHOTNUM; i++)
	{
		//ShotFlag��true�̎��ɒe��`��
		if (ShotFlag[i] == true)
		{
			shot.BulletShot(ShotFlag);
		}
	}

	stage.Draw();
	shot.Draw();
}

void Player::Update()
{
	stage.Update();
	shot.Update();

	//�v���C���[�̐����t���O��true�Ȃ�Ώ������s���悤��
	if (PlayerAliveFlag == true && TargetOllBreakFlag == false)
	{
		PlayerMoveControl();
		CameraControl();
		PlayerObbUpdate();
	}

	shot.ShotPosSet(PlayerPos, Direction, ShotFlag);


	if (ShotNum == SHOTNUM)
	{
		ShotNum = 0;
	}

}

//�v���C���[�̓����̐���
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	//�v���C���[�̌����Ă�������Ɍ������Ď����őO�i

	float flatLength = cos(PlayerPitch);

	Direction.x = sin(PlayerYaw)*flatLength;
	Direction.y = sin(PlayerPitch);
	Direction.z = cos(PlayerYaw)*flatLength;

	PlayerPos += Direction*PLAYER_SPEED;

	//����ւ̕����]��
	if (pDi->KeyCount(DIK_UP))
	{
		PlayerPitch += PLAYERANGLE_CHANGENUM;

		if (PlayerPitch >= PLAYERANGLE_DOWNMAX)
		{
			PlayerPitch = PLAYERANGLE_DOWNMAX;
		}
	}

	//�����ւ̕����ϊ�
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerPitch -= PLAYERANGLE_CHANGENUM;

		if (PlayerPitch <= PLAYERANGLE_UPMAX)
		{
			PlayerPitch = PLAYERANGLE_UPMAX;
		}
	}

	//���ւ̕����]��
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerYaw -= PLAYERANGLE_CHANGENUM;		
	}

	//�E�ւ̕����ϊ�
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerYaw += PLAYERANGLE_CHANGENUM;
	}

	//�X�y�[�X�L�[�������Ēe�𔭎�
	if (pDi->KeyJustPressed(DIK_SPACE))
	{
		if (ShotFlag[ShotNum] == false)
		{
			ShotFlag[ShotNum] = true;
			ShotNum++;
			se.ShotSEPlay();
		}
	}

}


//�J�����̓����̐���
void Player::CameraControl()
{
	//���@�ɍ��킹���J�����̈ړ�
	CameraPos.x = PlayerPos.x + (Direction.x*-0.6 * 100);
	CameraPos.y = (PlayerPos.y + 20.0f) + (Direction.y*-0.6 * 100);
	CameraPos.z = PlayerPos.z + (Direction.z*-0.6 * 100);

	//���@�̕����ɍ��킹���J�����̕����ϊ�
	CameraRel = Direction;

	//���W�̍X�V
	camera.SetEyePoint(CameraPos);
	//�����̍X�V
	camera.SetRelLookAtPoint(CameraRel);	

	camera.UpdateViewMatrix();
}

//�v���C���[�̓����蔻��̐���
void Player::PlayerObbUpdate()
{
	//����	
	forward.x = cos(-PlayerYaw + (D3DX_PI / 2));
	forward.y = cos(-PlayerPitch + (D3DX_PI / 2));
	forward.z = sin(-PlayerYaw + (D3DX_PI / 2));

	////�E��
	right.x = cos(-PlayerYaw);
	right.y = 0;
	right.z = sin(-PlayerYaw);

	PlayerObb.UpdateInfo(PlayerPos, forward, right, up);
}

//--���C�[�W�[���[�h�֌W��------------------------------------------------------------
void Player::EasyInitialize()
{
	easyTarget.EasyTargetInitialize();
}

void Player::EasyDraw()
{
	easyTarget.EasyTargetDraw();
}

void Player::EasyUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//�e���X�e�[�W���^�[�Q�b�g�ɓ����������̏������s��
			if (stage.StageCollision(shot.bulletObb[i]) == true || easyTarget.EasyTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i] = false;
				se.ShotHitSEPlay();
			}
		}
	}

	//�X�e�[�W�ƃv���C���[�̓����蔻�����������
	if (stage.StageCollision(PlayerObb) == true || easyTarget.EasyTargetColl(PlayerObb) == true)
	{
		if (PlayerAliveFlag == true)
		{
			se.PlayerHitSEPlay();
		}
		PlayerAliveFlag = false;
	}


	for (int i = 0; i < EASYTARGETNUM; i++)
	{
		if (easyTarget.EasyTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}

//--���m�[�}�����[�h�֌W��------------------------------------------------------------
void Player::NormalInitialize()
{
	normalTarget.NormalTargetInitialize();
}

void Player::NormalDraw()
{
	normalTarget.NormalTargetDraw();
}

void Player::NormalUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//�e���X�e�[�W���^�[�Q�b�g�ɓ����������̏������s��
			if (stage.StageCollision(shot.bulletObb[i]) == true || normalTarget.NormalTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i] = false;
				se.ShotHitSEPlay();
			}
		}
	}

	//�X�e�[�W�ƃv���C���[�̓����蔻�����������
	if (stage.StageCollision(PlayerObb) == true || normalTarget.NormalTargetColl(PlayerObb) == true)
	{
		if (PlayerAliveFlag == true)
		{
			se.PlayerHitSEPlay();
		}
		PlayerAliveFlag = false;
		
	}


	for (int i = 0; i < NORMALTARGETNUM; i++)
	{
		if (normalTarget.NormalTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}


//--���n�[�h���[�h�֌W��------------------------------------------------------------
void Player::HardInitialize()
{
	hardTarget.HardTargetInitialize();
}

void Player::HardDraw()
{
	hardTarget.HardTargetDraw();
}

void Player::HardUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//�e���X�e�[�W���^�[�Q�b�g�ɓ����������̏������s��
			if (stage.StageCollision(shot.bulletObb[i]) == true || hardTarget.HardTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i]= false;
				se.ShotHitSEPlay();
			}
		}
	}

	//�X�e�[�W�ƃv���C���[�̓����蔻�����������
	if (stage.StageCollision(PlayerObb) == true || hardTarget.HardTargetColl(PlayerObb) == true)
	{
		if (PlayerAliveFlag == true)
		{
			se.PlayerHitSEPlay();
		}
		PlayerAliveFlag = false;
		
	}


	for (int i = 0; i < HARDTARGETNUM; i++)
	{
		if (hardTarget.HardTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}