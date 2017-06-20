#include "Stage.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

Stage::Stage()
{

}

Stage::~Stage()
{

}

//�������֐�
void Stage::Initialize()
{
	BackGround.Load(_T("Model/spaceBox.x"));
	D3DXMatrixTranslation(&mat_transform, 0.0f, 0.0f, 0.0f);	//���W
	D3DXMatrixScaling(&mat_scale, 1.0f, 1.0f, 1.0f);		//�g��
	D3DXMatrixRotationY(&mat_rotate, 0);					//��]�@�iy�����S�j

	//������Ԃ̐��ʂ̖ʂ̓����蔻��--------------------------------------------
	forward[0].x = cos(D3DX_PI / 2);
	forward[0].y = sin(D3DX_PI / 2);
	forward[0].z = 0;

	right[0].x = cos(0);
	right[0].y = sin(0);
	right[0].z = 0;

	up[0].x = 0;
	up[0].y = 0;
	up[0].z = 0;

	pos[0].x = 0;
	pos[0].y = 100;
	pos[0].z = 100;
	//---------------------------------------------------------------------------

	//������Ԃ̌�둤�̖ʂ̓����蔻��-------------------------------------------

	forward[1].x = cos(D3DX_PI / 2);
	forward[1].y = sin(D3DX_PI / 2);
	forward[1].z = 0;

	right[1].x = cos(0);
	right[1].y = sin(0);
	right[1].z = 0;

	up[1].x = 0;
	up[1].y = 0;
	up[1].z = 0;

	pos[1].x = 0;
	pos[1].y = 100;
	pos[1].z = -100;

	//---------------------------------------------------------------------------

	//������Ԃ̉E���̖ʂ̓����蔻��---------------------------------------------

	forward[2].x = cos(D3DX_PI / 2);
	forward[2].y = 0;
	forward[2].z = sin(D3DX_PI / 2);

	right[2].x = 0;
	right[2].y = sin(0);
	right[2].z = 0;

	up[2].x = 0;
	up[2].y = 1;
	up[2].z = 0;

	pos[2].x = 100;
	pos[2].y = 100;
	pos[2].z = 0;

	//---------------------------------------------------------------------------

	//������Ԃ̍����̖ʂ̓����蔻��---------------------------------------------

	forward[3].x = cos(D3DX_PI / 2);
	forward[3].y = 0;
	forward[3].z = sin(D3DX_PI / 2);

	right[3].x = 0;
	right[3].y = sin(0);
	right[3].z = 0;

	up[3].x = 0;
	up[3].y = 1;
	up[3].z = 0;

	pos[3].x = -100;
	pos[3].y = 100;
	pos[3].z = 0;

	//---------------------------------------------------------------------------

	//������Ԃ̉����̖ʂ̓����蔻��---------------------------------------------

	forward[4].x = cos(D3DX_PI / 2);
	forward[4].y = 0;
	forward[4].z = sin(D3DX_PI / 2);

	right[4].x = cos(0);
	right[4].y = sin(0);
	right[4].z = 0;

	up[4].x = 0;
	up[4].y = 0;
	up[4].z = 0;

	pos[4].x = 0;
	pos[4].y = 0;
	pos[4].z = 0;

	//---------------------------------------------------------------------------

	//������Ԃ̏㑤�̖ʂ̓����蔻��---------------------------------------------

	forward[5].x = cos(D3DX_PI / 2);
	forward[5].y = 0;
	forward[5].z = sin(D3DX_PI / 2);

	right[5].x = cos(0);
	right[5].y = sin(0);
	right[5].z = 0;

	up[5].x = 0;
	up[5].y = 0;
	up[5].z = 0;

	pos[5].x = 0;
	pos[5].y = 200;
	pos[5].z = 0;

	//---------------------------------------------------------------------------


	for (int i = 0; i < 6; i++)
	{
		StageObb[i].SetLength(200, 200, 200);
		StageObb[i].UpdateInfo(pos[i], forward[i], right[i], up[i]);
	}
}

//�`��֐�
void Stage::Draw()
{
	BackGround.Draw(mat_transform, mat_scale, mat_rotate);
}


void Stage::Update()
{
	for (int i = 0; i < 6; i++)
	{
		StageObb[i].UpdateInfo(pos[i], forward[i], right[i], up[i]);
	}
}


//�X�e�[�W�Ƃ̓����蔻����s���֐�
//obb�ɔ������肽�����f���̓����蔻�������
bool Stage::StageCollision(OrientedBoundingBox obb)
{
	for (int i = 0; i < STAGE_COLLNUM; i++)
	{
		if (OrientedBoundingBox::Collision(obb, StageObb[i]))
		{
			return true;
		}
	}
}