#include "GameState.h"
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

//初期化関数
void Stage::Initialize()
{
	BackGround.Load(_T("Model/spaceBox.x"));
	D3DXMatrixTranslation(&mat_transform, 0.0f, 0.0f, 0.0f);	//座標
	D3DXMatrixScaling(&mat_scale, 1.0f, 1.0f, 1.0f);		//拡大
	D3DXMatrixRotationY(&mat_rotate, 0);					//回転　（y軸中心）

	forward.x = cos(D3DX_PI / 2);
	forward.y = sin(D3DX_PI / 2);
	forward.z = 0;

	right.x = cos(0);
	right.y = sin(0);
	right.z = 0;

	up.x = 0;
	up.z = 1;
	up.y = 0;

	pos.x = 0;
	pos.y = 20;
	pos.z = 20;

	obb.SetLength(20, 20, 20);
	obb.UpdateInfo(pos, forward, right, up);
}

//描画関数
void Stage::Draw()
{
	BackGround.Draw(mat_transform, mat_scale, mat_rotate);
	obb.DrawLine();
}


void Stage::Update()
{
	obb.UpdateInfo(pos, forward, right, up);

}