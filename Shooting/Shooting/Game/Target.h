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

#define TARGETNUM 5

class Target
{
private:

	Mesh TargetModel;

	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//�^�[�Q�b�g�̍��W
	D3DXVECTOR3 TargetPos[TARGETNUM];

	//�^�[�Q�b�g�̓����蔻��
	OrientedBoundingBox TargetObb[TARGETNUM];

	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	//�^�[�Q�b�g�̑��݂��Ă��邩�̃t���O
	bool TargetExistenceFlag[TARGETNUM];

public:
	
	//�R���X�g���N�^
	Target();

	//�f�X�g���N�^
	~Target();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();


	bool TargetColl(OrientedBoundingBox obb);


};