#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "SoundEffect.h"

SoundEffect::SoundEffect()
{

}

SoundEffect::~SoundEffect()
{
	
}

void SoundEffect::Initialize()
{

	//���肵�����̌��ʉ�
	DecisionSE.Load("Sound/decision.wav");

	//�I���������̌��ʉ�
	ChoiceSE.Load("Sound/choice.wav");

	//���ˉ�
	ShotSE.Load("Sound/shot.wav");

	//���e��
	ShotHitSE.Load("Sound/shotHit.wav");

	//���@�̏Փˉ�
	PlayerHitSE.Load("Sound/playerHit.wav");
	sb_PlayerHitSE.Create(PlayerHitSE);

	for (int i = 0; i < 10; i++)
	{
		sb_DicisionSE[i].Create(DecisionSE);
		sb_ChoiceSE[i].Create(ChoiceSE);
		sb_ShotSE[i].Create(ShotSE);
		sb_ShotHitSE[i].Create(ShotHitSE);
	}

}

void SoundEffect::Update()
{

}

//���艹��炷�֐�
void SoundEffect::DecisionSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_DicisionSE[i].Playing() == false)
		{
			sb_DicisionSE[i].Play(false);
			break;
		}
	}
}

//�I������炷�֐�
void SoundEffect::ChoiceSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_ChoiceSE[i].Playing() == false)
		{
			sb_ChoiceSE[i].Play(false);
			break;
		}
	}
}

//���ˉ���炷�֐�
void SoundEffect::ShotSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_ShotSE[i].Playing() == false)
		{
			sb_ShotSE[i].Play(false);
			break;
		}
	}
}

//���e����炷�֐�
void SoundEffect::ShotHitSEPlay()
{
	for (int i = 0; i < 10; i++)
	{
		if (sb_ShotHitSE[i].Playing() == false)
		{
			sb_ShotHitSE[i].Play(false);
			break;
		}
	}
}

void SoundEffect::PlayerHitSEPlay()
{
	sb_PlayerHitSE.Play(false);
}