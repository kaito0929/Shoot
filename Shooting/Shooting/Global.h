#pragma once

//フェードイン、フェードアウト関係
//フェードアウト用の数値
#define FADE_OUT_CHANGENUM 1 
#define FADE_OUT_END 1
//フェードイン用の数値
#define FADE_IN_CHANGENUM -1 
#define FADE_IN_END 0

//フェードイン、アウトのスピード
#define FADE_SPEED 0.01f


//画面のx軸での中央の数値
#define SCREEN_CENTERX 600
//画面外
#define SCREEN_OUT -120

//スタートの文字を動かす数値
#define STARTTEX_MOVE 25
//プレイヤーの操作が可能になるまでのインターバル
#define START_COUNT_MAX 10

//テクスチャを点滅させる関係
#define TEXTURE_DARW_SPEED 30
#define TEXTURE_DARW_TIMING 0


//メイン画面のフロー
enum PLAYSTATE
{
	FADE_IN,
	START_SIGNAL,
	MAIN,
};