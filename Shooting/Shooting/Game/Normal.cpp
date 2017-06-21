#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Normal.h"

Normal::Normal(ISceneChanger* changer) : BaseScene(changer)
{

}

Normal::~Normal()
{

}

//�������֐�
void Normal::Initialize()
{
	player.Initialize();
	player.NormalInitialize();
	sound.Initialize();
	se.Initialize();

	StartTexPosX = 1400;
	StartCount = 0;

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(1);

	StartTex.Load("Material/start.png");
	StartSprite.SetPos(StartTexPosX, 300);
	StartSprite.SetSize(400, 200);

	playState = FADE_IN;
}

//�`��֐�
void Normal::Draw()
{
	StartSprite.SetPos(StartTexPosX, 300);

	player.Draw();
	player.NormalDraw();

	Direct3D::DrawSprite(StartSprite, StartTex);

	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);
}

void Normal::Update()
{
	switch (playState)
	{
	case FADE_IN:		//�t�F�[�h�C���J�n

						//�t�F�[�h�C�������s
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_IN_CHANGENUM));

		//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[����J��
		if (FadeSprite.GetAlpha() == FADE_IN_END)
		{
			playState = START_SIGNAL;
		}

		break;
	case START_SIGNAL:		//�Q�[���X�^�[�g�̍��}

							//�X�^�[�g�̃e�N�X�`������ʒ����܂ňړ�
		if (StartTexPosX != SCREEN_CENTERX)
		{
			StartTexPosX -= STARTTEX_MOVE;
		}
		else
		{
			//��ʒ����Ɉړ�������SE���Đ�
			se.StartSEPlay();
			//�v���C���[�̑��삪�\�ɂȂ�܂ł̃J�E���g�����Z
			StartCount++;
		}

		//�J�E���g��10�𒴂�����v���C���[�̑�����\��
		if (StartCount >= START_COUNT_MAX)
		{
			playState = MAIN;
		}

		break;
	case MAIN:		//�v���C���[�̑���

		player.Update();
		player.NormalUpdate();
		sound.MainSoundPlay();

		//�v���C���[�������ƏՓ˂����珈��
		//�t�F�[�h�A�E�g���J�n���A�Q�[���I�[�o�[��ʂ֑J�ڂ���
		if (player.GetAliveFlag() == false)
		{
			FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_OUT_CHANGENUM));

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[����J��
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.MainSoundStop();
				mSceneChanger->ChangeScene(STATE_GAMEOVER);
			}
		}

		if (player.GetOllBreakFlag() == true && player.GetAliveFlag() == true)
		{
			FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED * FADE_OUT_CHANGENUM));

			//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[����J��
			if (FadeSprite.GetAlpha() == FADE_OUT_END)
			{
				sound.MainSoundStop();
				mSceneChanger->ChangeScene(STATE_RESULT);
			}
		}

		//�X�^�[�g�̃e�N�X�`������ʊO�Ɉړ�
		if (StartTexPosX != SCREEN_OUT)
		{
			StartTexPosX -= STARTTEX_MOVE;
		}

		break;
	}

	
}