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
	EnterSprite.SetSize(650, 450);

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

	if (DrawFlag == true)
	{
		//�X�y�[�X�L�[�������悤�Ɏw��
		Direct3D::DrawSprite(EnterSprite, EnterTex);
	}

	//�t�F�[�h�A�E�g�p�̉摜��`��
	Direct3D::DrawSprite(FadeSprite, FadeTex);

}

void Result::Update()
{
	DirectInput* pDi = DirectInput::GetInstance();

	sound.ClearSoundPlay();

	//�G���^�[�L�[���������Ȃ�t���O��true�ɂ��ăt�F�[�h�A�E�g�J�n
	if (pDi->KeyJustPressed(DIK_SPACE))
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
		FadeSprite.SetAlpha(FadeSprite.GetAlpha() + (FADE_SPEED*FADE_OUT_CHANGENUM));
	}

	//���S�ɉ�ʂ��Â��Ȃ����Ȃ�V�[�������C���Q�[���ɕύX
	if (FadeSprite.GetAlpha() == FADE_OUT_END)
	{
		sound.ClearSoundStop();
		mSceneChanger->ChangeScene(STATE_TITLE);
	}

	TextureFlashing();
}

void Result::TextureFlashing()
{
	//�J�E���g���v���X
	DrawCount++;

	//�t���O��true,false��؂�ւ��邱�Ƃɂ����
	//�e�N�X�`���̕\����\����؂�ւ���
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