#include "Player.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include <stdio.h>
#include <stdlib.h>	//rand()関数用
#include <time.h>	//time()関数用
#include <math.h>


Player::Player()
{		

}

Player::~Player()
{

}

//初期化関数
void Player::Initialize()
{
	PlayerModel.Load(_T("Model/Player.x"));


	PlayerPos.x = 0.0f;
	PlayerPos.y = 30.0f;
	PlayerPos.z = 0.0f;

	PlayerAngle.x = 0.0f;
	PlayerAngle.y = 0.0f;
	PlayerAngle.z = 0.0f;

	CameraPos.x = 0.0f;
	CameraPos.y = 50.0f;
	CameraPos.z = -60.0f;

	CameraRel.x = 0.0f;
	CameraRel.y = -4.0f;
	CameraRel.z = 10.0f;


	right.x = cos(0);
	right.y = 0;
	right.z = sin(0);

	up.x = 0;
	up.y = 1;
	up.z = 0;

	PlayerObb.SetLength(20, 10, 10);

	PlayerAliveFlag = true;

	for (int i = 0;i < SHOTNUM; i++)
	{
		ShotFlag[i] = false;
	}

	stage.Initialize();
	shot.Initialize();
	se.Initialize();
}

//描画関数
void Player::Draw()
{
	D3DXMatrixTranslation(&mat_transform, PlayerPos.x, PlayerPos.y, PlayerPos.z);	//座標
	D3DXMatrixScaling(&mat_scale, 0.1f, 0.1f, 0.1f);								//拡大
	D3DXMatrixRotationYawPitchRoll(&mat_rotate,PlayerAngle.x, PlayerAngle.y, PlayerAngle.z);//回転

	if (PlayerAliveFlag == true)
	{
		//プレイヤー（自機）の描画
		PlayerModel.Draw(mat_transform, mat_scale, mat_rotate);
	}

	for (int i = 0; i < SHOTNUM; i++)
	{
		//ShotFlagがtrueの時に弾を描画
		if (ShotFlag[i] == true)
		{
			shot.BulletShot(ShotFlag);
		}
	}

	stage.Draw();
}

void Player::Update()
{
	stage.Update();
	shot.Update();

	shot.ShotPosSet(PlayerPos, PlayerAngle, ShotFlag);

	//プレイヤーの生存フラグがtrueならば処理を行うように
	if (PlayerAliveFlag == true)
	{
		PlayerMoveControl();
		CameraControl();
		PlayerObbUpdate();
	}

	if (ShotNum == 5)
	{
		ShotNum = 0;
	}

}

//プレイヤーの動きの制御
void Player::PlayerMoveControl()
{
	DirectInput* pDi = DirectInput::GetInstance();

	////プレイヤーの向いている方向に向かって自動で前進
	PlayerPos.x += sin(PlayerAngle.x)*PLAYER_SPEED;
	PlayerPos.y += sin(-PlayerAngle.y)*PLAYER_SPEED;
	PlayerPos.z += cos(PlayerAngle.z)*PLAYER_SPEED;

	//下方への方向転換
	if (pDi->KeyCount(DIK_UP))
	{
		PlayerAngle.y += PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y >= PLAYERANGLE_DOWNMAX)
		{
			PlayerAngle.y = PLAYERANGLE_DOWNMAX;
		}
	}
	//上方への方向変換
	if (pDi->KeyCount(DIK_DOWN))
	{
		PlayerAngle.y -= PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.y <= PLAYERANGLE_UPMAX)
		{
			PlayerAngle.y = PLAYERANGLE_UPMAX;
		}
	}

	//左への方向転換
	if (pDi->KeyCount(DIK_LEFT))
	{
		PlayerAngle.z -= PLAYERANGLE_CHANGENUM;
		PlayerAngle.x -= PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.z <= PLAYERANGLE_LEFTMAX&&PlayerAngle.x <= PLAYERANGLE_LEFTMAX)
		{
			PlayerAngle.z = PLAYERANGLE_LEFTMAX;
			PlayerAngle.x = PLAYERANGLE_LEFTMAX;
		}
	}

	//右への方向変換
	if (pDi->KeyCount(DIK_RIGHT))
	{
		PlayerAngle.z += PLAYERANGLE_CHANGENUM;
		PlayerAngle.x += PLAYERANGLE_CHANGENUM;

		if (PlayerAngle.z >= PLAYERANGLE_RIGHTMAX&&PlayerAngle.x >= PLAYERANGLE_RIGHTMAX)
		{
			PlayerAngle.z = PLAYERANGLE_RIGHTMAX;
			PlayerAngle.x = PLAYERANGLE_RIGHTMAX;
		}
	}

	//スペースキーを押して弾を発射
	if (pDi->KeyJustPressed(DIK_SPACE))
	{
		if (ShotFlag[ShotNum] == false)
		{
			ShotFlag[ShotNum] = true;
			ShotNum++;
			se.ShotSEPlay();
		}
	}

}


//カメラの動きの制御
void Player::CameraControl()
{
	//自機に合わせたカメラの移動
	CameraPos.x = PlayerPos.x + sin(PlayerAngle.x)*CAMERA_RADIUS_MINUS;
	CameraPos.y = (PlayerPos.y+20.0f) + sin(-PlayerAngle.y)*CAMERA_RADIUS_MINUS;
	CameraPos.z = PlayerPos.z + cos(PlayerAngle.z)*CAMERA_RADIUS_MINUS;

	//自機の方向に合わせたカメラの方向変換
	CameraRel.x = sin(PlayerAngle.x)*CAMERA_RADIUS_PLUS;
	CameraRel.y = sin(-PlayerAngle.y)*CAMERA_RADIUS_PLUS;
	CameraRel.z = cos(PlayerAngle.z)*CAMERA_RADIUS_PLUS;

	//座標の更新
	camera.SetEyePoint(CameraPos);
	//方向の更新
	camera.SetRelLookAtPoint(CameraRel);	

	camera.UpdateViewMatrix();
}

//プレイヤーの当たり判定の制御
void Player::PlayerObbUpdate()
{
	//正面	
	forward.x = cos(-PlayerAngle.x + (D3DX_PI / 2));
	forward.y = cos(PlayerAngle.y + (D3DX_PI / 2));
	forward.z = sin(-PlayerAngle.z + (D3DX_PI / 2));

	//右側
	right.x = cos(-PlayerAngle.x);
	right.y = 0;
	right.z = sin(-PlayerAngle.z);

	PlayerObb.UpdateInfo(PlayerPos, forward, right, up);
}

//--□イージーモード関係□------------------------------------------------------------
void Player::EasyInitialize()
{
	easyTarget.EasyTargetInitialize();
}

void Player::EasyDraw()
{
	easyTarget.EasyTargetDraw();
}

void Player::EasyUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//弾がステージかターゲットに当たった時の処理を行う
			if (stage.StageCollision(shot.bulletObb[i]) == true || easyTarget.EasyTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i] = false;
				se.ShotHitSEPlay();
			}
		}
	}

	//ステージとプレイヤーの当たり判定を処理する
	if (stage.StageCollision(PlayerObb) == true || easyTarget.EasyTargetColl(PlayerObb) == true)
	{
		PlayerAliveFlag = false;
		se.PlayerHitSEPlay();
	}


	for (int i = 0; i < EASYTARGETNUM; i++)
	{
		if (easyTarget.EasyTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}

//--□ノーマルモード関係□------------------------------------------------------------
void Player::NormalInitialize()
{
	normalTarget.NormalTargetInitialize();
}

void Player::NormalDraw()
{
	normalTarget.NormalTargetDraw();
}

void Player::NormalUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//弾がステージかターゲットに当たった時の処理を行う
			if (stage.StageCollision(shot.bulletObb[i]) == true || normalTarget.NormalTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i] = false;
				se.ShotHitSEPlay();
			}
		}
	}

	//ステージとプレイヤーの当たり判定を処理する
	if (stage.StageCollision(PlayerObb) == true || normalTarget.NormalTargetColl(PlayerObb) == true)
	{
		PlayerAliveFlag = false;
		se.PlayerHitSEPlay();
	}


	for (int i = 0; i < NORMALTARGETNUM; i++)
	{
		if (normalTarget.NormalTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}


//--□ハードモード関係□------------------------------------------------------------
void Player::HardInitialize()
{
	hardTarget.HardTargetInitialize();
}

void Player::HardDraw()
{
	hardTarget.HardTargetDraw();
}

void Player::HardUpdate()
{
	for (int i = 0; i < SHOTNUM; i++)
	{
		if (ShotFlag[i] == true)
		{
			//弾がステージかターゲットに当たった時の処理を行う
			if (stage.StageCollision(shot.bulletObb[i]) == true || hardTarget.HardTargetColl(shot.bulletObb[i]) == true)
			{
				ShotFlag[i]= false;
				se.ShotHitSEPlay();
			}
		}
	}

	//ステージとプレイヤーの当たり判定を処理する
	if (stage.StageCollision(PlayerObb) == true || hardTarget.HardTargetColl(PlayerObb) == true)
	{
		PlayerAliveFlag = false;
		se.PlayerHitSEPlay();
	}


	for (int i = 0; i < HARDTARGETNUM; i++)
	{
		if (hardTarget.HardTargetExistenceFlag[i] == true)
		{
			TargetOllBreakFlag = false;
			break;
		}
		else
		{
			TargetOllBreakFlag = true;
		}
	}
}