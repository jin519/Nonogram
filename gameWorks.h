#ifndef GAME_WORKS_H
#define GAME_WORKS_H

#include "startupScreen.h"
#include "setBoard.h"
typedef enum { FIVE = 0, TEN, FIFTEEN, TWENTY, GOBACK } ChoiceLevel;

// 랭킹 정보를 저장하기 위해 구조체를 선언한다
typedef struct
{
	char name[50];    // 아이디
	int timeStorage;  // 클리어 하는데 걸린 시간
}Rank;

// 시작 메뉴를 출력하는 함수
int gameWorks_showStartMenu();

// 난이도를 선택하는 함수
int gameWorks_selectDifficultyLevel();

// no 정보를 출력하는 함수
void gameWorks_showLevel(int level);

// 평점을 출력하는 함수
void gameWorks_showGrades(Level(*data)[9], int level);

// 게임 번호를 선택하는 함수
int gameWorks_selectGame(int level);

// 팝업창 틀(배경)을 출력하는 함수
void gameWorks_printPopupBackground();

// "게임을 제작중입니다." 알림 창을 출력하는 함수
void gameWorks_noFileAlertPopup();

// 게임 진행 중에 ESC를 눌렀을 때 팝업창을 출력하는 함수
int gameWorks_showPopup(Level(*data)[9], int level, int no);

// 클리어 화면을 출력하는 함수 
void gameWorks_showClearPopup(Level(*data)[9], int level, int no);

// 게임을 진행하는 함수 
int gameWorks_playGame(Level(*data)[9], int level, int no);

// 전체 게임을 총괄하는 함수
void gameWorks(Level(*data)[9], Title *logo);

#endif