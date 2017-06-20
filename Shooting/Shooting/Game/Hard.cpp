#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Hard.h"

Hard::Hard(ISceneChanger* changer) : BaseScene(changer)
{

}

Hard::~Hard()
{

}

//‰Šú‰»ŠÖ”
void Hard::Initialize()
{
	player.Initialize();
	player.HardInitialize();
	sound.Initialize();
}

//•`‰æŠÖ”
void Hard::Draw()
{
	player.Draw();
	player.HardDraw();
}

void Hard::Update()
{
	player.Update();
	player.HardUpdate();
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