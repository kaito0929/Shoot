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

#include "Stage.h"
#include "Target.h"
#include "Shot.h"

#include "SoundEffect.h"

#define PLAYER_SPEED 0.5f			//自機の移動速度
#define PLAYERANGLE_CHANGENUM 0.1f	//自機の向きを変える時の数値

#define PLAYERANGLE_UPMAX -1.0f		//自機の向ける上方向の最大値
#define PLAYERANGLE_DOWNMAX 1.0f	//自機の向ける下方向の最大値
#define PLAYERANGLE_LEFTMAX -3.0f	//自機の向ける左方向の最大値
#define PLAYERANGLE_RIGHTMAX 3.0f	//自機の向ける右方向の最大値

#define CAMERA_RADIUS_PLUS 60.0f
#define CAMERA_RADIUS_MINUS -60.0f


class Player
{
private:

	//プレイヤーのモデル
	Mesh PlayerModel;
	
	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//プレイヤーの位置
	D3DXVECTOR3 PlayerPos;
	//プレイヤーの向き
	D3DXVECTOR3 Direction;

	float PlayerYaw;
	float PlayerPitch;


	//各方向のベクトル
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;


	//カメラ操作
	Camera camera;
	//カメラの位置
	D3DXVECTOR3 CameraPos;
	//カメラの位置
	D3DXVECTOR3 CameraRel;

	//プレイヤーの当たり判定
	OrientedBoundingBox PlayerObb;

	//プレイヤーの生存フラグ
	bool PlayerAliveFlag;

	//弾発射のフラグ
	bool ShotFlag[SHOTNUM];
	int ShotNum;

	//ターゲットを全て破壊したかのフラグ
	bool TargetOllBreakFlag;


	Stage stage;
	Shot shot;
	EasyTarget easyTarget;
	NormalTarget normalTarget;
	HardTarget hardTarget;

	SoundEffect se;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//実際の動き
	void Update();
	//描画
	void Draw();

	//プレイヤーの移動の制御
	void PlayerMoveControl();

	//カメラの動きの制御
	void CameraControl();

	//プレイヤーの当たり判定の動き
	void PlayerObbUpdate();

	bool GetAliveFlag() { return PlayerAliveFlag; };

	bool GetOllBreakFlag() { return TargetOllBreakFlag; };



	//--□イージーモード関係□---------------------------------
	void EasyInitialize();
	void EasyDraw();
	void EasyUpdate();
	//--□ノーマルモード関係□---------------------------------
	void NormalInitialize();
	void NormalDraw();
	void NormalUpdate();
	//--□ハードモード関係□---------------------------------
	void HardInitialize();
	void HardDraw();
	void HardUpdate();


};