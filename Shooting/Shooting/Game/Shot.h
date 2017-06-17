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

#define SHOTSPEED 2.0f

class Shot
{
private:

	//�e�̃��f��
	Mesh Bullet;

	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;


	//�e�̍��W
	D3DXVECTOR3 BulletPos;

	//�e�̔��˂�������Ɛi�ޕ���
	D3DXVECTOR3 BulletAngle;


	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

public:

	//�R���X�g���N�^
	Shot();

	//�f�X�g���N�^
	~Shot();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	void BulletShot();

	void ShotPosSet(D3DXVECTOR3 pPos,D3DXVECTOR3 pAngle,bool shotFlag);


	//�e�̓����蔻��
	OrientedBoundingBox bulletObb;


};