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


#define BUTTON_MOVE_SPEED 20
#define DIFFICULTY_NUM 3

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

	//����𑣂��t�H���g��_�ł����邽�߂̕ϐ�
	int DrawCount;
	bool DrawFlag;

	//�{�^����x���W
	int ButtonMoveNum[DIFFICULTY_NUM];
	//�{�^���ړ��J�n�̃t���O
	bool ButtonMoveFlag;

	//�I�����Ă����Փx
	DIFFICULTY difficulty;
	//�^�C�g����ʂł̃t���[
	TITLESTATE titleState;

	//����p�̕ϐ�
	DIFFICULTY difficultySelect[DIFFICULTY_NUM];

	Sound sound;
	SoundEffect se;

	//�{�^���̃T�C�Y�̕W��
	int ButtonSizeStandardX;
	int ButtonSizeStandardY;
	//�{�^���̃T�C�Y�̍ő�l
	int ButtonSizeMaxX;
	int ButtonSizeMaxY;

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

	void PushKeyDraw();

};