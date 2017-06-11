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


class Stage
{
private:

	//�w�i
	Mesh BackGround;
	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	OrientedBoundingBox obb;

	//�e�����̃x�N�g��
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;

	D3DXVECTOR3 pos;

public:

	Stage();
	~Stage();

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	OrientedBoundingBox* GetObb() { return &obb; }

};