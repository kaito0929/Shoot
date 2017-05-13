#pragma once

#include "../mesh.h"
#include "../Direct3D.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "../camera.h"

#include "../Scene/SceneManager.h"
#include "../Scene/ISceneChanger.h"
#include "../Scene/BaseScene.h"

#include "Player.h"

class GameState
{
private:

	Player player;

public:
	//�R���X�g���N�^
	GameState();
	//�f�X�g���N�^
	~GameState();			

	//������
	void Initialize();
	//���ۂ̓���
	void Update();
	//�`��
	void Draw();

	
};