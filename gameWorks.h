#ifndef GAME_WORKS_H
#define GAME_WORKS_H

#include "startupScreen.h"
#include "setBoard.h"
typedef enum { FIVE = 0, TEN, FIFTEEN, TWENTY, GOBACK } ChoiceLevel;

// ��ŷ ������ �����ϱ� ���� ����ü�� �����Ѵ�
typedef struct
{
	char name[50];    // ���̵�
	int timeStorage;  // Ŭ���� �ϴµ� �ɸ� �ð�
}Rank;

// ���� �޴��� ����ϴ� �Լ�
int gameWorks_showStartMenu();

// ���̵��� �����ϴ� �Լ�
int gameWorks_selectDifficultyLevel();

// no ������ ����ϴ� �Լ�
void gameWorks_showLevel(int level);

// ������ ����ϴ� �Լ�
void gameWorks_showGrades(Level(*data)[9], int level);

// ���� ��ȣ�� �����ϴ� �Լ�
int gameWorks_selectGame(int level);

// �˾�â Ʋ(���)�� ����ϴ� �Լ�
void gameWorks_printPopupBackground();

// "������ �������Դϴ�." �˸� â�� ����ϴ� �Լ�
void gameWorks_noFileAlertPopup();

// ���� ���� �߿� ESC�� ������ �� �˾�â�� ����ϴ� �Լ�
int gameWorks_showPopup(Level(*data)[9], int level, int no);

// Ŭ���� ȭ���� ����ϴ� �Լ� 
void gameWorks_showClearPopup(Level(*data)[9], int level, int no);

// ������ �����ϴ� �Լ� 
int gameWorks_playGame(Level(*data)[9], int level, int no);

// ��ü ������ �Ѱ��ϴ� �Լ�
void gameWorks(Level(*data)[9], Title *logo);

#endif