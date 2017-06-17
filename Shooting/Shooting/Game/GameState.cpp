#include "GameState.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()関数用
#include <time.h>	//time()関数用

GameState::GameState(ISceneChanger* changer) : BaseScene(changer)
{
	
}

GameState::~GameState()
{

}
//初期化関数
void GameState::Initialize()
{
	player.Initialize();
}
//描画関数
void GameState::Draw()
{
	player.Draw();
}

//メインの動作
void GameState::Update()
{
	player.Update();
}