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

float x = 0.0f;
float y = 0.0f;


GameState::GameState()
{
	
}

GameState::~GameState()
{

}
//�������֐�
void GameState::Initialize()
{
	player.Initialize();
}
//�`��֐�
void GameState::Draw()
{
	player.Draw();
}
//���C���̓���
void GameState::Update()
{
	player.Update();
}