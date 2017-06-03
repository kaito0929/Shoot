#include "GameState.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()関数用
#include <time.h>	//time()関数用

float x = 0;

GameState::GameState()
{
	
}

GameState::~GameState()
{

}
//初期化関数
void GameState::Initialize()
{
	player.Initialize();

	BackGround.Load(_T("Model/spaceBox.x"));
	D3DXMatrixTranslation(&mat_transform, 0.0f, 0.0f,0.0f);	//座標
	D3DXMatrixScaling(&mat_scale, 1.0f, 1.0f, 1.0f);		//拡大
	D3DXMatrixRotationY(&mat_rotate, 0);					//回転　（y軸中心）

	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.z = 0;
	up.y = 0;

	pos.x = 0;
	pos.y = 20;
	pos.z = 20;

	obb.SetLength(20, 10, 10);
	obb.UpdateInfo(pos, forward, right, up);
}
//描画関数
void GameState::Draw()
{
	//obb.DrawLine();

	BackGround.Draw(mat_transform, mat_scale, mat_rotate);

	player.Draw();
}

//メインの動作
void GameState::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	if (OrientedBoundingBox::Collision(obb, *(player.GetObb())))
	{
		int a = 0;
	}

	obb.UpdateInfo(pos, forward, right, up);


	player.Update();
}