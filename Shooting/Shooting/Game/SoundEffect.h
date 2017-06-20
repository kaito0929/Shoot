#pragma once

#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

class SoundEffect
{
private:

	//���肵�����̌��ʉ�
	WaveFile DecisionSE;
	SoundBuffer sb_DicisionSE[10];

	//�I���������̌��ʉ�
	WaveFile ChoiceSE;
	SoundBuffer sb_ChoiceSE[10];

	//�U���������̌��ʉ�
	WaveFile ShotSE;
	SoundBuffer sb_ShotSE[10];

	//���˂����e�������ɓ���������
	WaveFile ShotHitSE;
	SoundBuffer sb_ShotHitSE[10];

	//���@�������ɓ����������̉�
	WaveFile PlayerHitSE;
	SoundBuffer sb_PlayerHitSE;

public:
	SoundEffect();
	~SoundEffect();

	void Initialize();
	void Update();

	//���艹��炷�֐�
	void DecisionSEPlay();
	//�I������炷�֐�
	void ChoiceSEPlay();
	//�U������炷�֐�
	void ShotSEPlay();
	//���e�������̌��ʉ���炷�֐�
	void ShotHitSEPlay();
	//���@�������ƏՓ˂������Ɍ��ʉ���炷�֐�
	void PlayerHitSEPlay();

};