#include "../directInput.h"
#include "../Xinput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../mesh.h"
#include "../Direct3D.h"

#include "Normal.h"

Normal::Normal(ISceneChanger* changer) : BaseScene(changer)
{

}

Normal::~Normal()
{

}

//‰Šú‰»ŠÖ”
void Normal::Initialize()
{
	player.Initialize();
	player.NormalInitialize();
	sound.Initialize();
}

//•`‰æŠÖ”
void Normal::Draw()
{
	player.Draw();
	player.NormalDraw();
}

void Normal::Update()
{
	player.Update();
	player.NormalUpdate();
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