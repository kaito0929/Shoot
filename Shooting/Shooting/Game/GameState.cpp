#include "GameState.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()�֐��p
#include <time.h>	//time()�֐��p

float x = 0.0f;
float y = 0.0f;


GameState::GameState()
{
	
}

GameState::~GameState()
{

}
//�������֐�
void GameState::Initialize()
{
	Player.Load(_T("Model/Player2.x"));

	camera.SetEyePoint(0.0f, 60.0f, -60.0f);
	camera.SetRelLookAtPoint(0.0f, -10.0f, 1.0f);
}
//�`��֐�
void GameState::Draw()
{

	D3DXMatrixTranslation(&mat_transform, x, y, 0.0f);	//���W
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);		//�g��
	D3DXMatrixRotationY(&mat_rotate, 0);					//��]�@�iy�����S�j

	Player.Draw(mat_transform, mat_scale, mat_rotate);

}
//���C���̓���
void GameState::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	float f = 0.0f;
	float r = 0.0f;

	
	camera.Move(f, r);

	//D3DXMatrixTranslation(&mat_transform, x, y, 0.0f);	//���W

	if (pDi->KeyCount(DIK_UP))
	{
		y += 0.1;
	}
	if (pDi->KeyCount(DIK_DOWN))
	{
		y -= 0.1;
	}
	if (pDi->KeyCount(DIK_RIGHT))
	{
		x -= 0.1;
	}
	if (pDi->KeyCount(DIK_LEFT))
	{
		x += 0.1;
	}

	camera.Rotate(0.0f, 0.0f);

	

	camera.UpdateViewMatrix();
}