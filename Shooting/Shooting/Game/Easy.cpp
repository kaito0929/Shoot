#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Easy.h"

Easy::Easy(ISceneChanger* changer) : BaseScene(changer)
{

}

Easy::~Easy()
{

}

//‰Šú‰»ŠÖ”
void Easy::Initialize()
{
	player.Initialize();
	player.EasyInitialize();
	sound.Initialize();
}

//•`‰æŠÖ”
void Easy::Draw()
{
	player.Draw();
	player.EasyDraw();
}

void Easy::Update()
{
	player.Update();
	player.EasyUpdate();
	sound.MainSoundPlay();

	if (player.GetAliveFlag() == false)
	{
		mSceneChanger->ChangeScene(STATE_GAMEOVER);
		sound.MainSoundStop();
	}

	if (player.GetOllBreakFlag() == true)
	{
		mSceneChanger->ChangeScene(STATE_RESULT);
		sound.MainSoundStop();
	}
}