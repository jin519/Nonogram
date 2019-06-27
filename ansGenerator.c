#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "setBoard.h"
#include "ansGenerator.h"
#include "consoleFunc.h"
#include "update.h"

extern char *rankFile[4][9];
extern char *answerFile[4][9];

char numberInString[9][5][11] = { { "    ■    ", "  ■■    ", "    ■    ", "    ■    ", "  ■■■  " },  // 1
								  { "  ■■■  ", "      ■  ", "  ■■■  ", "  ■      ", "  ■■■  " },     // 2
								  { "  ■■■  ", "      ■  ", "  ■■■  ", "      ■  ", "  ■■■  " },     // 3
								  { "  ■  ■  ", "  ■  ■  ", "  ■■■  ", "      ■  ", "      ■  " },   // 4
								  { "  ■■■  ", "  ■      ", "  ■■■  ", "      ■  ", "  ■■■  " },     // 5
								  { "  ■■■  ", "  ■      ", "  ■■■  ", "  ■  ■  ", "  ■■■  " },      // 6
								  { "  ■■■  ", "  ■  ■  ", "  ■  ■  ", "      ■  ", "      ■  " },   // 7
								  { "  ■■■  ", "  ■  ■  ", "  ■■■  ", "  ■  ■  ", "  ■■■  " },       // 8
								  { "  ■■■  ", "  ■  ■  ", "  ■■■  ", "      ■  ", "  ■■■  " } };    // 9

char *editorFile[4] = { "editorData_5.txt", "editorData_10.txt", "editorData_15.txt", "editorData_20.txt" };

// 동적으로 할당받은 메모리를 해제하는 함수
void ansGenerator_freeMemory(int **board, int level)
{
	int row = 0;
	level = (level + 1) * 5;

	for (row = 0; row < level; row++) free(board[row]);
	free(board);
}

// 정답의 삭제/생성 여부를 선택하는 메뉴 출력
int ansGenerator_selectDeleteOrGenerateOption() 
{
	char *arr[3] = { "    Delete Answer    ", "   Generate Answer   ", "       Go Back       " };
	char ch = '\0';
	int i, j, k;
	i = j = k = 0;

	setColor(WHITE, RED);
	gotoxy(46, 19); fputs("                     ", stdout);
	gotoxy(46, 20); fprintf(stdout, "%s", arr[i]);
	gotoxy(46, 21); fputs("                     ", stdout);
	setColor(WHITE, BLACK); 

	for (i = 1; i < 3; i++) 
	{
		gotoxy(46, 19 + (6 * i)); fputs("                     ", stdout);
		gotoxy(46, 19 + (6 * i) + 1); fprintf(stdout, "%s", arr[i]);
		gotoxy(46, 19 + (6 * i) + 2); fputs("                     ", stdout);
	}

	i = 0;
	while (1) 
	{
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출

		switch (ch)
		{
		case UP:
			setColor(WHITE, BLACK);
			gotoxy(46, 19 + (6 * i)); fputs("                     ", stdout);
			gotoxy(46, 19 + (6 * i) + 1); fprintf(stdout, "%s", arr[i]);
			gotoxy(46, 19 + (6 * i) + 2); fputs("                     ", stdout);
			i--; break;
		case DOWN: 
			setColor(WHITE, BLACK);
			gotoxy(46, 19 + (6 * i)); fputs("                     ", stdout);
			gotoxy(46, 19 + (6 * i) + 1); fprintf(stdout, "%s", arr[i]);
			gotoxy(46, 19 + (6 * i) + 2); fputs("                     ", stdout);
			i++;
		}

		if (i < 0) i = 2;
		else if (i > 2) i = 0;

		setColor(WHITE, RED);
		gotoxy(46, 19 + (6 * i)); fputs("                     ", stdout);
		gotoxy(46, 19 + (6 * i) + 1); fprintf(stdout, "%s", arr[i]);
		gotoxy(46, 19 + (6 * i) + 2); fputs("                     ", stdout);
	}

	// 화면 글자 지우기
	setColor(WHITE, BLACK);
	for (k = 0; k < 3; k++) 
	{
		for (j = 0; j < 3; j++)
		{
			gotoxy(46, 19 + (6 * k) + j);
			fputs("                     ", stdout);
		}
	}

	return i;
}

// 파일로부터 해당 라운드의 전체 정답 데이터를 구조체로 가져오는 함수
void ansGenerator_aboutDelete_importAnsDataToStructure(Level(*data)[9], int level) 
{
	FILE *fp = NULL;
	int pictureSize = (level + 1) * 5;
	int i = 0, row = 0, col = 0, rd = 0, tmp = 0;

	for (i = 0; i < 9; i++)
	{
		fopen_s(&fp, answerFile[level][i], "rt");
		if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][i]); exit(-1); }

		rd = fscanf_s(fp, "%d", &tmp); // 파일이 비어있는지 여부를 확인한다 
		if (rd == 1) // 비어있지 않다면
		{
			// 해당 번호의 구조체 배열 요소에 정답 데이터를 넣어준다 
			data[level][i].ansData = (int**)malloc(sizeof(int*)*pictureSize);
			for (row = 0; row < pictureSize; row++)
				data[level][i].ansData[row] = (int*)malloc(sizeof(int)*pictureSize);
			if (data[level][i].ansData == NULL) { puts("Memory Allocation Failure"); exit(-1); }

			data[level][i].ansData[0][0] = tmp;
			for (row = 0; row < pictureSize; row++) 
			{
				for (col = 0; col < pictureSize; col++) 
				{
					if (row == 0 && col == 0) continue;
					fscanf_s(fp, "%d", &data[level][i].ansData[row][col]);
				}
			}
		}
		fclose(fp);
	}
}

// 해당 번호의 정답 데이터를 보여주고, 삭제 여부를 선택하는 함수 -> 수정 필요(첫번쨰 그림 삭제 시 프로그램 터짐)
int ansGenerator_aboutDelete_selectAndDeleteData(Level(*data)[9], int level)
{
	char ch = '\0';
	int row = 0, col = 0, tmp = 0, i = 0;
	int pictureSize = (level + 1) * 5, xPos, backgroundSize;
	if (level % 2) { xPos = 13; backgroundSize = 22; }
	else { xPos = 14; backgroundSize = 21; }

	ansGenerator_aboutDelete_importAnsDataToStructure(data, level); // 파일로부터 해당 라운드의 전체 정답 데이터를 구조체로 가져온다

    // ESC 버튼 출력
	gotoxy(73 + backgroundSize, 17 + backgroundSize); fputs("ESC", stdout);

	// 버튼 출력
	setColor(WHITE, RED);
	for (col = 0; col < 5; col++)
	{
		gotoxy(xPos, 16 + col);
		fputs(numberInString[0][col], stdout);
	}

	setColor(WHITE, BLACK);
	for (row = 1; row < 9; row++)
	{
		for (col = 0; col < 5; col++)
		{
			gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * (row / 3));
			fputs(numberInString[row][col], stdout);
		}
	}

	// 정답 화면 배경 출력 
	setColor(WHITE, GRAY);
	for (row = 0; row < backgroundSize; row++)
	{
		gotoxy(xPos + 41, 16 + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
	}

	// 정답 화면 출력
	setColor(WHITE, WHITE);
	for (row = 0; row < pictureSize; row++)
		for (col = 0; col < pictureSize; col++)
		{
			gotoxy(xPos + 41 + (backgroundSize - pictureSize) + 2 * col, 16 + (backgroundSize - pictureSize) / 2 + row);
			if (data[level][0].ansData[row][col]) { setColor(WHITE, BLACK); fputs("  ", stdout); setColor(WHITE, WHITE); }
			else fputs("  ", stdout);
		}

	// 버튼 선택
	row = 0; 
	while (1)
	{
		tmp = row / 3;
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출
		else if (ch == ESC) { return -1; }

		// 방향키 입력 시
		switch (ch) 
		{
		case UP:
			setColor(WHITE, BLACK);
			for (col = 0; col < 5; col++)
			{
				gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * tmp);
				fprintf(stdout, "%s", numberInString[row][col]);
			}
			row -= 3; if (row < 0) row += 9;
			break;
		case DOWN: 
			setColor(WHITE, BLACK);
			for (col = 0; col < 5; col++)
			{
				gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * tmp);
				fprintf(stdout, "%s", numberInString[row][col]);
			}
			row += 3; if (row > 8) row -= 9;
			break;
		case LEFT: 
			setColor(WHITE, BLACK);
			for (col = 0; col < 5; col++)
			{
				gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * tmp);
				fprintf(stdout, "%s", numberInString[row][col]);
			}
			row--; if (row == -1 || (row / 3) < tmp) row += 3;
			break;
		case RIGHT: 
			setColor(WHITE, BLACK);
			for (col = 0; col < 5; col++)
			{
				gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * tmp);
				fprintf(stdout, "%s", numberInString[row][col]);
			}
			row++; if ((row / 3) > tmp) row -= 3;
		}

		setColor(WHITE, RED);
		for (col = 0; col < 5; col++)
		{
			gotoxy(xPos + 13 * (row % 3), 16 + col + 8 * (row / 3));
			fprintf(stdout, "%s", numberInString[row][col]);
		}

		setColor(WHITE, WHITE);
		if (data[level][row].ansData != NULL)
		{
			for (i = 0; i < pictureSize; i++)
				for (col = 0; col < pictureSize; col++)
				{
					gotoxy(xPos + 41 + (backgroundSize - pictureSize) + 2 * col, 16 + (backgroundSize - pictureSize) / 2 + i);
					if (data[level][row].ansData[i][col]) { setColor(WHITE, BLACK); fputs("  ", stdout); setColor(WHITE, WHITE); }
					else fputs("  ", stdout);
				}
		}
		else
		{
			for (i = 0; i < pictureSize; i++)
				for (col = 0; col < pictureSize; col++)
				{
					gotoxy(xPos + 41 + (backgroundSize - pictureSize) + 2 * col, 16 + (backgroundSize - pictureSize) / 2 + i);
					fputs("  ", stdout);
				}
		}
	}
	
	return row;
}

// 해당 번호의 정답 데이터 삭제 -> 문제가 있는 듯
void ansGenerator_aboutDelete_deleteData(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	int i = 0, pictureSize = (level + 1) * 5;

	// 구조체 내 정답 데이터를 소멸시킨다
	if (data[level][no].ansData != NULL) // 정답 데이터가 존재한다면
	{
		ansGenerator_freeMemory(data[level][no].ansData, level);
		data[level][no].ansData = NULL;
	}

	// 정답 파일을 오픈하고 데이터를 소멸시킨다
	fopen_s(&fp, answerFile[level][no], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }
	fputs("", stdout);
	fclose(fp);

	// 랭킹 파일을 오픈하고 데이터를 소멸시킨다
	fopen_s(&fp, rankFile[level][no], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }
	fputs("", stdout);
	fclose(fp);
}

// 타이틀 출력
void ansGenerator_aboutGenerate_printTitle() 
{
	setColor(WHITE, RED);
	gotoxy(47, 3);
	fputs("                    ", stdout);
	gotoxy(47, 4);
	fputs("  Answer Generator  ", stdout);
	gotoxy(47, 5);
	fputs("                    ", stdout);
}

// 제어키 출력
void ansGenerator_aboutGenerate_printControlKeys(int level) 
{
	int xPos1, xPos2, xPos3;
	if (level % 2 == 0) { xPos1 = 12; xPos2 = 17; xPos3 = 19; } // 5*5, 15*15
	else { xPos1 = 10; xPos2 = 15; xPos3 = 17; } // 10*10, 20*20

	gotoxy(xPos1, 4); fputs("ESC", stdout);
	gotoxy(xPos2, 33); fputs("┏━┓┏━━━━┓┏━━━━━┓", stdout);
	gotoxy(xPos2, 34); fputs("┃Ｏ┃┃ＳＡＶＥ┃┃ＲＥＳＥＴ┃", stdout);
	gotoxy(xPos2, 35); fputs("┗━┛┗━━━━┛┗━━━━━┛", stdout);
	gotoxy(xPos3, 37); fputs("Ａ       Ｓ           Ｒ", stdout);
	gotoxy(78, 33); fputs("┏━┓", stdout);
	gotoxy(72, 34); fputs("┃↑┃", stdout);
	gotoxy(78, 35); fputs("┗━┛", stdout);
	gotoxy(72, 36); fputs("┏━┓┏━┓┏━┓", stdout);
	gotoxy(72, 37); fputs("┃←┃┃↓┃┃→┃", stdout);
	gotoxy(72, 38); fputs("┗━┛┗━┛┗━┛", stdout);
}

// board 배열을 저장할 메모리를 동적할당하고, 파일로부터 데이터를 가져와서 요소 값을 초기화하는 함수
int** ansGenerator_aboutGenerate_dynamicMemoryAllocation(int level) 
{
	FILE *fp = NULL;
	int **board = NULL;
	int row = 0, col = 0, rd = 0, pictureSize;
	pictureSize = (level + 1) * 5;
	
	// 메모리 동적할당
	board = (int**)malloc(sizeof(int*)*pictureSize);
	for (row = 0; row < pictureSize; row++) board[row] = (int*)malloc(sizeof(int)*pictureSize);
	if (board == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// 파일 열기
	fopen_s(&fp, editorFile[level], "rt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", editorFile[level]); exit(-1); }

	// 파일로부터 데이터를 가져온다
	for (row = 0; row < pictureSize; row++) {
		for (col = 0; col < pictureSize; col++)
		{
			if (row == 0 && col == 0) 
			{
				rd = fscanf_s(fp, "%d", &board[row][col]);
				if (rd == EOF) break;
			}
			else fscanf_s(fp, "%d", &board[row][col]);
		}
		if (rd == EOF) break;
	}

	// 파일이 비어있다면 모든 요소를 0으로 초기화한다
	if (rd == EOF)
	{
		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < pictureSize; col++)
				board[row][col] = 0;
	}

	fclose(fp); // 파일을 닫고
	return board; // board 주소를 반환한다
}

// 수치를 해석하여 해당 유니코드 값을 출력하는 함수
void ansGenerator_aboutGenerate_printIntegerToUnicode(int **board, int *row, int *col)
{
	if (board[*row][*col] == 0) fputs("□", stdout);      // □ : 0  
	else if (board[*row][*col] == 1) fputs("■", stdout); // ■ : 1
	else fputs("Ｘ", stdout);                            // Ｘ : 2
}

// 편집 화면을 출력하는 함수
void ansGenerator_aboutGenerate_setBoard(int **board, int level)
{
	int row = 0, col = 0, x, y, backgroundSize;
	if (level % 2) { x = 10; y = 9; backgroundSize = 22; }
	else { x = 12; y = 9; backgroundSize = 21; }

	system("cls");
	ansGenerator_aboutGenerate_printControlKeys(level); // 제어키 출력
	ansGenerator_aboutGenerate_printTitle(); // 타이틀 출력
	
	// background 출력
	setColor(WHITE, GRAY);
	for (row = 0; row < backgroundSize; row++)
	{
		gotoxy(x, y + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
		gotoxy(x + 2 * backgroundSize + 5, y + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
	}

	level = (level + 1) * 5;

	// board 출력
	for (row = 0; row < level; row++)
	{
		setColor(WHITE, BLACK);
		gotoxy(x + backgroundSize - level, y + row + (backgroundSize - level) / 2);
		for (col = 0; col < level; col++) ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
		gotoxy(x + backgroundSize - level + 2 * backgroundSize + 5, y + row + (backgroundSize - level) / 2);
		for (col = 0; col < level; col++) 
		{
			if (board[row][col]) { setColor(WHITE, WHITE); fputs("  ", stdout); setColor(WHITE, BLACK); }
			else fputs("  ", stdout);
		} 
	}
}

// 데이터를 파일에 저장하는 함수
void ansGenerator_aboutGenerate_saveDataToFile(int **board, int level)
{
	FILE *fp = NULL;
	int row = 0, col = 0, pictureSize;
	pictureSize = (level + 1) * 5;
	
	fopen_s(&fp, editorFile[level], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", editorFile[level]); exit(-1); }

	for (row = 0; row < pictureSize; row++)
	{
		for (col = 0; col < pictureSize; col++) 
			fprintf(fp, "%d ", board[row][col]);
		fputc('\n', fp);
	}

	fclose(fp);
}

// 팝업창 출력 함수
int ansGenerator_aboutGenerate_showPopup(int level) 
{
	int row = 0, col = 0, x, y, backgroundSize, gapX, gapY;
	char ch = '\0';
	char *menu[3] = { "     Previous Page     ", 
		              "    Generate Answer    ", 
		              "   Back To Main Menu   " };

	if (level % 2) { x = 12; y = 9; backgroundSize = 21; gapX = 3; gapY = 11; }
	else { x = 10; y = 9; backgroundSize = 22; gapX = 4; gapY = 12; }

	// 기본 틀 출력
	for (row = 0; row < backgroundSize; row++)
	{
		gotoxy(x, y + row);
		if (row < 3)
		{
			setColor(WHITE, GRAY);
			for (col = 0; col < 2 * backgroundSize + 2; col++) fputs("  ", stdout);
		}
		else
		{
			setColor(BLACK, WHITE);
			for (col = 0; col < 2 * backgroundSize + 2; col++) fputs("  ", stdout);
			fputs(" ", stdout);
		}
	}
	gotoxy(x + 4 * backgroundSize + 1, y + 1); setColor(BLACK, WHITE); fputs("Ｘ", stdout);

	// 옵션 버튼 생성
	setColor(WHITE, BLACK);
	gotoxy(x + gapX, y + gapY - 1); fputs("                       ", stdout);
	gotoxy(x + gapX, y + gapY); fputs(menu[0], stdout);
	gotoxy(x + gapX, y + gapY + 1); fputs("                       ", stdout);
	
	setColor(BLACK, GRAY);
	for (col = 1; col < 3; col++) 
	{
		gotoxy(x + gapX + (30 * col), y + gapY - 1); fputs("                       ", stdout);
		gotoxy(x + gapX + (30 * col), y + gapY); fputs(menu[col], stdout);
		gotoxy(x + gapX + (30 * col), y + gapY + 1); fputs("                       ", stdout);
	}
	
	// 옵션 선택
	col = 0;
	while (1) 
	{
		ch = _getch(); // 키 입력

		if (ch == 13 || ch == ' ') break; // enter, spacebar 입력 시 반복 탈출
		else if (ch == LEFT || ch == RIGHT)
		{
			setColor(BLACK, GRAY);
			gotoxy(x + gapX + (30 * col), y + gapY - 1); fputs("                       ", stdout);
			gotoxy(x + gapX + (30 * col), y + gapY); fputs(menu[col], stdout);
			gotoxy(x + gapX + (30 * col), y + gapY + 1); fputs("                       ", stdout);
		}
		switch (ch) 
		{
		case LEFT: col--; break;
		case RIGHT: col++;        
		}

		if (col < 0) col = 2;
		else if (col > 2) col = 0;

		setColor(WHITE, BLACK);
		gotoxy(x + gapX + (30 * col), y + gapY - 1); fputs("                       ", stdout);
		gotoxy(x + gapX + (30 * col), y + gapY); fputs(menu[col], stdout);
		gotoxy(x + gapX + (30 * col), y + gapY + 1); fputs("                       ", stdout);
	}
	
	return col;
}

// 데이터 편집 함수 
int ansGenerator_aboutGenerate_editData(int **board, int level)
{
	char ch = '\0';
	int row = 0, col = 0, x, y, backgroundSize, pictureSize;
	if (level % 2) { x = 10; y = 9; backgroundSize = 22; } // 10*10, 20*20
	else { x = 12; y = 9; backgroundSize = 21; } // 5*5, 15*15
	pictureSize = (level + 1) * 5;

	while (1) 
	{
		// 배열 요소의 값을 해석하여 대응되는 유니코드 출력
		gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
		setColor(BRIGHT_YELLOW, BLACK);
		ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);  

		ch = _getch(); // 키 입력
		if (ch == ESC) // ESC 입력 시 
			return ansGenerator_aboutGenerate_showPopup(pictureSize);
		else if (ch == 'r' || ch == 'R') // 초기화 명령 시 
		{
			for (row = 0; row < pictureSize; row++) { for (col = 0; col < pictureSize; col++) board[row][col] = 0; }
			setColor(WHITE, BLACK);
			for (row = 0; row < pictureSize; row++)
			{
				gotoxy(x + backgroundSize - pictureSize, y + row + (backgroundSize - pictureSize) / 2);
				for (col = 0; col < pictureSize; col++) ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
				gotoxy(x + backgroundSize - pictureSize + 2 * backgroundSize + 5, y + row + (backgroundSize - pictureSize) / 2);
				for (col = 0; col < pictureSize; col++) fputs("  ", stdout);
			}
		}
		else if (ch == 's' || ch == 'S') // 저장 명령 시 
			ansGenerator_aboutGenerate_saveDataToFile(board, level);
		else if (ch == 'a' || ch == 'A') // 색칠 명령 시
		{
			if (board[row][col] == 0) // □ -> ■
			{
				board[row][col] = 1;
				gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("■", stdout);
				setColor(WHITE, WHITE);
				gotoxy(x + backgroundSize - pictureSize + 2 * backgroundSize + 5 + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("  ", stdout);
			}
			else if (board[row][col] == 1) // ■ -> □
			{
				board[row][col] = 0; 
				gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("□", stdout);
				setColor(WHITE, BLACK);
				gotoxy(x + backgroundSize - pictureSize + 2 * backgroundSize + 5 + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("  ", stdout);
			}
		}
		else if (ch != 0x48 && ch != 0x50 && ch != 0x4b && ch != 0X4d) continue;

		// 위치이동 명령 시
		setColor(WHITE, BLACK);
		gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
		
		switch (ch)
		{
		case 0x48: // 상방향 키
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			row--; break;
		case 0x50: // 하방향 키
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			row++; break;
		case 0x4b: // 좌방향 키
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			col--; break;
		case 0X4d: // 우방향 키
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			col++; break;
		}
	
		if (row < 0) row = pictureSize - 1;
		if (row > pictureSize - 1) row = 0;
		if (col < 0) col = pictureSize - 1;
		if (col > pictureSize - 1) col = 0;
	}

	return 0;
}

// 해당 레벨의 정답 파일을 순차적으로 탐색하여 비어있는 곳에 생성한 정답 데이터를 입력하는 함수 -> 꽉차면 저장못해라고 말해주는 거 만들기
void ansGenerator_aboutGenerate_generateAnswer(int **board, int level) 
{
	FILE *fp = NULL;
	int row = 0, col = 0, no = 1, tmp = 0, pictureSize;
	pictureSize = (level + 1) * 5;

	for (row = 0; row < 9; row++) 
	{
		// 해당 레벨의 정답 파일들을 순차적으로 오픈한다 
		fopen_s(&fp, answerFile[level][row], "rt"); 
		if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][row]); exit(-1); }

		if (fscanf_s(fp, "%d", &tmp) != EOF) { fclose(fp); continue; } // 빈 파일이 아니라면
		else 
		{ // 생성한 정답 데이터를 분석하여 각각의 값을 입력한다
			fclose(fp);
			update_AnalyzeAnsDataAndSaveToFile(board, answerFile[level][row], pictureSize);
			break;
		}
	}

	// 해당 레벨의 에디터 파일을 초기화 한다
	fopen_s(&fp, editorFile[level], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", editorFile[level]); exit(-1); }
	fputs("", fp);

	fclose(fp);
}