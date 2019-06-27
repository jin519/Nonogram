#ifndef PLAY_SOUND_H
#define PLAY_SOUND_H

// 초기 화면 구동시 메인 sound를 비동기적 + 반복 재생하는 함수
void playSound_startupScreen_repeatMainMusicPlayback();

// Game Start 효과음을 재생하는 함수
void playSound_GameStartSoundEffect();

// Game Over 효과음을 재생하는 함수
void playSound_GameOverSoundEffect();

// 메인으로 돌아갈 때 메인 sound를 비동기적 + 반복 재생하는 함수
void playSound_returnMain_repeatMainMusicPlayback();

// Sorry 팝업창 출력 시 Fail 효과음을 재생하는 함수
void playSound_FailSoundEffect();

// Clear Game 효과음을 재생하는 함수
void playSound_ClearSoundEffect();

// 음악 파일 재생을 멈추는 함수
void playSound_Stop();

#endif