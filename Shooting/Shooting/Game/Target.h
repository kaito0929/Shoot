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

#define EASYTARGETNUM 5
#define NORMALTARGETNUM 10
#define HARDTARGETNUM 15

//================================================================
//クラス名  ：Targetクラス
//基底クラス：
//
//内容：このクラスを基底クラスとして派生させていく
//================================================================

class Target
{
private:
	
public:
	
	//コンストラクタ
	Target();

	//デストラクタ
	~Target();


	Mesh TargetModel;

	//メッシュに渡す行列を作成
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

	//各方向のベクトル
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	D3DXVECTOR3 up;


};

//================================================================
//クラス名  ：EasyTargetクラス
//基底クラス：Targetクラス
//
//内容：Targetから派生させたクラス。イージーモードでのターゲット関係のクラス
//================================================================

class EasyTarget : public Target
{
private:

	//ターゲットの座標
	D3DXVECTOR3 EasyTargetPos[EASYTARGETNUM];

	//ターゲットの当たり判定
	OrientedBoundingBox EasyTargetObb[EASYTARGETNUM];


public:

	//コンストラクタ
	EasyTarget();
	//デストラクタ
	~EasyTarget();

	//初期化
	void EasyTargetInitialize();
	//描画
	void EasyTargetDraw();

	bool EasyTargetColl(OrientedBoundingBox obb);

	//ターゲットが存在しているかのフラグ
	bool EasyTargetExistenceFlag[EASYTARGETNUM];

};

//================================================================
//クラス名  ：NormalTargetクラス
//基底クラス：Targetクラス
//
//内容：Targetから派生させたクラス。ノーマルモードでのターゲット関係のクラス
//================================================================

class NormalTarget : public Target
{
private:

	//ターゲットの座標
	D3DXVECTOR3 NormalTargetPos[NORMALTARGETNUM];

	//ターゲットの当たり判定
	OrientedBoundingBox NormalTargetObb[NORMALTARGETNUM];


public:

	//コンストラクタ
	NormalTarget();
	//デストラクタ
	~NormalTarget();

	//初期化
	void NormalTargetInitialize();
	//描画
	void NormalTargetDraw();

	bool NormalTargetColl(OrientedBoundingBox obb);

	//ターゲットが存在しているかのフラグ
	bool NormalTargetExistenceFlag[NORMALTARGETNUM];


};

//================================================================
//クラス名  ：HardTargetクラス
//基底クラス：Targetクラス
//
//内容：Targetから派生させたクラス。ハードモードでのターゲット関係のクラス
//================================================================

class HardTarget : public Target
{
private:

	//ターゲットの座標
	D3DXVECTOR3 HardTargetPos[HARDTARGETNUM];

	//ターゲットの当たり判定
	OrientedBoundingBox HardTargetObb[HARDTARGETNUM];


public:

	//コンストラクタ
	HardTarget();
	//デストラクタ
	~HardTarget();

	//初期化
	void HardTargetInitialize();
	//描画
	void HardTargetDraw();

	bool HardTargetColl(OrientedBoundingBox obb);

	//ターゲットが存在しているかのフラグ
	bool HardTargetExistenceFlag[HARDTARGETNUM];


};