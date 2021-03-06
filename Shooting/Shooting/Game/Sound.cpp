#include "../directInput.h"
#include "../Texture.h"
#include "../Sprite.h"
#include "../Direct3D.h"
#include "../Wave.h"
#include "../DirectSound.h"
#include "../SoundBuffer.h"
#include "Sound.h"

Sound::Sound()
{

}

Sound::~Sound()
{

}

void Sound::Initialize()
{
	//タイトルの音関係
	TitleMusic.Load("Sound/title.wav");
	sb_TitleMusic.Create(TitleMusic);

	//メインゲームの音関係
	MainMusic.Load("Sound/main.wav");
	sb_MainMusic.Create(MainMusic);

	//ゲームクリア画面の音関係
	ClearMusic.Load("Sound/gameclear.wav");
	sb_ClearMusic.Create(ClearMusic);

	//ゲームオーバー画面の音関係
	GameOverMusic.Load("Sound/gameover.wav");
	sb_GameOverMusic.Create(GameOverMusic);
}

void Sound::Update()
{

}

//タイトルの音楽を流す関数
void Sound::TitleSoundPlay()
{
	sb_TitleMusic.Play(true);
}

//タイトルの音楽を止める関数
void Sound::TitleSoundStop()
{
	sb_TitleMusic.Stop();
}

//メインゲームの音楽を流す関数
void Sound::MainSoundPlay()
{
	sb_MainMusic.Play(true);
}

//メインゲームの音楽を止める関数
void Sound::MainSoundStop()
{
	sb_MainMusic.Stop();
}

//リザルト画面の音楽を流す関数
void Sound::ClearSoundPlay()
{
	sb_ClearMusic.Play(true);
}

//リザルト画面の音楽を止める関数
void Sound::ClearSoundStop()
{
	sb_ClearMusic.Stop();
}

//ゲームオーバー画面の音楽を流す関数
void Sound::GameOverSoundPlay()
{
	sb_GameOverMusic.Play(true);
}

//ゲームオーバー画面の音楽を止める関数
void Sound::GameOverSoundStop()
{
	sb_GameOverMusic.Stop();
}