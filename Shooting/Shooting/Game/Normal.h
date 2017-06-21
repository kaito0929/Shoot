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

#include "Player.h"
#include "Sound.h"
#include "Easy.h"
#include "../Global.h"

class Normal : public BaseScene
{
private:

	Player player;
	Sound sound;
	SoundEffect se;

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	Texture FadeTex;
	Sprite FadeSprite;

	//�Q�[���J�n�̍��}���s���e�N�X�`��
	Texture StartTex;
	Sprite StartSprite;

	//�X�^�[�g�̃e�N�X�`����x���W
	int StartTexPosX;
	//�X�^�[�g�̍��}�����Ă���̃C���^�[�o��
	int StartCount;

	PLAYSTATE playState;


public:

	//�R���X�g���N�^
	Normal::Normal(ISceneChanger* changer);

	//�f�X�g���N�^
	~Normal();


	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;


};