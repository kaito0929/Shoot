#pragma once

//�t�F�[�h�C���A�t�F�[�h�A�E�g�֌W
//�t�F�[�h�A�E�g�p�̐��l
#define FADE_OUT_CHANGENUM 1 
#define FADE_OUT_END 1
//�t�F�[�h�C���p�̐��l
#define FADE_IN_CHANGENUM -1 
#define FADE_IN_END 0

//�t�F�[�h�C���A�A�E�g�̃X�s�[�h
#define FADE_SPEED 0.01f


//��ʂ�x���ł̒����̐��l
#define SCREEN_CENTERX 600
//��ʊO
#define SCREEN_OUT -120

//�X�^�[�g�̕����𓮂������l
#define STARTTEX_MOVE 25
//�v���C���[�̑��삪�\�ɂȂ�܂ł̃C���^�[�o��
#define START_COUNT_MAX 10

//�e�N�X�`����_�ł�����֌W
#define TEXTURE_DARW_SPEED 30
#define TEXTURE_DARW_TIMING 0


//���C����ʂ̃t���[
enum PLAYSTATE
{
	FADE_IN,
	START_SIGNAL,
	MAIN,
};