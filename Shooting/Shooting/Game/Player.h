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
	D3DXVECTOR3 PlayerAngle;
	//�v���C���[�̑���
	D3DXVECTOR3 PlayerSpeed;

	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	D3DXVECTOR3 rotate;

	//�J��������
	Camera camera;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraPos;
	//�J�����̈ʒu
	D3DXVECTOR3 CameraRel;


	//�����蔻��
	OrientedBoundingBox obb;

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


	void CameraControl();

	OrientedBoundingBox* GetObb() { return &obb; }


};