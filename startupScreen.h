#ifndef START_UP_SCREEN_H
#define START_UP_SCREEN_H

typedef struct
{
	int **ansData;      // 수치화된 정답 데이터
	int **upkeys;       // upkeys 
	int **sidekeys;     // sidekeys
	int upRowSize;      // upkeys의 전체 행 개수
	int sideColSize;    // sidekeys의 전체 열 개수 
}Title;

// 파일로부터 타이틀 데이터를 가져오는 함수 
void startupScreen_importTitleDataFromFile(Title *data);

// upkeys 출력
void startupScreen_printUpkeys(Title *data, char(*changeIntegerToStr)[3]);

// sidekeys 출력
void startupScreen_printSidekeys(Title *data, char(*changeIntegerToStr)[3]);

// 움직이는 타이틀 출력
void startupScreen_showMovingTitle(Title *data);

// X 표시를 제거한 정답 출력
void startupScreen_showCompleteAns(Title *data);

// 게임 시작 메세지 출력
void startupScreen_showStartMsg();

// 초기 화면
void startupScreen(Title *data);

// 로고 출력
void startupScreen_showTitle(Title *data);

#endif