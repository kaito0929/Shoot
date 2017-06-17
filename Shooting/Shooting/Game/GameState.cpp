#include "GameState.h"
#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"
#include <stdio.h>
#include <stdlib.h>	//rand()ŠÖ”—p
#include <time.h>	//time()ŠÖ”—p

GameState::GameState(ISceneChanger* changer) : BaseScene(changer)
{
	
}

GameState::~GameState()
{

}
//‰Šú‰»ŠÖ”
void GameState::Initialize()
{
	player.Initialize();
}
//•`‰æŠÖ”
void GameState::Draw()
{
	player.Draw();
}

//ƒƒCƒ“‚Ì“®ì
void GameState::Update()
{
	player.Update();
}