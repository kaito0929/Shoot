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
}

//�`��֐�
void Normal::Draw()
{
	player.Draw();
	player.NormalDraw();
}

void Normal::Update()
{
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
}