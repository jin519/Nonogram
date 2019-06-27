#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include "consoleFunc.h"
#include "gameWorks.h"
#include "ansGenerator.h"
#include "tutorial.h"
#include "playSound.h"

typedef enum { MEMBERSHIP = 0, GUEST, TUTORIAL, EDITOR, QUIT } FirstMenu;
typedef enum { DEL = 0, GENERATE, BACK } GeneratorMenu;
typedef enum { RETURNGAME = 0, GENERATEANS, BACKTOMAIN } PopupMenu;
typedef enum { CLEAR = -2, GAMEOVER } PlayingGame;

extern char numberInString[9][5][11];
extern char changeIntegerToStr[10][3];

char *rankFile[4][9] = { { "rank_5_1.txt", "rank_5_2.txt", "rank_5_3.txt", "rank_5_4.txt", "rank_5_5.txt", "rank_5_6.txt", "rank_5_7.txt", "rank_5_8.txt", "rank_5_9.txt" },
						 { "rank_10_1.txt", "rank_10_2.txt", "rank_10_3.txt", "rank_10_4.txt", "rank_10_5.txt", "rank_10_6.txt", "rank_10_7.txt", "rank_10_8.txt", "rank_10_9.txt" },
						 { "rank_15_1.txt", "rank_15_2.txt", "rank_15_3.txt", "rank_15_4.txt", "rank_15_5.txt", "rank_15_6.txt", "rank_15_7.txt", "rank_15_8.txt", "rank_15_9.txt" },
						 { "rank_20_1.txt", "rank_20_2.txt", "rank_20_3.txt", "rank_20_4.txt", "rank_20_5.txt", "rank_20_6.txt", "rank_20_7.txt", "rank_20_8.txt", "rank_20_9.txt" } };

char grade[4][7] = { "☆☆☆", "★☆☆", "★★☆", "★★★" };

// 버블 정렬
void gameWorks_bubbleSort(Rank *arr, int cnt)
{
	int repeat = 0, i = 0;
	Rank tmp = { 0 };

	for (repeat = 0; repeat < cnt - 1; repeat++) { for (i = 0; i < cnt - 1 - repeat; i++) {
		if (arr[i].timeStorage > arr[i + 1].timeStorage)
		{
			tmp = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = tmp;
	}}}
}

// 시작 메뉴를 출력하는 함수
int gameWorks_showStartMenu()
{
	char *arr[5] = { "    Member mode    ", 
		             "    Guest mode     ",
		             "    Tutorial       ", 
		             "    Edit Answer    ",
		             "    Quit           " };
	char ch = '\0';
	int i = 0, j = 0;

	gotoxy(86, 20);
	setColor(WHITE, RED);
	fprintf(stdout, "%s", arr[i]);
	setColor(WHITE, BLACK);
	for (j = 1; j < 5; j++)
	{
		gotoxy(86, 20 + 2 * j);
		fprintf(stdout, "%s", arr[j]);
	}

	while (1)
	{
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출

		switch (ch)
		{
		case 0x48: gotoxy(86, 20 + 2 * i);  // 상방향 키
			setColor(WHITE, BLACK);
			fprintf(stdout, "%s", arr[i]);
			i--; break;
		case 0x50: gotoxy(86, 20 + 2 * i);  // 하방향 키
			setColor(WHITE, BLACK);
			fprintf(stdout, "%s", arr[i]);
			i++;
		}

		if (i < 0) i = 4;
		else if (i > 4) i = 0;

		gotoxy(86, 20 + 2 * i);
		setColor(WHITE, RED);
		fprintf(stdout, "%s", arr[i]);
	}

	// 화면 글자 지우기
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 20 + 2 * j);
		fputs("                    ", stdout);
	}

	return i;
}

// 난이도를 선택하는 함수
int gameWorks_selectDifficultyLevel()
{
	char *arr[5] = { "       5 * 5       ", "      10 * 10      ",
		             "      15 * 15      ", "      20 * 20      ", 
		             "      Go Back      " };
	char ch = '\0';
	int i = 0, j = 0;

	gotoxy(86, 21);
	setColor(WHITE, RED);
	fprintf(stdout, "%s", arr[i]);
	setColor(WHITE, BLACK);
	for (j = 1; j < 5; j++)
	{
		gotoxy(86, 21 + 2 * j);
		fprintf(stdout, "%s", arr[j]);
	}

	while (1)
	{
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출

		switch (ch)
		{
		case UP: gotoxy(86, 21 + 2 * i);  
			setColor(WHITE, BLACK);
			fprintf(stdout, "%s", arr[i]);
			i--; break;
		case DOWN: gotoxy(86, 21 + 2 * i);  
			setColor(WHITE, BLACK);
			fprintf(stdout, "%s", arr[i]);
			i++;
		}

		if (i < 0) i = 4;
		else if (i > 4) i = 0;

		gotoxy(86, 21 + 2 * i);
		setColor(WHITE, RED);
		fprintf(stdout, "%s", arr[i]);
		setColor(WHITE, BLACK);
	}

	// 화면 글자 지우기
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 21 + 2 * j);
		fputs("                   ", stdout);
	}

	return i;
}

// no 정보를 출력하는 함수
void gameWorks_showLevel(int level) 
{
	char no[4][7][71] = { { "                                                                      ",
							"              ■■■■■      ■      ■      ■■■■■              ",
							"              ■                ■  ■        ■                      ",
							"              ■■■■■          ■          ■■■■■              ",
							"                      ■        ■  ■                ■              ",
							"              ■■■■■      ■      ■      ■■■■■              ",
							"                                                                      " },
							{ "                                                                      ",
							"          ■  ■■■■■      ■      ■      ■  ■■■■■          ",
							"          ■  ■      ■        ■  ■        ■  ■      ■          ",
							"          ■  ■      ■          ■          ■  ■      ■          ",
							"          ■  ■      ■        ■  ■        ■  ■      ■          ",
							"          ■  ■■■■■      ■      ■      ■  ■■■■■          ",
							"                                                                      " },
							{ "                                                                      ",
							"          ■  ■■■■■      ■      ■      ■  ■■■■■          ",
							"          ■  ■                ■  ■        ■  ■                  ",
							"          ■  ■■■■■          ■          ■  ■■■■■          ",
							"          ■          ■        ■  ■        ■          ■          ",
							"          ■  ■■■■■      ■      ■      ■  ■■■■■          ",
							"                                                                      " },
							{ "                                                                      ",
							"  ■■■■■  ■■■■■      ■      ■      ■■■■■  ■■■■■  ",
							"          ■  ■      ■        ■  ■                ■  ■      ■  ",
							"  ■■■■■  ■      ■          ■          ■■■■■  ■      ■  ",
							"  ■          ■      ■        ■  ■        ■          ■      ■  ",
							"  ■■■■■  ■■■■■      ■      ■      ■■■■■  ■■■■■  ",
							"                                                                      " } };
	int i = 0;

	setColor(WHITE, BLUE);
	for (i = 0; i < 7; i++)
	{
		gotoxy(21, 5 + i);
		fputs(no[level][i], stdout);
	}
}

// 평점을 출력하는 함수
void gameWorks_showGrades(Level(*data)[9], int level) 
{
	int i = 0, j = 0;

	setColor(WHITE, BLACK);
	for (i = 0; i < 9; i++)
	{
		gotoxy(40 + 13 * (i % 3), 22 + 8 * (i / 3));
		fputs(grade[data[level][i].achievement], stdout);
	}
}

// 게임 번호를 선택하는 함수
int gameWorks_selectGame(int level)
{
	char ch = '\0';
	int i = 0, j = 0, tmp = 0;
	
	gotoxy(21, 3); fputs("ESC", stdout); // ESC 키를 화면에 출력한다
	gameWorks_showLevel(level); // no 정보를 화면에 출력한다

	// button 선택
	setColor(WHITE, RED);
	for (j = 0; j < 5; j++)
	{
		gotoxy(38, 16 + j);
		fputs(numberInString[0][j], stdout);
	}
	setColor(WHITE, BLACK);

	for (i = 1; i < 9; i++)
	{
		for (j = 0; j < 5; j++)
		{
			gotoxy(38 + 13 * (i % 3), 16 + j + 8 * (i / 3));
			fputs(numberInString[i][j], stdout);
		}
	}

	i = 0;
	while (1)
	{
		tmp = i / 3;
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출
		else if (ch == ESC) { return -1; break; } // ESC 입력 시 이전 화면으로 돌아간다
		else if (ch == UP || ch == DOWN || ch == LEFT || ch == RIGHT)
		{
			setColor(WHITE, BLACK);
			for (j = 0; j < 5; j++)
			{
				gotoxy(38 + 13 * (i % 3), 16 + j + 8 * tmp);
				fprintf(stdout, "%s", numberInString[i][j]);
			}
		}

		switch (ch)
		{
		case UP: 
			i -= 3; if (i < 0) i += 9; break;
		case DOWN: 
			i += 3; if (i > 8) i -= 9; break;
		case LEFT: 
			i--; if (i == -1 || (i / 3) < tmp) i += 3; break;
		case RIGHT: 
			i++; if ((i / 3) > tmp) i -= 3;
		}

		setColor(WHITE, RED);
		for (j = 0; j < 5; j++)
		{
			gotoxy(38 + 13 * (i % 3), 16 + j + 8 * (i / 3));
			fputs(numberInString[i][j], stdout);
		}
	}

	// 화면 글자 지우기
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 21 + 2 * j);
		fputs("                   ", stdout);
	}

	return i; // 번호 정보를 리턴한다
}

// 팝업창 틀(배경)을 출력하는 함수
void gameWorks_printPopupBackground()
{
	int row = 0, col = 0;

	setColor(BLACK, WHITE);
	for (row = 0; row < 29; row++)
	{
		gotoxy(24, 7 + row);
		for (col = 0; col < 59; col++)
		{
			if (row < 3) { setColor(BLACK, GRAY); fputs(" ", stdout); setColor(BLACK, WHITE); }
			else fputs(" ", stdout);
		}
	}
	gotoxy(80, 8); fputs("Ｘ", stdout);
}

// "게임을 제작중입니다." 알림 창을 출력하는 함수
void gameWorks_noFileAlertPopup()
{
	int row = 0, col = 0, i = 0;
	int sorry[5][5][3] =
	{ { { 0, 1, 1 },{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{ 1, 1, 0 } },   // s 
	  { { 0, 1, 0 },{ 1, 0, 1 },{ 1, 0, 1 },{ 1, 0, 1 },{ 0, 1, 0 } },   // o
	  { { 1, 1, 0 },{ 1, 0, 1 },{ 1, 1, 0 },{ 1, 0, 1 },{ 1, 0, 1 } },   // r
	  { { 1, 1, 0 },{ 1, 0, 1 },{ 1, 1, 0 },{ 1, 0, 1 },{ 1, 0, 1 } },   // r
	  { { 1, 0, 1 },{ 1, 0, 1 },{ 0, 1, 0 },{ 0, 1, 0 },{ 0, 1, 0 } } }; // y
	char *key = "   ENTER   ", ch = '\0';

	playSound_FailSoundEffect();
	gameWorks_printPopupBackground(); // 배경을 출력한다

	// SORRY 그래픽을 출력한다
	setColor(WHITE, BLACK);
	for (i = 0; i < 5; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		if (sorry[i][row][col] == 1)
		{
			gotoxy(36 + 2 * col + 7 * i, 14 + row);
			fputs("  ", stdout);
	}}}}

	// 오류 메세지를 출력한다
	setColor(BLACK, WHITE);
	gotoxy(40, 22); fputs("The game is being produced.", stdout);
	gotoxy(42, 23); fputs("Please wait for update.", stdout);
	gotoxy(31, 25); fputs("Press Enter to return to the previous screen.", stdout);

	// ENTER 버튼 생성
	setColor(WHITE, BLACK);
	gotoxy(48, 29); fputs("           ", stdout);
	gotoxy(48, 30); fputs(key, stdout);
	gotoxy(48, 31); fputs("           ", stdout);

	while (!_kbhit()); // 아무키나 입력하면 넘어간다
	_getch(); // 버퍼 비우기
}

// 게임 진행 중에 ESC를 눌렀을 때 팝업창을 출력하는 함수
int gameWorks_showPopup(Level(*data)[9], int level, int no)
{
	char *menu[2] = { "     Return To Game    ", "   Back To Main Menu   " };
	int num[10][5][3] = { { { 1, 1, 1 },{ 1, 0, 1 },{ 1, 0, 1 },{ 1, 0, 1 },{ 1, 1, 1 } },  // 0
						  { { 0, 1, 0 },{ 1, 1, 0 },{ 0, 1, 0 },{ 0, 1, 0 },{ 0, 1, 0 } },  // 1
						  { { 1, 1, 1 },{ 0, 0, 1 },{ 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 } },  // 2
						  { { 1, 1, 1 },{ 0, 0, 1 },{ 1, 1, 1 },{ 0, 0, 1 },{ 1, 1, 1 } },  // 3
						  { { 1, 0, 1 },{ 1, 0, 1 },{ 1, 1, 1 },{ 0, 0, 1 },{ 0, 0, 1 } },  // 4
						  { { 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 },{ 0, 0, 1 },{ 1, 1, 1 } },  // 5
						  { { 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 },{ 1, 0, 1 },{ 1, 1, 1 } },  // 6
						  { { 1, 1, 1 },{ 1, 0, 1 },{ 1, 0, 1 },{ 0, 0, 1 },{ 0, 0, 1 } },  // 7
						  { { 1, 1, 1 },{ 1, 0, 1 },{ 1, 1, 1 },{ 1, 0, 1 },{ 1, 1, 1 } },  // 8
						  { { 1, 1, 1 },{ 1, 0, 1 },{ 1, 1, 1 },{ 0, 0, 1 },{ 1, 1, 1 } } };// 9
	int colon[5][3] = { { 0, 0, 0 },{ 0, 1, 0 },{ 0, 0, 0 },{ 0, 1, 0 },{ 0, 0, 0 } };      // :
	char ch = '\0';
	int row = 0, col = 0, i = 0, min = 0, sec = 0;

	gotoxy(51, 6); setColor(WHITE, BLACK); fputs("      ", stdout); // 상단의 남은 시간 알리미를 지운다
	gameWorks_printPopupBackground(); // 창 기본 틀(배경)을 출력한다

	// 남은 시간을 화면에 그래픽으로 표시한다
	gotoxy(47, 13); fputs("Time Remaining", stdout);
	min = ((int)data[level][no].timeStorage / CLOCKS_PER_SEC) / 60;
	sec = ((int)data[level][no].timeStorage / CLOCKS_PER_SEC) % 60;

	for (i = 0; i < 5; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		switch (i)
		{
		case 0: if (num[min / 10][row][col] == 0) setColor(WHITE, WHITE);
				else setColor(WHITE, BLACK); break;
		case 1: if (num[min % 10][row][col] == 0) setColor(WHITE, WHITE);
				else setColor(WHITE, BLACK); break;
		case 2: if (colon[row][col] == 0) setColor(WHITE, WHITE);
				else setColor(WHITE, BLACK); break;
		case 3: if (num[sec / 10][row][col] == 0) setColor(WHITE, WHITE);
				else setColor(WHITE, BLACK); break;
		case 4: if (num[sec % 10][row][col] == 0) setColor(WHITE, WHITE);
				else setColor(WHITE, BLACK);
		}
		gotoxy(36 + 7 * i + 2 * col, 17 + row);
		fputs("  ", stdout);
	}}}

	// 버튼을 출력한다
	setColor(WHITE, BLACK);
	gotoxy(28, 30); fputs("                       ", stdout);
	gotoxy(28, 31); fputs(menu[0], stdout);
	gotoxy(28, 32); fputs("                       ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(56, 30); fputs("                       ", stdout);
	gotoxy(56, 31); fputs(menu[1], stdout);
	gotoxy(56, 32); fputs("                       ", stdout);

	// 옵션 선택
	row = 0; col = 0;
	while (1)
	{
		ch = _getch(); // 키 입력

		if (ch == 13 || ch == ' ') break;  // enter, spacebar 입력 시 반복 탈출
		else if (ch == 0x4b || ch == 0X4d) // 좌방향 혹은 우방향 키 선택 시
		{
			setColor(BLACK, GRAY);
			gotoxy(28 + 28 * col, 30); fputs("                       ", stdout);
			gotoxy(28 + 28 * col, 31); fputs(menu[col], stdout);
			gotoxy(28 + 28 * col, 32); fputs("                       ", stdout);
		}
		switch (ch)
		{
		case 0x4b: col--; break; // 좌방향 키
		case 0X4d: col++;        // 우방향 키
		}

		if (col < 0) col = 1;
		else if (col > 1) col = 0;

		setColor(WHITE, BLACK);
		gotoxy(28 + 28 * col, 30); fputs("                       ", stdout);
		gotoxy(28 + 28 * col, 31); fputs(menu[col], stdout);
		gotoxy(28 + 28 * col, 32); fputs("                       ", stdout);
	}

	if (col == 1) col = 2; // gameWorks.c 파일에 정의한 열거형을 활용하기 위해 값을 수정
	return col;
}

// clear 화면을 출력하는 함수 
void gameWorks_showClearPopup(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	Rank arr[4] = { 0 }; // 랭킹 데이터를 관리할 구조체 배열
	int clear[11][5][3] =
	{ { { 0, 1, 1 },{ 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 },{ 1, 1, 0 } },   // s
	  { { 1, 1, 1 },{ 0, 1, 0 },{ 0, 1, 0 },{ 0, 1, 0 },{ 0, 1, 0 } },   // t
	  { { 0, 1, 0 },{ 1, 0, 1 },{ 1, 1, 1 },{ 1, 0, 1 },{ 1, 0, 1 } },   // a
	  { { 0, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 },{ 1, 0, 1 },{ 0, 1, 1 } },   // g
	  { { 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 } },   // e
	  { { 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 },{ 0, 0, 0 } },
	  { { 0, 1, 0 },{ 1, 0, 1 },{ 1, 0, 0 },{ 1, 0, 1 },{ 0, 1, 0 } },   // c
	  { { 1, 0, 0 },{ 1, 0, 0 },{ 1, 0, 0 },{ 1, 0, 0 },{ 1, 1, 1 } },   // l
	  { { 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 },{ 1, 0, 0 },{ 1, 1, 1 } },   // e
	  { { 0, 1, 0 },{ 1, 0, 1 },{ 1, 1, 1 },{ 1, 0, 1 },{ 1, 0, 1 } },   // a
	  { { 1, 1, 0 },{ 1, 0, 1 },{ 1, 1, 0 },{ 1, 0, 1 },{ 1, 0, 1 } } }; // r
	int min = 0, sec = 0, rd = 0;
	int i = 0, row = 0, col = 0, pictureSize, xPos, background;

	pictureSize = (level + 1) * 5;
	if (level % 2) { xPos = 11; background = 22; } // 10*10, 20*20
	else { xPos = 12, background = 21; } // 5*5, 15*15

	playSound_ClearSoundEffect();

	// 팝업창 틀(배경)을 출력한다
	setColor(BLACK, WHITE);
	for (row = 0; row < 33; row++)
	{
		gotoxy(8, 5 + row);
		for (col = 0; col < 97; col++)
		{
			if (row < 3) { setColor(BLACK, GRAY); fputs(" ", stdout); setColor(BLACK, WHITE); }
			else fputs(" ", stdout);
		}
	}
	gotoxy(102, 6); fputs("Ｘ", stdout);

	// CLEAR 그래픽을 출력한다
	setColor(WHITE, BLACK);
	for (i = 0; i < 11; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		if (clear[i][row][col] == 1) {
			if (i == 3 && row == 2 && col == 1) // G
			{
				gotoxy(19 + 2 * col + 7 * i, 9 + row);
				fputs(" ", stdout);
			}
			else
			{
				gotoxy(18 + 2 * col + 7 * i, 9 + row);
				fputs("  ", stdout);
			}
	}}}}

	// 회색 틀을 출력한다
	setColor(BLACK, GRAY);
	for (row = 0; row < background; row++)
	{
		for (col = 0; col < background; col++)
		{
			gotoxy(xPos + 2 * col, 15 + row);
			fputs("  ", stdout);
			gotoxy(xPos + 47 + 2 * col, 15 + row);
			fputs("  ", stdout);
		}
	}

	// 정답을 출력한다
	for (row = 0; row < pictureSize; row++)
	{
		for (col = 0; col < pictureSize; col++)
		{
			if (data[level][no].ansData[row][col] == 1) setColor(BLACK, BLACK);
			else setColor(WHITE, WHITE);
			gotoxy(xPos + (background - pictureSize) + 2 * col, 15 + (background - pictureSize) / 2 + row);
			fputs("  ", stdout);
		}
	}

	// 소요 시간을 출력한다
	setColor(BLACK, WHITE);
	gotoxy(xPos + 47 + 4, 17);
	fputs("              ", stdout);
	gotoxy(xPos + 47 + 4, 18);
	fputs("  Time Spent  ", stdout);
	gotoxy(xPos + 47 + 4, 19);
	fputs("              ", stdout);

	min = ((int)data[level][no].timeStorage / CLOCKS_PER_SEC) / 60;
	sec = ((int)data[level][no].timeStorage / CLOCKS_PER_SEC) % 60;

	setColor(BLACK, GRAY);
	gotoxy(xPos + 47 + 22, 18); fprintf(stdout, "%02d:%02d", min, sec);

	// 성적을 출력한다
	setColor(BLACK, WHITE);
	gotoxy(xPos + 47 + 4, 21);
	fputs("              ", stdout);
	gotoxy(xPos + 47 + 4, 22);
	fputs("  Your Grade  ", stdout);
	gotoxy(xPos + 47 + 4, 23);
	fputs("              ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(xPos + 47 + 22, 22); fputs(grade[data[level][no].achievement], stdout);

	// 랭킹을 출력한다
	setColor(BLACK, WHITE);
	gotoxy(xPos + 47 + 4, 25);
	fputs("              ", stdout);
	gotoxy(xPos + 47 + 4, 26);
	fputs("     Rank     ", stdout);
	gotoxy(xPos + 47 + 4, 27);
	fputs("              ", stdout);

	for (row = 0; row < 4; row++) { arr[row].timeStorage = INT_MAX; }
	fopen_s(&fp, rankFile[level][no], "rt"); // 해당 번째 라운드의 랭킹 정보를 담고 있는 파일을 읽기 모드로 연다

	i = 0;
	while (1)
	{
		rd = fscanf(fp, "%s %d", arr[i].name, &arr[i].timeStorage);
		if (rd < 2) break;
		i++;
	}

	if (!i) // 파일 안에 내용이 하나도 없다면 
	{
		fclose(fp); // 파일을 닫는다
		fopen_s(&fp, rankFile[level][no], "wt"); // 파일을 쓰기 모드로 다시 연다 
		fprintf(fp, "%s %d\n", "guest", (int)data[level][no].timeStorage); // 현재 데이터를 저장한다
		fclose(fp); // 파일을 닫는다

		// 화면에 랭킹 정보를 출력한다 
		setColor(BLACK, GRAY);
		gotoxy(xPos + 47 + 4, 29);
		fprintf(stdout, "1. %s, %02d:%02d", "guest", min, sec);
	}
	else // 파일 안에 하나 이상의 데이터가 있다면
	{
		fclose(fp); // 파일을 닫는다
		strcpy_s(arr[i].name, 50, "guest");
		arr[i].timeStorage = (int)data[level][no].timeStorage;

		gameWorks_bubbleSort(arr, 4); // 오름차순으로 정렬한 다음

		// 화면에 3등까지 랭킹 정보를 출력한다
		setColor(BLACK, GRAY);
		for (row = 0; row < 3; row++)
		{
			if (arr[row].timeStorage == INT_MAX) break;
			min = (arr[row].timeStorage / CLOCKS_PER_SEC) / 60;
			sec = (arr[row].timeStorage / CLOCKS_PER_SEC) % 60;
			gotoxy(xPos + 51, 29 + 2 * row);
			fprintf(stdout, "%d. %s, %02d:%02d", row + 1, arr[row].name, min, sec);
		}

		fopen_s(&fp, rankFile[level][no], "wt"); // 파일을 쓰기 모드로 다시 연다 
		for (row = 0; row < 3; row++) // 3등까지 데이터를 저장한다
		{
			if (arr[row].timeStorage == INT_MAX) break;
			fprintf(fp, "%s %d\n", arr[row].name, arr[row].timeStorage);
		}
		fclose(fp); // 파일을 닫는다
	}

	while (!_kbhit())
	{
		gotoxy(45, 6);
		setColor(WHITE, GRAY);
		fputs("press any key to continue", stdout);
		Sleep(300);
		setColor(DEEP_WHITE, GRAY);
		gotoxy(45, 6);
		fputs("press any key to continue", stdout);
		Sleep(300);
	}
	_getch();
}

// game over 화면을 출력하는 함수
int gameWorks_showGameOverPopup(Level(*data)[9], int level, int no) 
{
	int arr[9][5][3] =
	{ { { 0, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 1, 0, 1 }, { 0, 1, 1 } },   // g
	  { { 0, 1, 0 }, { 1, 0, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 1 } },   // a
	  { { 1, 0, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 } },   // m
	  { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 } },   // e
	  { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } },
	  { { 0, 1, 0 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 0, 1, 0 } },   // o
	  { { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 1, 0 }, { 0, 1, 0 } },   // v
	  { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 } },   // e
	  { { 1, 1, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 1 } } }; // r 
	int i = 0, row = 0, col = 0;
	char *button[2] = { "   Retry   ", "  Give Up  " };
	char ch = '\0';

	playSound_GameOverSoundEffect();
	gameWorks_printPopupBackground();
	
	// game over 그래픽 출력
	setColor(BLACK, BLACK);
	for (i = 0; i < 9; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		if (arr[i][row][col] == 1)
		{
			if (i >= 5) gotoxy(20 + 2 * col + 7 * i, 14 + row); 
			else if (i == 0 && row == 2 && col == 1) gotoxy(26 + 2 * col + 7 * i, 14 + row);
			else gotoxy(25 + 2 * col + 7 * i, 14 + row); 
			fputs("  ", stdout);
	}}}}

	// 버튼 출력
	setColor(WHITE, BLACK);
	gotoxy(34, 29); fputs("           ", stdout);
	gotoxy(34, 30); fputs(button[0], stdout);
	gotoxy(34, 31); fputs("           ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(62, 29); fputs("           ", stdout);
	gotoxy(62, 30); fputs(button[1], stdout);
	gotoxy(62, 31); fputs("           ", stdout);

	// 옵션 선택
	col = 0;
	while (1)
	{
		ch = _getch(); // 키 입력

		if (ch == 13 || ch == ' ') break;  // enter, spacebar 입력 시 반복 탈출
		else if (ch == 0x4b || ch == 0X4d) // 좌방향 혹은 우방향 키 선택 시
		{
			setColor(BLACK, GRAY);
			gotoxy(34 + 28 * col, 29); fputs("           ", stdout);
			gotoxy(34 + 28 * col, 30); fputs(button[col], stdout);
			gotoxy(34 + 28 * col, 31); fputs("           ", stdout);
		}
		switch (ch)
		{
		case 0x4b: col--; break; // 좌방향 키
		case 0X4d: col++;        // 우방향 키
		}

		if (col < 0) col = 1;
		else if (col > 1) col = 0;

		setColor(WHITE, BLACK);
		gotoxy(34 + 28 * col, 29); fputs("           ", stdout);
		gotoxy(34 + 28 * col, 30); fputs(button[col], stdout);
		gotoxy(34 + 28 * col, 31); fputs("           ", stdout);
	}
	
	if (col == 0) col = GAMEOVER;
	else if (col == 1) col = -2;

	return col;
}

// 게임을 진행하는 함수 
int gameWorks_playGame(Level(*data)[9], int level, int no)
{
	char ch = '\0';
	int row = 0, col = 0, i = 0, j = 0;
	int pictureSize = (level + 1) * 5, cntAnsNum = 0, cntColoringBoxes = 0;
	int min = 0, sec = 0;
	clock_t start, now, duration = 0, oldduration = 0;

	if (data[level][no].timeStorage == 0) // 플레이 시간을 30분으로 제한한다
		data[level][no].timeStorage = 30 * 60 * CLOCKS_PER_SEC; 
	start = clock(); // 기준점이 되는 시간

	while (1)
	{
		// 시간 계산
		now = clock(); // 현재까지 걸린 시간
		duration = (clock_t)(data[level][no].timeStorage - (now - start));

		sec = (int)duration / CLOCKS_PER_SEC;
		min = sec / 60;
		sec %= 60;

		if (oldduration != duration) // 1초 간격으로 화면에 남은 시간 알리미를 출력한다
		{
			gotoxy(51, 6); setColor(WHITE, BLACK);
			printf("%02d:%02d", min, sec);
		}

		// 30분이 경과하기 전에, 정답을 다 맞추면 게임을 종료한다
		if (duration >= 0)
		{
			if (cntColoringBoxes == data[level][no].cntAns && cntAnsNum == data[level][no].cntAns)
			{
				switch (level)
				{
				case FIVE: 
					if ((now - start) <= 2 * 60 * CLOCKS_PER_SEC)        // ★★★ 2분 내로 클리어
						data[level][no].achievement = 3;
					else if ((now - start) <= 5 * 60 * CLOCKS_PER_SEC)   // ★★ 5분 내로 클리어 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // ★ 
					break;
				case TEN: 
					if ((now - start) <= 3.5 * 60 * CLOCKS_PER_SEC)      // ★★★ 3분 30초 내로 클리어
						data[level][no].achievement = 3;
					else if ((now - start) <= 8 * 60 * CLOCKS_PER_SEC)   // ★★ 8분 내로 클리어 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // ★ 
					break;
				case FIFTEEN: 
					if ((now - start) <= 4 * 60 * CLOCKS_PER_SEC)        // ★★★ 4분 내로 클리어
						data[level][no].achievement = 3;
					else if ((now - start) <= 10 * 60 * CLOCKS_PER_SEC)  // ★★ 10분 내로 클리어 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // ★ 
					break;
				case TWENTY: 
					if ((now - start) <= 5.5 * 60 * CLOCKS_PER_SEC)      // ★★★ 5분 30초 내로 클리어
						data[level][no].achievement = 3;
					else if ((now - start) <= 12.5 * 60 * CLOCKS_PER_SEC)// ★★ 12분 30초 내로 클리어 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // ★ 
				}
				data[level][no].timeStorage = (now - start) + 1;
				gameWorks_showClearPopup(data, level, no); // 클리어 화면을 출력한다
				return CLEAR;
			}
		}
		else if (duration < 0) // 30분 내로 정답을 맞추지 못했다면
		{
			// 유저 데이터를 초기화 하고
			for (row = 0; row < pictureSize; row++) 
				for (col = 0; col < pictureSize; col++)
					data[level][no].userData[row][col] = 0;
		
			return gameWorks_showGameOverPopup(data, level, no); // game over 화면을 출력한다
		}

		oldduration = duration; // 시간을 1초에 한번씩 출력하기 위한 작업이다

		// 현재 위치의 배열 요소 값을 해석하여 대응되는 유니코드를 노랑색으로 강조한다
		gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
		setColor(BLACK, BRIGHT_YELLOW);
		ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);

		// 현재 위치와 같은 열에 해당하는 upkey를 노랑색으로 강조한다
		for (i = 0; i < data[level][no].upRowSize; i++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + i);
			if (data[level][no].upkeys[i][col] == 0 && i != data[level][no].upRowSize - 1)
				fprintf(stdout, "%s", "  ");
			else if (data[level][no].upkeys[i][col] >= 0 && data[level][no].upkeys[i][col] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data[level][no].upkeys[i][col]]);
			else
				fprintf(stdout, "%d", data[level][no].upkeys[i][col]);
		}

		// 현재 위치와 같은 행에 해당하는 sidekeys를 노랑색으로 강조한다
		for (i = 0; i < data[level][no].sideColSize; i++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * i, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if (data[level][no].sidekeys[row][i] == 0 && i != data[level][no].sideColSize - 1)
				fprintf(stdout, "%s", "  ");
			else if (data[level][no].sidekeys[row][i] >= 0 && data[level][no].sidekeys[row][i] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data[level][no].sidekeys[row][i]]);
			else fprintf(stdout, "%d", data[level][no].sidekeys[row][i]);
		}
		
		if (_kbhit())
		{
			ch = _getch(); // 키 입력

			if (ch == ESC) // ESC 명령 시
			{
				data[level][no].timeStorage = duration;
				return gameWorks_showPopup(data, level, no);
			}
			else if (ch == 'r' || ch == 'R') // 초기화 명령 시
			{
				// 현재 위치와 같은 열에 해당하는 upkey의 강조를 제거한다
				setColor(BLACK, WHITE);
				for (i = 0; i < data[level][no].upRowSize; i++)
				{
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + i);
					if (data[level][no].upkeys[i][col] == 0 && i != data[level][no].upRowSize - 1)
						fprintf(stdout, "%s", "  ");
					else if (data[level][no].upkeys[i][col] >= 0 && data[level][no].upkeys[i][col] <= 9)
						fprintf(stdout, "%s", changeIntegerToStr[data[level][no].upkeys[i][col]]);
					else
						fprintf(stdout, "%d", data[level][no].upkeys[i][col]);
				}

				// 현재 위치와 같은 행에 해당하는 sidekeys의 강조를 제거한다
				for (i = 0; i < data[level][no].sideColSize; i++)
				{
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * i, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					if (data[level][no].sidekeys[row][i] == 0 && i != data[level][no].sideColSize - 1)
						fprintf(stdout, "%s", "  ");
					else if (data[level][no].sidekeys[row][i] >= 0 && data[level][no].sidekeys[row][i] <= 9)
						fprintf(stdout, "%s", changeIntegerToStr[data[level][no].sidekeys[row][i]]);
					else fprintf(stdout, "%d", data[level][no].sidekeys[row][i]);
				}

				// 플레이어 데이터를 초기화 시키고
				for (row = 0; row < pictureSize; row++) 
					for (col = 0; col < pictureSize; col++) 
						data[level][no].userData[row][col] = 0; 

				// 게임 보드를 재출력 한다
				for (row = 0; row < pictureSize; row++) 
					for (col = 0; col < pictureSize; col++) 
					{
						gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
						if ((row / 5 + col / 5) % 2 == 0) setColor(BLACK, WHITE);
						else setColor(BLACK, GRAY);
						ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
					}

				cntColoringBoxes = 0; cntAnsNum = 0; row = 0; col = 0;
			}
			else if (ch == 'a' || ch == 'A') // 색칠 명령 시
			{
				if (data[level][no].userData[row][col] == 0) // □ -> ■
				{
					data[level][no].userData[row][col] = 1;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
					cntColoringBoxes++; // 색칠 면의 개수를 증가시킨다
					if (data[level][no].ansData[row][col] == 1) // 정답이고, 색칠했다면 cntAnsNum 개수를 증가시킨다
						cntAnsNum++;
				}
				else if (data[level][no].userData[row][col] == 1) // ■ -> □
				{
					data[level][no].userData[row][col] = 0;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
					cntColoringBoxes--; // 색칠 면의 개수를 감소시킨다
					if (data[level][no].ansData[row][col] == 1) // 정답이고, 색칠을 취소했다면 cntAnsNum 개수를 감소시킨다
						cntAnsNum--; 
				}
			}
			else if (ch == 'd' || ch == 'D') // Ｘ표시 명령 시
			{
				if (data[level][no].userData[row][col] == 2) // Ｘ -> □
				{
					data[level][no].userData[row][col] = 0;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
				}
				else if (data[level][no].userData[row][col] == 0) // □ -> Ｘ
				{
					data[level][no].userData[row][col] = 2;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
				}
			}
			else if (ch != UP && ch != DOWN && ch != LEFT && ch != RIGHT) continue;

			// 위치이동 명령 시
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if ((row / 5 + col / 5) % 2 == 0) setColor(BLACK, WHITE);
			else setColor(BLACK, GRAY);
			if (data[level][no].userData[row][col] == 0)fputs("□", stdout);
			else if (data[level][no].userData[row][col] == 1) fputs("■", stdout);
			else fputs("Ｘ", stdout);

			// 현재 위치와 같은 열에 해당하는 upkey의 강조를 제거한다
			setColor(BLACK, WHITE);
			for (i = 0; i < data[level][no].upRowSize; i++)
			{
				gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + i);
				if (data[level][no].upkeys[i][col] == 0 && i != data[level][no].upRowSize - 1)
					fprintf(stdout, "%s", "  ");
				else if (data[level][no].upkeys[i][col] >= 0 && data[level][no].upkeys[i][col] <= 9)
					fprintf(stdout, "%s", changeIntegerToStr[data[level][no].upkeys[i][col]]);
				else
					fprintf(stdout, "%d", data[level][no].upkeys[i][col]);
			}

			// 현재 위치와 같은 행에 해당하는 sidekeys의 강조를 제거한다
			for (i = 0; i < data[level][no].sideColSize; i++)
			{
				gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * i, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
				if (data[level][no].sidekeys[row][i] == 0 && i != data[level][no].sideColSize - 1)
					fprintf(stdout, "%s", "  ");
				else if (data[level][no].sidekeys[row][i] >= 0 && data[level][no].sidekeys[row][i] <= 9)
					fprintf(stdout, "%s", changeIntegerToStr[data[level][no].sidekeys[row][i]]);
				else fprintf(stdout, "%d", data[level][no].sidekeys[row][i]);
			}

			switch (ch)
			{
			case UP: 
				row--; break;
			case DOWN: 
				row++; break;
			case LEFT:
				col--; break;
			case RIGHT:
				col++; break;
			}

			if (row < 0) row = pictureSize - 1;
			if (row > pictureSize - 1) row = 0;
			if (col < 0) col = pictureSize - 1;
			if (col > pictureSize - 1) col = 0;
		}
	}
	return 0;
}

// 전체 게임을 총괄하는 함수
void gameWorks(Level(*data)[9], Title *logo)
{
	int level = 0, no = 0;
	int **board = NULL;

startMenu:
	switch (gameWorks_showStartMenu()) 
	{
	case MEMBERSHIP:
		system("cls"); gameWorks_noFileAlertPopup(); 
		system("cls"); startupScreen_showTitle(logo);
		playSound_returnMain_repeatMainMusicPlayback();
		goto startMenu;

	case GUEST:
	guest_selectDifficulty:
		level = gameWorks_selectDifficultyLevel();
		switch (level)
		{
		case GOBACK:
			goto startMenu;
		
		case FIVE: case TEN: case FIFTEEN: case TWENTY:
		guest_selectGame:
			system("cls");
			gameWorks_showGrades(data, level); 
			
			no = gameWorks_selectGame(level); 
			switch (no) 
			{
			case -1: 
				setColor(WHITE, BLACK); 
				system("cls"); 
			    startupScreen_showTitle(logo); 
			    goto guest_selectDifficulty;
			default: 
				system("cls");
				setBoard_importAnsData(data, level, no);

			guest_setBoard:
				switch (setBoard(data, level, no)) 
				{
				case THERE_IS_NO_GAME: 
					system("cls");
					playSound_returnMain_repeatMainMusicPlayback();
					goto guest_selectGame;

				default: 
					playSound_GameStartSoundEffect();
					switch (gameWorks_playGame(data, level, no)) 
				    {
					case GAMEOVER:
						setColor(WHITE, BLACK);
						system("cls");
						data[level][no].timeStorage = 0;
						playSound_returnMain_repeatMainMusicPlayback();
						goto guest_setBoard;
					case RETURNGAME: 
						setColor(WHITE, BLACK);
						system("cls");
						playSound_returnMain_repeatMainMusicPlayback();
						goto guest_setBoard;
					case CLEAR: case BACKTOMAIN: 
						setColor(WHITE, BLACK);
						system("cls");
						startupScreen_showTitle(logo);
						playSound_returnMain_repeatMainMusicPlayback();
						goto startMenu;
					}
				}
			}
			break; 
		}
		break;

	case TUTORIAL: 
		playSound_GameStartSoundEffect();
		tutorial_runTutorial();
		clearScreen();
		playSound_returnMain_repeatMainMusicPlayback();
		startupScreen_showTitle(logo); 
		goto startMenu;

	case EDITOR: 
	editor_selectDifficulty:
		level = gameWorks_selectDifficultyLevel();
		switch (level) 
		{
		case GOBACK: goto startMenu;

		case FIVE: case TEN: case FIFTEEN: case TWENTY:
		editor_selectOption:
			system("cls");
			gameWorks_showLevel(level);

			switch (ansGenerator_selectDeleteOrGenerateOption()) 
			{
			case DEL: 
				no = ansGenerator_aboutDelete_selectAndDeleteData(data, level);
				switch (no) 
			    {
				case -1: setColor(WHITE, BLACK);
					     goto editor_selectOption;
				default: ansGenerator_aboutDelete_deleteData(data, level, no); 
					     setColor(WHITE, BLACK); 
						 goto editor_selectOption;
			    } break;

			case GENERATE: 
				board = ansGenerator_aboutGenerate_dynamicMemoryAllocation(level);
			editor_returnToGame:
				playSound_GameStartSoundEffect();
				ansGenerator_aboutGenerate_setBoard(board, level);
				switch (ansGenerator_aboutGenerate_editData(board, level))
				{
				case RETURNGAME: 
					ansGenerator_aboutGenerate_setBoard(board, level); 
					goto editor_returnToGame; 
				case GENERATEANS: 
					ansGenerator_aboutGenerate_generateAnswer(board, level); ansGenerator_freeMemory(board, level); 
					system("cls"); startupScreen_showTitle(logo);
					playSound_returnMain_repeatMainMusicPlayback();
					goto startMenu;
				case BACKTOMAIN: 
					ansGenerator_freeMemory(board, level); 
					system("cls"); startupScreen_showTitle(logo);
					playSound_returnMain_repeatMainMusicPlayback();
					goto startMenu;
				}
				break;

			case BACK: 
				system("cls"); startupScreen_showTitle(logo);
				goto editor_selectDifficulty;
			}
		}
		break;

	case QUIT: exit(0);
	}
}