#include "GameState.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()�֐��p
#include <time.h>	//time()�֐��p

GameState::GameState()
{
	
}

GameState::~GameState()
{

}
//�������֐�
void GameState::Initialize()
{
	//stage.Initialize();
	player.Initialize();
}
//�`��֐�
void GameState::Draw()
{
	//stage.Draw();
	player.Draw();
}

//���C���̓���
void GameState::Update()
{
	//stage.Update();
	player.Update();
}