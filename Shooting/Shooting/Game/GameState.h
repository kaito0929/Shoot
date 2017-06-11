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
#include "Stage.h"

class GameState
{
private:

	Player player;

	Stage stage;

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