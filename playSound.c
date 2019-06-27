#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "playSound.h"

// �ʱ� ȭ�� ������ ���� sound�� �񵿱��� + �ݺ� ����ϴ� �Լ�
void playSound_startupScreen_repeatMainMusicPlayback() 
{
	PlaySound(TEXT("ShawnWasabi_MarbleSoda.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Game Start ȿ������ ����ϴ� �Լ�
void playSound_GameStartSoundEffect() 
{
	PlaySound(TEXT("GameStart"), NULL, SND_ASYNC);
}

// Game Over ȿ������ ����ϴ� �Լ�
void playSound_GameOverSoundEffect() 
{
	PlaySound(TEXT("GameOver"), NULL, SND_ASYNC);
}

// �������� ���ư� �� ���� sound�� �񵿱��� + �ݺ� ����ϴ� �Լ�
void playSound_returnMain_repeatMainMusicPlayback() 
{
	PlaySound(TEXT("ReturnMain.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Sorry �˾�â ��� �� Fail ȿ������ ����ϴ� �Լ�
void playSound_FailSoundEffect() 
{
	PlaySound(TEXT("Fail.wav"), NULL, SND_ASYNC);
}

// Clear Game ȿ������ ����ϴ� �Լ�
void playSound_ClearSoundEffect()
{
	PlaySound(TEXT("Victorious.wav"), NULL, SND_ASYNC);
}

// ���� ���� ����� ���ߴ� �Լ�
void playSound_Stop() 
{
	PlaySound(NULL, 0, 0);
}