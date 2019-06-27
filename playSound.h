#ifndef PLAY_SOUND_H
#define PLAY_SOUND_H

// �ʱ� ȭ�� ������ ���� sound�� �񵿱��� + �ݺ� ����ϴ� �Լ�
void playSound_startupScreen_repeatMainMusicPlayback();

// Game Start ȿ������ ����ϴ� �Լ�
void playSound_GameStartSoundEffect();

// Game Over ȿ������ ����ϴ� �Լ�
void playSound_GameOverSoundEffect();

// �������� ���ư� �� ���� sound�� �񵿱��� + �ݺ� ����ϴ� �Լ�
void playSound_returnMain_repeatMainMusicPlayback();

// Sorry �˾�â ��� �� Fail ȿ������ ����ϴ� �Լ�
void playSound_FailSoundEffect();

// Clear Game ȿ������ ����ϴ� �Լ�
void playSound_ClearSoundEffect();

// ���� ���� ����� ���ߴ� �Լ�
void playSound_Stop();

#endif