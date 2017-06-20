#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Hard.h"

Hard::Hard(ISceneChanger* changer) : BaseScene(changer)
{

}

Hard::~Hard()
{

}

//�������֐�
void Hard::Initialize()
{
	player.Initialize();
	player.HardInitialize();
	sound.Initialize();

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

}

//�`��֐�
void Hard::Draw()
{
	player.Draw();
	player.HardDraw();

	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

void Hard::Update()
{
	player.Update();
	player.HardUpdate();
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
}