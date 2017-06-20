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

	//Œˆ’è‚µ‚½‚ÌŒø‰Ê‰¹
	DecisionSE.Load("Sound/decision.wav");

	//‘I‘ğ‚µ‚½‚ÌŒø‰Ê‰¹
	ChoiceSE.Load("Sound/choice.wav");

	//”­Ë‰¹
	ShotSE.Load("Sound/shot.wav");

	//’…’e‰¹
	ShotHitSE.Load("Sound/shotHit.wav");

	//©‹@‚ÌÕ“Ë‰¹
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

//Œˆ’è‰¹‚ğ–Â‚ç‚·ŠÖ”
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

//‘I‘ğ‰¹‚ğ–Â‚ç‚·ŠÖ”
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

//”­Ë‰¹‚ğ–Â‚ç‚·ŠÖ”
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

//’…’e‰¹‚ğ–Â‚ç‚·ŠÖ”
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