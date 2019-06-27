#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "consoleFunc.h"

extern char changeIntegerToStr[10][3];

// 타이틀, 조작키를 제외하고 화면의 나머지 부분을 지우는 함수
void tutorial_clearScreenExceptTitleAndButton()
{
	int i = 0;

	setColor(WHITE, BLACK);
	for (i = 15; i < 30; i++)
	{
		gotoxy(10, i);
		fputs("                                                                                             ", stdout);
	}
}

// 화면에서 설명문을 지우는 함수
void tutorial_clearOnlyInstructions() 
{
	int i = 0;

	setColor(WHITE, BLACK);
	for (i = 13; i < 32; i++)
	{
		gotoxy(34, i);
		fputs("                                                                         ", stdout);
	}
}

// 첫번째 페이지를 출력하는 함수
void tutorial_printFirstPage() 
{
	int arr[8][5][3] = { { { 1, 1, 1 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } },   // t
						 { { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 0, 1, 0 } },   // u
						 { { 1, 1, 1 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } },   // t
						 { { 0, 1, 0 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 0, 1, 0 } },   // o
						 { { 1, 1, 0 }, { 1, 0, 1 }, { 1, 1, 0 }, { 1, 0, 1 }, { 1, 0, 1 } },   // r
						 { { 0, 1, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 } },   // i
						 { { 0, 1, 0 }, { 1, 0, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 1 } },   // a
						 { { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 }, { 1, 1, 1 } } }; // l
	int i = 0, row = 0, col = 0;

	clearScreen(); // 화면 지우기

	// 조작 버튼을 출력한다
	gotoxy(5, 35); fputs("┏━┓", stdout);
	gotoxy(5, 36); fputs("┃←┃", stdout);
	gotoxy(5, 37); fputs("┗━┛", stdout);
	gotoxy(102, 35); fputs("┏━┓", stdout);
	gotoxy(100, 36); fputs("┃→┃", stdout);
	gotoxy(102, 37); fputs("┗━┛", stdout);

	// TUTORIAL 그래픽을 출력한다
	setColor(WHITE, WHITE);
	for (i = 0; i < 8; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) 
	{
		if (arr[i][row][col] == 1) 
		{
			if (i < 5) gotoxy(31 + 2 * col + 7 * i, 5 + row); // TUTOR
			else if (i == 5) gotoxy(29 + 2 * col + 7 * i, 5 + row); // I
			else gotoxy(27 + 2 * col + 7 * i, 5 + row); // AL
			fputs("  ", stdout);
		}
	}}}

	// 간단한 설명을 출력한다
	setColor(BRIGHT_CYAN, BLACK);
	gotoxy(20, 15); fputs("NEMO LOGIC", stdout);
	setColor(WHITE, BLACK);
	gotoxy(31, 15); fputs("is a logic puzzle with simple rules and challenging solutions.", stdout);
	gotoxy(46, 17); fputs("The rules are simple.", stdout);
	gotoxy(15, 19); fputs("You have a grid of squares, which must be either filled in black or marked with X.", stdout);
	gotoxy(10, 21); fputs("Beside each row of the grid are listed the lengths of the runs of black squares on that row.", stdout);
	gotoxy(14, 23); fputs("Above each column are listed the lengths of the runs of black squares in that column.", stdout);
	gotoxy(38, 25); fputs("Your aim is to find all black squares.", stdout);
	gotoxy(39, 27); fputs("Press A on a square to make it black.", stdout);
	gotoxy(45, 29); fputs("Press D to mark with X.", stdout);

	_getch(); // 버퍼 제거
}

// 두번째 페이지를 출력하는 함수
void tutorial_printSecondPage()
{
	int tutorial_ansData[5][5] = { { 1, 0, 0, 0, 1 },{ 1, 1, 0, 1, 1 },{ 0, 1, 1, 1, 0 },
								   { 1, 1, 0, 0, 0 },{ 1, 1, 0, 0, 0 } };
	int tutorial_upkeys[2][5] = { { 2, 0, 0, 0, 0 },{ 2, 4, 1, 2, 2 } };
	int tutorial_sidekeys[5][2] = { { 1, 1 },{ 2, 2 },{ 0, 3 },{ 0, 2 },{ 0, 2 } };
	int i = 0, j = 0;

	// 배경 출력
	setColor(BLACK, WHITE);
	for (i = 0; i < 9; i++)
	{
		gotoxy(14, 12 + i);
		for (j = 0; j < 8; j++) fputs("  ", stdout);
		gotoxy(14, 24 + i);
		for (j = 0; j < 8; j++) fputs("  ", stdout);
	}

	// upkeys 출력
	for (i = 0; i < 2; i++)
	{
		gotoxy(19, 13 + i);
		for (j = 0; j < 5; j++)
		{
			if (tutorial_upkeys[i][j] == 0) fputs("  ", stdout);
			else fputs(changeIntegerToStr[tutorial_upkeys[i][j]], stdout);
		}
		gotoxy(19, 25 + i);
		for (j = 0; j < 5; j++)
		{
			if (tutorial_upkeys[i][j] == 0) fputs("  ", stdout);
			else fputs(changeIntegerToStr[tutorial_upkeys[i][j]], stdout);
		}
	}

	// sidekeys 출력
	for (i = 0; i < 5; i++)
	{
		gotoxy(15, 15 + i);
		for (j = 0; j < 2; j++)
		{
			if (tutorial_sidekeys[i][j] == 0) fputs("  ", stdout);
			else fputs(changeIntegerToStr[tutorial_sidekeys[i][j]], stdout);
		}
		gotoxy(15, 27 + i);
		for (j = 0; j < 2; j++)
		{
			if (tutorial_sidekeys[i][j] == 0) fputs("  ", stdout);
			else fputs(changeIntegerToStr[tutorial_sidekeys[i][j]], stdout);
		}
	}

	// board 출력
	for (i = 0; i < 5; i++)
	{
		gotoxy(19, 15 + i);
		fputs("□□□□□", stdout);
		gotoxy(19, 27 + i);
		for (j = 0; j < 5; j++)
		{
			if (tutorial_ansData[i][j] == 0) fputs("Ｘ", stdout);
			else fputs("■", stdout);
		}
	}

	setColor(BRIGHT_CYAN, BLACK);
	gotoxy(34, 16); fputs("** You can not have 2 black runs without at least one X separating them", stdout);

	setColor(WHITE, BLACK);
	gotoxy(34, 21); fputs("Q. What are these numbers for?", stdout);
	gotoxy(34, 23); fputs("A. Each number indicates the number of black squares", stdout);
	gotoxy(37, 24); fputs("on each run in that row/column", stdout);

	gotoxy(34, 26); fputs("Q. What is not allowed?", stdout);
	gotoxy(34, 28); fputs("A. ", stdout);
	setColor(BLACK, CYAN);
	fprintf(stdout, " %s%s■■■■□ ", changeIntegerToStr[2], changeIntegerToStr[2]);

	_getch(); // 버퍼 제거
}

// 세번째 페이지를 출력하는 함수
void tutorial_printThirdPage() 
{
	setColor(WHITE, BLACK);
	gotoxy(34, 13); fputs("Q. Where do I start?", stdout);
	gotoxy(34, 15); fputs("A. Think logical! Take a look at this example:", stdout);
	setColor(BLACK, CYAN);
	gotoxy(37, 17); fprintf(stdout, "   %s□□□□□ ", changeIntegerToStr[3]);

	setColor(WHITE, BLACK);
	gotoxy(37, 19); fputs("If the run starts at the beginning of the row", stdout);
	gotoxy(37, 20); fputs("it will end at the third square:", stdout);
	setColor(BLACK, CYAN);
	gotoxy(37, 22); fprintf(stdout, "   %s■■■□□ ", changeIntegerToStr[3]);

	setColor(WHITE, BLACK);
	gotoxy(37, 24); fputs("If the run ends at the end of the row", stdout);
	gotoxy(37, 25); fputs("it will start from the third square", stdout);
	setColor(BLACK, CYAN);
	gotoxy(37, 27); fprintf(stdout, "   %s□□■■■ ", changeIntegerToStr[3]);

	setColor(WHITE, BLACK);
	gotoxy(37, 29); fputs("In both cases the third square is black", stdout);
	setColor(BLACK, CYAN);
	gotoxy(37, 31); fprintf(stdout, "   %s□□■□□ ", changeIntegerToStr[3]);

	_getch(); // 버퍼 제거
}

// 튜토리얼을 실행하는 함수
void tutorial_runTutorial() 
{
	char ch = '\0';
	int cnt = 0;

firstPage:
	tutorial_printFirstPage();
	
	ch = _getch();
	switch (ch)
	{
	case LEFT: return;
	case RIGHT:
	secondPage:
		tutorial_clearScreenExceptTitleAndButton();
		tutorial_printSecondPage();

		ch = _getch();
		switch (ch) 
		{
		case LEFT:
			goto firstPage;
		case RIGHT:
			tutorial_clearOnlyInstructions();
			tutorial_printThirdPage();
			
			ch = _getch();
			if (ch == LEFT) 
			{
				tutorial_clearOnlyInstructions();
				goto secondPage;
			}
		}
	}
}