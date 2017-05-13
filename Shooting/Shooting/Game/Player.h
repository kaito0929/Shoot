#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"

class Player
{
private:

	//�v���C���[�̃��f��
	Mesh PlayerModel;
	//�e�̃��f��
	Mesh Bullet;

	Camera camera;

	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform2, mat_scale2, mat_rotate2;

	//�v���C���[�̈ʒu
	D3DXVECTOR3 PlayerPos;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPos;


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

	//�v���C���[�̒e�̔���
	void BulletShot();

};