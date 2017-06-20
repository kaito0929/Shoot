#include "Title.h"
#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

DIFFICULTY dif;

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{

}

Title::~Title()
{

}

void Title::Initialize()
{
	//�^�C�g�����S
	TitleTex.Load("Material/title.png");
	TitleSprite.SetPos(600, 450);
	TitleSprite.SetSize(1200, 1000);

	//�G���^�[�������悤�Ɏw������e�N�X�`��
	EnterTex.Load("Material/pushspace.png");
	EnterSprite.SetPos(600, 800);
	EnterSprite.SetSize(600, 400);

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

	EasyTex.Load("Material/easy.png");
	EasySptite.SetPos(1400, 400);
	EasySptite.SetSize(400, 130);

	NormalTex.Load("Material/normal.png");
	NormalSptite.SetPos(1600, 600);
	NormalSptite.SetSize(400, 130);

	HardTex.Load("Material/hard.png");
	HardSptite.SetPos(1800, 800);
	HardSptite.SetSize(400, 130);

	ButtonMoveNum[0] = 1400;
	ButtonMoveNum[1] = 1600;
	ButtonMoveNum[2] = 1800;


	sound.Initialize();
	se.Initialize();

	difficulty = EASY;
	titleState = START;

	difficultySelect[0] = EASY;
	difficultySelect[1] = NORMAL;
	difficultySelect[2] = HARD;


	ButtonMoveFlag = false;
}


void Title::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	//�^�C�g����ʂ̕`��
	Direct3D::DrawSprite(TitleSprite, TitleTex);

	if (titleState == START)
	{
		if (EnterFlashingNum == 0)
		{
			//�G���^�[�L�[�������悤�Ɏw��
			Direct3D::DrawSprite(EnterSprite, EnterTex);
		}
	}

	EasySptite.SetPos(ButtonMoveNum[0], 400);

	NormalSptite.SetPos(ButtonMoveNum[1], 600);

	HardSptite.SetPos(ButtonMoveNum[2], 800);


	Direct3D::DrawSprite(EasySptite, EasyTex);
	Direct3D::DrawSprite(NormalSptite, NormalTex);
	Direct3D::DrawSprite(HardSptite, HardTex);

	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Title::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.TitleSoundPlay();

	//�J�E���g���v���X
	EnterDrawCount++;
	//�\����\����switch�Ő؂�ւ���
	switch (EnterFlashingNum)
	{
	case 0://�e�N�X�`���̕\��
		if (EnterDrawCount % 30 == 0)
		{
			EnterFlashingNum = 1;
		}
		break;
	case 1://�e�N�X�`���̔�\��
		if (EnterDrawCount % 30 == 0)
		{
			EnterFlashingNum = 0;
		}
		break;
	}

	switch (titleState)
	{
	case START:
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			titleState = BUTTONMOVE;
			se.DecisionSEPlay();
		}
		break;
	case BUTTONMOVE:

		for (int i = 0; i < 3; i++)
		{
			if (ButtonMoveNum[i] != 600)
			{
				ButtonMoveNum[i] -= 20;
				ButtonMoveFlag = false;
			}
			else
			{
				ButtonMoveFlag = true;
			}
		}

		if (ButtonMoveFlag == true)
		{
			titleState = SELECT;
		}

		break;
	case SELECT:

		switch (difficulty)
		{
		case EASY:
			EasySptite.SetSize(450, 180);
			NormalSptite.SetSize(400, 130);
			HardSptite.SetSize(400, 130);

			DifficultySelect(difficultySelect[2], difficultySelect[1]);
			dif = EASY;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == 1)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_EASY);
			}

			break;
		case NORMAL:
			EasySptite.SetSize(400, 130);
			NormalSptite.SetSize(450, 180);
			HardSptite.SetSize(400, 130);

			DifficultySelect(difficultySelect[0], difficultySelect[2]);
			dif = NORMAL;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == 1)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_NORMAL);
			}

			break;
		case HARD:
			EasySptite.SetSize(400, 130);
			NormalSptite.SetSize(400, 130);
			HardSptite.SetSize(450, 180);
			
			DifficultySelect(difficultySelect[1], difficultySelect[0]);
			dif = HARD;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == 1)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_HARD);
			}

			break;
		}

		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			FadeFlag = true;
			se.DecisionSEPlay();
		}


		break;
	}



	//FadeFlag��true�Ȃ���s����悤��
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (0.01f*FADE_OUT_CHANGENUM));
	}

	
}


void Title::DifficultySelect(DIFFICULTY dif1, DIFFICULTY dif2)
{
	DirectInput* pDi = DirectInput::GetInstance();

	if (FadeFlag == false)
	{
		if (pDi->KeyJustPressed(DIK_UP))
		{
			difficulty = dif1;
			se.ChoiceSEPlay();
		}

		if (pDi->KeyJustPressed(DIK_DOWN))
		{
			difficulty = dif2;
			se.ChoiceSEPlay();
		}
	}

}