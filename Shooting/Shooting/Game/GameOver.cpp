#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../directInput.h"

#include "GameOver.h"
#include "Title.h"

GameOver::GameOver(ISceneChanger* changer) : BaseScene(changer)
{

}

GameOver::~GameOver()
{

}

//�������֐�
void GameOver::Initialize()
{
	GameOverTex.Load("Material/gameover.png");
	GameOverSprite.SetPos(600, 450);
	GameOverSprite.SetSize(1200, 1000);

	RetryTex.Load("Material/retry.png");
	RetrySptite.SetPos(300, 700);
	RetrySptite.SetSize(300, 200);

	TitleGoTex.Load("Material/titlego.png");
	TitleGoSprite.SetPos(900, 700);
	TitleGoSprite.SetSize(300, 200);

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(1);

	FadeFlag = false;

	gameoverState = FADE;

	sound.Initialize();
	se.Initialize();
}

//�`��֐�
void GameOver::Draw()
{
	Direct3D::DrawSprite(GameOverSprite, GameOverTex);

	Direct3D::DrawSprite(RetrySptite, RetryTex);
	Direct3D::DrawSprite(TitleGoSprite, TitleGoTex);

	//�t�F�[�h�C���A�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

//���C���̓���
void GameOver::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.GameOverSoundPlay();

	switch (gameoverState)
	{
	case FADE:	//�t�F�[�h�C��

		//�t�F�[�h�C���J�n
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_IN_CHANGENUM));

		//�t�F�[�h�C�����I�������^�C�~���O��State��؂�ւ���
		if (FadeSprite.GetAlpha() == FADE_IN_END)
		{
			gameoverState = RETRY;
		}

		break;

	case RETRY:	//������Փx�ōĊJ

		//�{�^���̃T�C�Y��ύX
		RetrySptite.SetSize(350, 250);
		TitleGoSprite.SetSize(300, 200);

		//�ĊJ���A�^�C�g���ֈړ������肵�ĂȂ���Ώ���
		//�ǂ���ɂ��邩�I�����邩���肵���肷��
		if (FadeFlag == false)
		{
			//�^�C�g���ւ�I��
			if (pDi->KeyJustPressed(DIK_RIGHT) || pDi->KeyJustPressed(DIK_LEFT))
			{
				gameoverState = TITLEGO;
				se.ChoiceSEPlay();
			}

			//������Փx�ōĊJ
			if (pDi->KeyJustPressed(DIK_SPACE))
			{
				se.DecisionSEPlay();
				//�t�F�[�h�A�E�g�J�n
				FadeFlag = true;
			}
		}

		//�e�N�X�`���̃��l��1�ɂȂ�����BGM���~�߂đJ�ڊJ�n
		if (FadeSprite.GetAlpha() == FADE_OUT_END)
		{
			sound.GameOverSoundStop();
			switch (dif)
			{
			case EASY:
				mSceneChanger->ChangeScene(STATE_EASY);
				break;
			case NORMAL:
				mSceneChanger->ChangeScene(STATE_NORMAL);
				break;
			case HARD:
				mSceneChanger->ChangeScene(STATE_HARD);
				break;
			}
		}

		break;

	case TITLEGO:	//�^�C�g���֑J��

		//��{�I�ȗ���͏�L�ƈꏏ�̈�
		//�R�����g�͏�L���Q�Ƃ��Ă�������

		RetrySptite.SetSize(300, 200);
		TitleGoSprite.SetSize(350, 250);

		if (FadeFlag == false)
		{
			if (pDi->KeyJustPressed(DIK_RIGHT) || pDi->KeyJustPressed(DIK_LEFT))
			{
				gameoverState = RETRY;
				se.ChoiceSEPlay();
			}

			if (pDi->KeyJustPressed(DIK_SPACE))
			{
				se.DecisionSEPlay();
				FadeFlag = true;
			}
		}

		if (FadeSprite.GetAlpha() == FADE_OUT_END)
		{
			sound.GameOverSoundStop();
			mSceneChanger->ChangeScene(STATE_TITLE);
		}

		break;
	}



	//FadeFlag��true�Ȃ���s����悤��
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}


}

