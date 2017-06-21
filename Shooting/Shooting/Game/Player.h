#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"
#include "../BoundingBox.h"

#include "Stage.h"
#include "Target.h"
#include "Shot.h"

#include "SoundEffect.h"

#define PLAYER_SPEED 0.5f			//���@�̈ړ����x
#define PLAYERANGLE_CHANGENUM 0.1f	//���@�̌�����ς��鎞�̐��l

#define PLAYERANGLE_UPMAX -1.0f		//���@�̌����������̍ő�l
#define PLAYERANGLE_DOWNMAX 1.0f	//���@�̌����鉺�����̍ő�l
#define PLAYERANGLE_LEFTMAX -3.0f	//���@�̌����鍶�����̍ő�l
#define PLAYERANGLE_RIGHTMAX 3.0f	//���@�̌�����E�����̍ő�l

#define CAMERA_RADIUS_PLUS 60.0f
#define CAMERA_RADIUS_MINUS -60.0f


class Player
{
private:

	//�v���C���[�̃��f��
	Mesh PlayerModel;
	
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;
	//�v���C���[�̌���
	D3DXVECTOR3 Direction;

	float PlayerYaw;
	float PlayerPitch;


	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;


	//�J��������
	Camera camera;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPos;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraRel;

	//�v���C���[�̓����蔻��
	OrientedBoundingBox PlayerObb;

	//�v���C���[�̐����t���O
	bool PlayerAliveFlag;

	//�e���˂̃t���O
	bool ShotFlag[SHOTNUM];
	int ShotNum;

	//�^�[�Q�b�g��S�Ĕj�󂵂����̃t���O
	bool TargetOllBreakFlag;


	Stage stage;
	Shot shot;
	EasyTarget easyTarget;
	NormalTarget normalTarget;
	HardTarget hardTarget;

	SoundEffect se;

public:

	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	//�v���C���[�̈ړ��̐���
	void PlayerMoveControl();

	//�J�����̓����̐���
	void CameraControl();

	//�v���C���[�̓����蔻��̓���
	void PlayerObbUpdate();

	bool GetAliveFlag() { return PlayerAliveFlag; };

	bool GetOllBreakFlag() { return TargetOllBreakFlag; };



	//--���C�[�W�[���[�h�֌W��---------------------------------
	void EasyInitialize();
	void EasyDraw();
	void EasyUpdate();
	//--���m�[�}�����[�h�֌W��---------------------------------
	void NormalInitialize();
	void NormalDraw();
	void NormalUpdate();
	//--���n�[�h���[�h�֌W��---------------------------------
	void HardInitialize();
	void HardDraw();
	void HardUpdate();


};