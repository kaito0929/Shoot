#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"
#include "../BoundingBox.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Sound.h"
#include "SoundEffect.h"

#include "Title.h"
#include "../Global.h"


#define BUTTON_DRAW_SPEED 30
#define BUTTON_DRAW_TIMING 0


enum GAMEOVERSTATE
{
	FADE,
	RETRY,
	TITLEGO,
};

class GameOver : public BaseScene
{
private:

	//�Q�[���I�[�o�[��ʂ̃e�N�X�`��
	Texture GameOverTex;
	Sprite GameOverSprite;

	//���g���C�̃e�N�X�`��
	Texture RetryTex;
	Sprite RetrySptite;

	//�^�C�g���ւ̃e�N�X�`��
	Texture TitleGoTex;
	Sprite TitleGoSprite;

	//�t�F�[�h�C���A�A�E�g�p�̃e�N�X�`��
	Texture FadeTex;
	Sprite FadeSprite;

	GAMEOVERSTATE gameoverState;

	int ButtonDrawCount;
	bool ButtonDrawFlag;

	//�t�F�[�h�A�E�g�����s���邩�̃t���O
	//�X�y�[�X�L�[���������Ȃ�true�ɂ���
	bool FadeFlag;


	Sound sound;
	SoundEffect se;

public:

	//�R���X�g���N�^
	GameOver::GameOver(ISceneChanger* changer);

	//�f�X�g���N�^
	~GameOver();

	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;

	void ButtonDrawSet();

};