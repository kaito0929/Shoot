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
#include "../Global.h"

class Easy : public BaseScene
{
private:

	Player player;
	Sound sound;

	//�t�F�[�h�A�E�g�p�̃e�N�X�`��
	Texture FadeTex;
	Sprite FadeSprite;

public:

	//�R���X�g���N�^
	Easy::Easy(ISceneChanger* changer);

	//�f�X�g���N�^
	~Easy();


	//������
	void Initialize() override;
	//���ۂ̓���
	void Update() override;
	//�`��
	void Draw() override;


};