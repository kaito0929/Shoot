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

#define STAGE_COLLNUM 6

class Stage
{
private:

	//�w�i
	Mesh BackGround;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;


	//�X�e�[�W�̃��f���̓����蔻��
	OrientedBoundingBox StageObb[STAGE_COLLNUM];

	//�e�����̃x�N�g��
	D3DXVECTOR3 forward[STAGE_COLLNUM];
	D3DXVECTOR3 right[STAGE_COLLNUM];
	D3DXVECTOR3 up[STAGE_COLLNUM];

	//�����蔻��̏ꏊ
	D3DXVECTOR3 pos[STAGE_COLLNUM];

public:

	Stage();
	~Stage();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();


	//�X�e�[�W�Ƃ̓����蔻����s���֐�
	bool StageCollision(OrientedBoundingBox obb);


};