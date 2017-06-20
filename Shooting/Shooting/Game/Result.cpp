#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

#include "Result.h"

Result::Result(ISceneChanger* changer) : BaseScene(changer)
{

}

Result::~Result()
{

}

void Result::Initialize()
{
	//���U���g��ʂ̃e�N�X�`��
	ResultTex.Load("Material/result.png");
	ResultSprite.SetPos(600, 450);
	ResultSprite.SetSize(1200, 1000);

	//�X�y�[�X�L�[�������悤�Ɏw������e�N�X�`��
	EnterTex.Load("Material/pushspace.png");
	EnterSprite.SetPos(600, 700);
	EnterSprite.SetSize(600, 400);

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	FadeTex.Load("Material/fade_b.png");
	FadeSprite.SetPos(600, 500);
	FadeSprite.SetSize(1200, 1100);
	FadeSprite.SetAlpha(0);

	sound.Initialize();
	se.Initialize();
}

void Result::Draw()
{
	Direct3D::SetRenderState(RENDER_ALPHABLEND);

	Direct3D::DrawSprite(ResultSprite, ResultTex);

	if (EnterFlashingNum == 0)
	{
		//�G���^�[�L�[�������悤�Ɏw��
		Direct3D::DrawSprite(EnterSprite, EnterTex);
	}

	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

void Result::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.ClearSoundPlay();

	//==���G���^�[�L�[�������悤�Ɏw�����o���e�N�X�`����_�ł����遡====================================
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
	//==================================================================================================

	//�G���^�[�L�[���������Ȃ�t���O��true�ɂ��ăt�F�[�h�A�E�g�J�n
	if (pDi->KeyJustPressed(DIK_RETURN))
	{
		if (FadeFlag == false)
		{
			se.DecisionSEPlay();
		}
		FadeFlag = true;
	}

	//FadeFlag��true�Ȃ���s����悤��
	if (FadeFlag == true)
	{
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (0.01f*FADE_OUT_CHANGENUM));
	}

	//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
	if (FadeSprite.GetAlpha() == 1)
	{
		sound.ClearSoundStop();
		mSceneChanger->ChangeScene(STATE_TITLE);
	}
}