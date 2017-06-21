#include "Title.h"
#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

//�Q�[���I�[�o�[��ʂł̃��g���C��I�񂾍ۂ�
//�J�ڂ���V�[�������肷��O���[�o���ϐ�
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

	//�C�[�W�[
	EasyTex.Load("Material/easy.png");
	EasySptite.SetPos(1400, 400);
	EasySptite.SetSize(400, 130);

	//�m�[�}��
	NormalTex.Load("Material/normal.png");
	NormalSptite.SetPos(1600, 600);
	NormalSptite.SetSize(400, 130);

	//�n�[�h
	HardTex.Load("Material/hard.png");
	HardSptite.SetPos(1800, 800);
	HardSptite.SetSize(400, 130);

	ButtonMoveNum[0] = 1400;
	ButtonMoveNum[1] = 1600;
	ButtonMoveNum[2] = 1800;

	ButtonSizeStandardX = 400;
	ButtonSizeStandardY = 130;
	ButtonSizeMaxX = 450;
	ButtonSizeMaxY = 180;

	sound.Initialize();
	se.Initialize();

	difficulty = EASY;
	titleState = START;

	difficultySelect[0] = EASY;
	difficultySelect[1] = NORMAL;
	difficultySelect[2] = HARD;


	DrawCount = 0;
	DrawFlag = true;

	ButtonMoveFlag = false;
}


void Title::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	//�^�C�g����ʂ̕`��
	Direct3D::DrawSprite(TitleSprite, TitleTex);

	if (titleState == START)
	{
		if (DrawFlag == true)
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

	switch (titleState)
	{
	case START:		//�X�y�[�X�L�[�������悤�Ɏw��

		PushKeyDraw();

		//�X�y�[�X�L�[���������珈��
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			titleState = BUTTONMOVE;
			se.DecisionSEPlay();
		}

		break;
	case BUTTONMOVE:	//�{�^�����ړ�������

		//�O�̃{�^���̈ʒu����ʒ����Ɉړ�����悤�ɏ���
		for (int i = 0; i < DIFFICULTY_NUM; i++)
		{
			if (ButtonMoveNum[i] != SCREEN_CENTERX)
			{
				ButtonMoveNum[i] -= BUTTON_MOVE_SPEED;
				ButtonMoveFlag = false;
			}
			else
			{
				//�{�^���̈ړ������������t���O
				ButtonMoveFlag = true;
			}
		}

		//�{�^���̈ړ������������t���O��true�ɂȂ�Ώ���
		if (ButtonMoveFlag == true)
		{
			//��Փx�I����
			titleState = SELECT;
		}

		break;
	case SELECT:	//��Փx�I��

		//�I�����Ă����Փx�ɂ���ă{�^���̃T�C�Y��ς�����
		//�J�ڂ���V�[����ύX����
		switch (difficulty)
		{
		case EASY:		//�C�[�W�[���[�h

			//�C�[�W�[���[�h��I�����Ă���{�^���̃T�C�Y��傫��
			EasySptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//���̃{�^���͕W���T�C�Y�̕ύX���Ă���
			NormalSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			HardSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);

			DifficultySelect(difficultySelect[2], difficultySelect[1]);
			dif = EASY;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_EASY);
			}

			break;
		case NORMAL:		//�m�[�}�����[�h

			//�m�[�}�����[�h��I�����Ă���{�^���̃T�C�Y��傫��
			NormalSptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//���̃{�^���͕W���T�C�Y�̕ύX���Ă���
			EasySptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			HardSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);

			DifficultySelect(difficultySelect[0], difficultySelect[2]);
			dif = NORMAL;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_NORMAL);
			}

			break;
		case HARD:		//�n�[�h���[�h

			//�n�[�h���[�h��I�����Ă���{�^���̃T�C�Y��傫��
			HardSptite.SetSize(ButtonSizeMaxX, ButtonSizeMaxY);
			//���̃{�^���͕W���T�C�Y�̕ύX���Ă���
			EasySptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			NormalSptite.SetSize(ButtonSizeStandardX, ButtonSizeStandardY);
			
			DifficultySelect(difficultySelect[1], difficultySelect[0]);
			dif = HARD;

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.TitleSoundStop();
				mSceneChanger->ChangeScene(STATE_HARD);
			}
			break;
		}

		//��Փx�I�����ăX�y�[�X�L�[����������t�F�[�h�A�E�g�J�n
		if (pDi->KeyJustPressed(DIK_SPACE))
		{
			if (FadeFlag == false)
			{
				FadeFlag = true;
				se.DecisionSEPlay();
			}
		}


		break;
	}

	//FadeFlag��true�Ȃ���s����悤��
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}

	
}


//��Փx�I������������֐�
void Title::DifficultySelect(DIFFICULTY dif1, DIFFICULTY dif2)
{
	DirectInput* pDi = DirectInput::GetInstance();

	//�t�F�[�h�A�E�g���J�n���Ă��Ȃ���Ώ���
	if (FadeFlag == false)
	{
		//��L�[���������炻�̏�̓�Փx�ɑ��
		if (pDi->KeyJustPressed(DIK_UP))
		{
			difficulty = dif1;
			se.ChoiceSEPlay();
		}

		//���L�[���������炻�̉��̓�Փx�ɑ��
		if (pDi->KeyJustPressed(DIK_DOWN))
		{
			difficulty = dif2;
			se.ChoiceSEPlay();
		}
	}
}

//�e�N�X�`����_�ł����邽�߂̏���
void Title::PushKeyDraw()
{
	//�J�E���g���v���X
	DrawCount++;

	//�t���O��true��false�ɐ؂�ւ��邱�Ƃɂ����
	//�e�N�X�`���̕\����\����؂�ւ��Ă���
	if (DrawFlag == false)
	{
		if (DrawCount % TEXTURE_DARW_SPEED == TEXTURE_DARW_TIMING)
		{
			DrawFlag = true;
		}
	}
	else
	{
		if (DrawCount % TEXTURE_DARW_SPEED == TEXTURE_DARW_TIMING)
		{
			DrawFlag = false;
		}
	}
}