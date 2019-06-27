#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "playSound.h"

// 초기 화면 구동시 메인 sound를 비동기적 + 반복 재생하는 함수
void playSound_startupScreen_repeatMainMusicPlayback() 
{
	PlaySound(TEXT("ShawnWasabi_MarbleSoda.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Game Start 효과음을 재생하는 함수
void playSound_GameStartSoundEffect() 
{
	PlaySound(TEXT("GameStart"), NULL, SND_ASYNC);
}

// Game Over 효과음을 재생하는 함수
void playSound_GameOverSoundEffect() 
{
	PlaySound(TEXT("GameOver"), NULL, SND_ASYNC);
}

// 메인으로 돌아갈 때 메인 sound를 비동기적 + 반복 재생하는 함수
void playSound_returnMain_repeatMainMusicPlayback() 
{
	PlaySound(TEXT("ReturnMain.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Sorry 팝업창 출력 시 Fail 효과음을 재생하는 함수
void playSound_FailSoundEffect() 
{
	PlaySound(TEXT("Fail.wav"), NULL, SND_ASYNC);
}

// Clear Game 효과음을 재생하는 함수
void playSound_ClearSoundEffect()
{
	PlaySound(TEXT("Victorious.wav"), NULL, SND_ASYNC);
}

// 음악 파일 재생을 멈추는 함수
void playSound_Stop() 
{
	PlaySound(NULL, 0, 0);
}