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

class GameState
{
private:

	Mesh Player;

	Camera camera;

	//���b�V���ɓn���s����쐬
	D3DXMATRIXA16 mat_transform, mat_scale, mat_rotate;

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