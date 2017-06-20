#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "../Global.h"
#include "Sound.h"
#include "SoundEffect.h"


//��Փx
enum DIFFICULTY
{
	EASY,
	NORMAL,
	HARD,
};

//�^�C�g���̃t���[
enum TITLESTATE
{
	START,
	BUTTONMOVE,
	SELECT,
};

extern DIFFICULTY dif;

class Title : public BaseScene
{
private:

	//�^�C�g���̃e�N�X�`��
	Texture TitleTex;
	Sprite TitleSprite;

	//�G���^�[�L�[�������Ă��炤�w���̃e�N�X�`��
	Texture EnterTex;
	Sprite EnterSprite;

	//��Փx�I��p�̃e�N�X�`���iEasy�j
	Texture EasyTex;
	Sprite EasySptite;

	//��Փx�I��p�̃e�N�X�`���iNormal�j
	Texture NormalTex;
	Sprite NormalSptite;

	//��Փx�I��p�̃e�N�X�`���iHard�j
	Texture HardTex;
	Sprite HardSptite;


	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	Texture FadeTex;
	Sprite FadeSprite;

	//�t�F�[�h�A�E�g�����s���邩�̃t���O
	//�X�y�[�X�L�[���������Ȃ�true�ɂ���
	bool FadeFlag;

	//�G���^�[�L�[�̑���𑣂��t�H���g��_�ł����邽�߂̕ϐ�
	int EnterDrawCount;
	int EnterFlashingNum;

	int ButtonMoveNum[3];


	Sound sound;
	SoundEffect se;

	DIFFICULTY difficulty;
	TITLESTATE titleState;

	DIFFICULTY difficultySelect[3];
	bool ButtonMoveFlag;

public:
	//�R���X�g���N�^
	Title::Title(ISceneChanger* changer);
	//�f�X�g���N�^
	~Title();

	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;

	void DifficultySelect(DIFFICULTY dif1, DIFFICULTY dif2);

};