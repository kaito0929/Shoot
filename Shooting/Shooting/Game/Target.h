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

#define EASYTARGETNUM 5
#define NORMALTARGETNUM 10
#define HARDTARGETNUM 15

//================================================================
//�N���X��  �FTarget�N���X
//���N���X�F
//
//���e�F���̃N���X�����N���X�Ƃ��Ĕh�������Ă���
//================================================================

class Target
{
private:
	
public:
	
	//�R���X�g���N�^
	Target();

	//�f�X�g���N�^
	~Target();


	Mesh TargetModel;

	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;


};

//================================================================
//�N���X��  �FEasyTarget�N���X
//���N���X�FTarget�N���X
//
//���e�FTarget����h���������N���X�B�C�[�W�[���[�h�ł̃^�[�Q�b�g�֌W�̃N���X
//================================================================

class EasyTarget : public Target
{
private:

	//�^�[�Q�b�g�̍��W
	D3DXVECTOR3 EasyTargetPos[EASYTARGETNUM];

	//�^�[�Q�b�g�̓����蔻��
	OrientedBoundingBox EasyTargetObb[EASYTARGETNUM];


public:

	//�R���X�g���N�^
	EasyTarget();
	//�f�X�g���N�^
	~EasyTarget();

	//������
	void EasyTargetInitialize();
	//�`��
	void EasyTargetDraw();

	bool EasyTargetColl(OrientedBoundingBox obb);

	//�^�[�Q�b�g�����݂��Ă��邩�̃t���O
	bool EasyTargetExistenceFlag[EASYTARGETNUM];

};

//================================================================
//�N���X��  �FNormalTarget�N���X
//���N���X�FTarget�N���X
//
//���e�FTarget����h���������N���X�B�m�[�}�����[�h�ł̃^�[�Q�b�g�֌W�̃N���X
//================================================================

class NormalTarget : public Target
{
private:

	//�^�[�Q�b�g�̍��W
	D3DXVECTOR3 NormalTargetPos[NORMALTARGETNUM];

	//�^�[�Q�b�g�̓����蔻��
	OrientedBoundingBox NormalTargetObb[NORMALTARGETNUM];


public:

	//�R���X�g���N�^
	NormalTarget();
	//�f�X�g���N�^
	~NormalTarget();

	//������
	void NormalTargetInitialize();
	//�`��
	void NormalTargetDraw();

	bool NormalTargetColl(OrientedBoundingBox obb);

	//�^�[�Q�b�g�����݂��Ă��邩�̃t���O
	bool NormalTargetExistenceFlag[NORMALTARGETNUM];


};

//================================================================
//�N���X��  �FHardTarget�N���X
//���N���X�FTarget�N���X
//
//���e�FTarget����h���������N���X�B�n�[�h���[�h�ł̃^�[�Q�b�g�֌W�̃N���X
//================================================================

class HardTarget : public Target
{
private:

	//�^�[�Q�b�g�̍��W
	D3DXVECTOR3 HardTargetPos[HARDTARGETNUM];

	//�^�[�Q�b�g�̓����蔻��
	OrientedBoundingBox HardTargetObb[HARDTARGETNUM];


public:

	//�R���X�g���N�^
	HardTarget();
	//�f�X�g���N�^
	~HardTarget();

	//������
	void HardTargetInitialize();
	//�`��
	void HardTargetDraw();

	bool HardTargetColl(OrientedBoundingBox obb);

	//�^�[�Q�b�g�����݂��Ă��邩�̃t���O
	bool HardTargetExistenceFlag[HARDTARGETNUM];


};