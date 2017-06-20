#pragma once

#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

class SoundEffect
{
private:

	//決定した時の効果音
	WaveFile DecisionSE;
	SoundBuffer sb_DicisionSE[10];

	//選択した時の効果音
	WaveFile ChoiceSE;
	SoundBuffer sb_ChoiceSE[10];

	//攻撃した時の効果音
	WaveFile ShotSE;
	SoundBuffer sb_ShotSE[10];

	//発射した弾が何かに当たった音
	WaveFile ShotHitSE;
	SoundBuffer sb_ShotHitSE[10];

	//自機が何かに当たった時の音
	WaveFile PlayerHitSE;
	SoundBuffer sb_PlayerHitSE;

public:
	SoundEffect();
	~SoundEffect();

	void Initialize();
	void Update();

	//決定音を鳴らす関数
	void DecisionSEPlay();
	//選択音を鳴らす関数
	void ChoiceSEPlay();
	//攻撃音を鳴らす関数
	void ShotSEPlay();
	//着弾した時の効果音を鳴らす関数
	void ShotHitSEPlay();
	//自機が何かと衝突した時に効果音を鳴らす関数
	void PlayerHitSEPlay();

};