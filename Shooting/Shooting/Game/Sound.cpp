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
	//�^�C�g���̉��֌W
	TitleMusic.Load("Sound/title.wav");
	sb_TitleMusic.Create(TitleMusic);

	//���C���Q�[���̉��֌W
	MainMusic.Load("Sound/main.wav");
	sb_MainMusic.Create(MainMusic);

	//�Q�[���N���A��ʂ̉��֌W
	ClearMusic.Load("Sound/gameclear.wav");
	sb_ClearMusic.Create(ClearMusic);

	//�Q�[���I�[�o�[��ʂ̉��֌W
	GameOverMusic.Load("Sound/gameover.wav");
	sb_GameOverMusic.Create(GameOverMusic);
}

void Sound::Update()
{

}

//�^�C�g���̉��y�𗬂��֐�
void Sound::TitleSoundPlay()
{
	sb_TitleMusic.Play(true);
}

//�^�C�g���̉��y���~�߂�֐�
void Sound::TitleSoundStop()
{
	sb_TitleMusic.Stop();
}

//���C���Q�[���̉��y�𗬂��֐�
void Sound::MainSoundPlay()
{
	sb_MainMusic.Play(true);
}

//���C���Q�[���̉��y���~�߂�֐�
void Sound::MainSoundStop()
{
	sb_MainMusic.Stop();
}

//���U���g��ʂ̉��y�𗬂��֐�
void Sound::ClearSoundPlay()
{
	sb_ClearMusic.Play(true);
}

//���U���g��ʂ̉��y���~�߂�֐�
void Sound::ClearSoundStop()
{
	sb_ClearMusic.Stop();
}

//�Q�[���I�[�o�[��ʂ̉��y�𗬂��֐�
void Sound::GameOverSoundPlay()
{
	sb_GameOverMusic.Play(true);
}

//�Q�[���I�[�o�[��ʂ̉��y���~�߂�֐�
void Sound::GameOverSoundStop()
{
	sb_GameOverMusic.Stop();
}