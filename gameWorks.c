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

char grade[4][7] = { "�١١�", "�ڡ١�", "�ڡڡ�", "�ڡڡ�" };

// ���� ����
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

// ���� �޴��� ����ϴ� �Լ�
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
		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��

		switch (ch)
		{
		case 0x48: gotoxy(86, 20 + 2 * i);  // ����� Ű
			setColor(WHITE, BLACK);
			fprintf(stdout, "%s", arr[i]);
			i--; break;
		case 0x50: gotoxy(86, 20 + 2 * i);  // �Ϲ��� Ű
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

	// ȭ�� ���� �����
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 20 + 2 * j);
		fputs("                    ", stdout);
	}

	return i;
}

// ���̵��� �����ϴ� �Լ�
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
		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��

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

	// ȭ�� ���� �����
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 21 + 2 * j);
		fputs("                   ", stdout);
	}

	return i;
}

// no ������ ����ϴ� �Լ�
void gameWorks_showLevel(int level) 
{
	char no[4][7][71] = { { "                                                                      ",
							"              ������      ��      ��      ������              ",
							"              ��                ��  ��        ��                      ",
							"              ������          ��          ������              ",
							"                      ��        ��  ��                ��              ",
							"              ������      ��      ��      ������              ",
							"                                                                      " },
							{ "                                                                      ",
							"          ��  ������      ��      ��      ��  ������          ",
							"          ��  ��      ��        ��  ��        ��  ��      ��          ",
							"          ��  ��      ��          ��          ��  ��      ��          ",
							"          ��  ��      ��        ��  ��        ��  ��      ��          ",
							"          ��  ������      ��      ��      ��  ������          ",
							"                                                                      " },
							{ "                                                                      ",
							"          ��  ������      ��      ��      ��  ������          ",
							"          ��  ��                ��  ��        ��  ��                  ",
							"          ��  ������          ��          ��  ������          ",
							"          ��          ��        ��  ��        ��          ��          ",
							"          ��  ������      ��      ��      ��  ������          ",
							"                                                                      " },
							{ "                                                                      ",
							"  ������  ������      ��      ��      ������  ������  ",
							"          ��  ��      ��        ��  ��                ��  ��      ��  ",
							"  ������  ��      ��          ��          ������  ��      ��  ",
							"  ��          ��      ��        ��  ��        ��          ��      ��  ",
							"  ������  ������      ��      ��      ������  ������  ",
							"                                                                      " } };
	int i = 0;

	setColor(WHITE, BLUE);
	for (i = 0; i < 7; i++)
	{
		gotoxy(21, 5 + i);
		fputs(no[level][i], stdout);
	}
}

// ������ ����ϴ� �Լ�
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

// ���� ��ȣ�� �����ϴ� �Լ�
int gameWorks_selectGame(int level)
{
	char ch = '\0';
	int i = 0, j = 0, tmp = 0;
	
	gotoxy(21, 3); fputs("ESC", stdout); // ESC Ű�� ȭ�鿡 ����Ѵ�
	gameWorks_showLevel(level); // no ������ ȭ�鿡 ����Ѵ�

	// button ����
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
		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��
		else if (ch == ESC) { return -1; break; } // ESC �Է� �� ���� ȭ������ ���ư���
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

	// ȭ�� ���� �����
	setColor(WHITE, BLACK);
	for (j = 0; j < 5; j++)
	{
		gotoxy(86, 21 + 2 * j);
		fputs("                   ", stdout);
	}

	return i; // ��ȣ ������ �����Ѵ�
}

// �˾�â Ʋ(���)�� ����ϴ� �Լ�
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
	gotoxy(80, 8); fputs("��", stdout);
}

// "������ �������Դϴ�." �˸� â�� ����ϴ� �Լ�
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
	gameWorks_printPopupBackground(); // ����� ����Ѵ�

	// SORRY �׷����� ����Ѵ�
	setColor(WHITE, BLACK);
	for (i = 0; i < 5; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		if (sorry[i][row][col] == 1)
		{
			gotoxy(36 + 2 * col + 7 * i, 14 + row);
			fputs("  ", stdout);
	}}}}

	// ���� �޼����� ����Ѵ�
	setColor(BLACK, WHITE);
	gotoxy(40, 22); fputs("The game is being produced.", stdout);
	gotoxy(42, 23); fputs("Please wait for update.", stdout);
	gotoxy(31, 25); fputs("Press Enter to return to the previous screen.", stdout);

	// ENTER ��ư ����
	setColor(WHITE, BLACK);
	gotoxy(48, 29); fputs("           ", stdout);
	gotoxy(48, 30); fputs(key, stdout);
	gotoxy(48, 31); fputs("           ", stdout);

	while (!_kbhit()); // �ƹ�Ű�� �Է��ϸ� �Ѿ��
	_getch(); // ���� ����
}

// ���� ���� �߿� ESC�� ������ �� �˾�â�� ����ϴ� �Լ�
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

	gotoxy(51, 6); setColor(WHITE, BLACK); fputs("      ", stdout); // ����� ���� �ð� �˸��̸� �����
	gameWorks_printPopupBackground(); // â �⺻ Ʋ(���)�� ����Ѵ�

	// ���� �ð��� ȭ�鿡 �׷������� ǥ���Ѵ�
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

	// ��ư�� ����Ѵ�
	setColor(WHITE, BLACK);
	gotoxy(28, 30); fputs("                       ", stdout);
	gotoxy(28, 31); fputs(menu[0], stdout);
	gotoxy(28, 32); fputs("                       ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(56, 30); fputs("                       ", stdout);
	gotoxy(56, 31); fputs(menu[1], stdout);
	gotoxy(56, 32); fputs("                       ", stdout);

	// �ɼ� ����
	row = 0; col = 0;
	while (1)
	{
		ch = _getch(); // Ű �Է�

		if (ch == 13 || ch == ' ') break;  // enter, spacebar �Է� �� �ݺ� Ż��
		else if (ch == 0x4b || ch == 0X4d) // �¹��� Ȥ�� ����� Ű ���� ��
		{
			setColor(BLACK, GRAY);
			gotoxy(28 + 28 * col, 30); fputs("                       ", stdout);
			gotoxy(28 + 28 * col, 31); fputs(menu[col], stdout);
			gotoxy(28 + 28 * col, 32); fputs("                       ", stdout);
		}
		switch (ch)
		{
		case 0x4b: col--; break; // �¹��� Ű
		case 0X4d: col++;        // ����� Ű
		}

		if (col < 0) col = 1;
		else if (col > 1) col = 0;

		setColor(WHITE, BLACK);
		gotoxy(28 + 28 * col, 30); fputs("                       ", stdout);
		gotoxy(28 + 28 * col, 31); fputs(menu[col], stdout);
		gotoxy(28 + 28 * col, 32); fputs("                       ", stdout);
	}

	if (col == 1) col = 2; // gameWorks.c ���Ͽ� ������ �������� Ȱ���ϱ� ���� ���� ����
	return col;
}

// clear ȭ���� ����ϴ� �Լ� 
void gameWorks_showClearPopup(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	Rank arr[4] = { 0 }; // ��ŷ �����͸� ������ ����ü �迭
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

	// �˾�â Ʋ(���)�� ����Ѵ�
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
	gotoxy(102, 6); fputs("��", stdout);

	// CLEAR �׷����� ����Ѵ�
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

	// ȸ�� Ʋ�� ����Ѵ�
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

	// ������ ����Ѵ�
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

	// �ҿ� �ð��� ����Ѵ�
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

	// ������ ����Ѵ�
	setColor(BLACK, WHITE);
	gotoxy(xPos + 47 + 4, 21);
	fputs("              ", stdout);
	gotoxy(xPos + 47 + 4, 22);
	fputs("  Your Grade  ", stdout);
	gotoxy(xPos + 47 + 4, 23);
	fputs("              ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(xPos + 47 + 22, 22); fputs(grade[data[level][no].achievement], stdout);

	// ��ŷ�� ����Ѵ�
	setColor(BLACK, WHITE);
	gotoxy(xPos + 47 + 4, 25);
	fputs("              ", stdout);
	gotoxy(xPos + 47 + 4, 26);
	fputs("     Rank     ", stdout);
	gotoxy(xPos + 47 + 4, 27);
	fputs("              ", stdout);

	for (row = 0; row < 4; row++) { arr[row].timeStorage = INT_MAX; }
	fopen_s(&fp, rankFile[level][no], "rt"); // �ش� ��° ������ ��ŷ ������ ��� �ִ� ������ �б� ���� ����

	i = 0;
	while (1)
	{
		rd = fscanf(fp, "%s %d", arr[i].name, &arr[i].timeStorage);
		if (rd < 2) break;
		i++;
	}

	if (!i) // ���� �ȿ� ������ �ϳ��� ���ٸ� 
	{
		fclose(fp); // ������ �ݴ´�
		fopen_s(&fp, rankFile[level][no], "wt"); // ������ ���� ���� �ٽ� ���� 
		fprintf(fp, "%s %d\n", "guest", (int)data[level][no].timeStorage); // ���� �����͸� �����Ѵ�
		fclose(fp); // ������ �ݴ´�

		// ȭ�鿡 ��ŷ ������ ����Ѵ� 
		setColor(BLACK, GRAY);
		gotoxy(xPos + 47 + 4, 29);
		fprintf(stdout, "1. %s, %02d:%02d", "guest", min, sec);
	}
	else // ���� �ȿ� �ϳ� �̻��� �����Ͱ� �ִٸ�
	{
		fclose(fp); // ������ �ݴ´�
		strcpy_s(arr[i].name, 50, "guest");
		arr[i].timeStorage = (int)data[level][no].timeStorage;

		gameWorks_bubbleSort(arr, 4); // ������������ ������ ����

		// ȭ�鿡 3����� ��ŷ ������ ����Ѵ�
		setColor(BLACK, GRAY);
		for (row = 0; row < 3; row++)
		{
			if (arr[row].timeStorage == INT_MAX) break;
			min = (arr[row].timeStorage / CLOCKS_PER_SEC) / 60;
			sec = (arr[row].timeStorage / CLOCKS_PER_SEC) % 60;
			gotoxy(xPos + 51, 29 + 2 * row);
			fprintf(stdout, "%d. %s, %02d:%02d", row + 1, arr[row].name, min, sec);
		}

		fopen_s(&fp, rankFile[level][no], "wt"); // ������ ���� ���� �ٽ� ���� 
		for (row = 0; row < 3; row++) // 3����� �����͸� �����Ѵ�
		{
			if (arr[row].timeStorage == INT_MAX) break;
			fprintf(fp, "%s %d\n", arr[row].name, arr[row].timeStorage);
		}
		fclose(fp); // ������ �ݴ´�
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

// game over ȭ���� ����ϴ� �Լ�
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
	
	// game over �׷��� ���
	setColor(BLACK, BLACK);
	for (i = 0; i < 9; i++) { for (row = 0; row < 5; row++) { for (col = 0; col < 3; col++) {
		if (arr[i][row][col] == 1)
		{
			if (i >= 5) gotoxy(20 + 2 * col + 7 * i, 14 + row); 
			else if (i == 0 && row == 2 && col == 1) gotoxy(26 + 2 * col + 7 * i, 14 + row);
			else gotoxy(25 + 2 * col + 7 * i, 14 + row); 
			fputs("  ", stdout);
	}}}}

	// ��ư ���
	setColor(WHITE, BLACK);
	gotoxy(34, 29); fputs("           ", stdout);
	gotoxy(34, 30); fputs(button[0], stdout);
	gotoxy(34, 31); fputs("           ", stdout);

	setColor(BLACK, GRAY);
	gotoxy(62, 29); fputs("           ", stdout);
	gotoxy(62, 30); fputs(button[1], stdout);
	gotoxy(62, 31); fputs("           ", stdout);

	// �ɼ� ����
	col = 0;
	while (1)
	{
		ch = _getch(); // Ű �Է�

		if (ch == 13 || ch == ' ') break;  // enter, spacebar �Է� �� �ݺ� Ż��
		else if (ch == 0x4b || ch == 0X4d) // �¹��� Ȥ�� ����� Ű ���� ��
		{
			setColor(BLACK, GRAY);
			gotoxy(34 + 28 * col, 29); fputs("           ", stdout);
			gotoxy(34 + 28 * col, 30); fputs(button[col], stdout);
			gotoxy(34 + 28 * col, 31); fputs("           ", stdout);
		}
		switch (ch)
		{
		case 0x4b: col--; break; // �¹��� Ű
		case 0X4d: col++;        // ����� Ű
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

// ������ �����ϴ� �Լ� 
int gameWorks_playGame(Level(*data)[9], int level, int no)
{
	char ch = '\0';
	int row = 0, col = 0, i = 0, j = 0;
	int pictureSize = (level + 1) * 5, cntAnsNum = 0, cntColoringBoxes = 0;
	int min = 0, sec = 0;
	clock_t start, now, duration = 0, oldduration = 0;

	if (data[level][no].timeStorage == 0) // �÷��� �ð��� 30������ �����Ѵ�
		data[level][no].timeStorage = 30 * 60 * CLOCKS_PER_SEC; 
	start = clock(); // �������� �Ǵ� �ð�

	while (1)
	{
		// �ð� ���
		now = clock(); // ������� �ɸ� �ð�
		duration = (clock_t)(data[level][no].timeStorage - (now - start));

		sec = (int)duration / CLOCKS_PER_SEC;
		min = sec / 60;
		sec %= 60;

		if (oldduration != duration) // 1�� �������� ȭ�鿡 ���� �ð� �˸��̸� ����Ѵ�
		{
			gotoxy(51, 6); setColor(WHITE, BLACK);
			printf("%02d:%02d", min, sec);
		}

		// 30���� ����ϱ� ����, ������ �� ���߸� ������ �����Ѵ�
		if (duration >= 0)
		{
			if (cntColoringBoxes == data[level][no].cntAns && cntAnsNum == data[level][no].cntAns)
			{
				switch (level)
				{
				case FIVE: 
					if ((now - start) <= 2 * 60 * CLOCKS_PER_SEC)        // �ڡڡ� 2�� ���� Ŭ����
						data[level][no].achievement = 3;
					else if ((now - start) <= 5 * 60 * CLOCKS_PER_SEC)   // �ڡ� 5�� ���� Ŭ���� 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // �� 
					break;
				case TEN: 
					if ((now - start) <= 3.5 * 60 * CLOCKS_PER_SEC)      // �ڡڡ� 3�� 30�� ���� Ŭ����
						data[level][no].achievement = 3;
					else if ((now - start) <= 8 * 60 * CLOCKS_PER_SEC)   // �ڡ� 8�� ���� Ŭ���� 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // �� 
					break;
				case FIFTEEN: 
					if ((now - start) <= 4 * 60 * CLOCKS_PER_SEC)        // �ڡڡ� 4�� ���� Ŭ����
						data[level][no].achievement = 3;
					else if ((now - start) <= 10 * 60 * CLOCKS_PER_SEC)  // �ڡ� 10�� ���� Ŭ���� 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // �� 
					break;
				case TWENTY: 
					if ((now - start) <= 5.5 * 60 * CLOCKS_PER_SEC)      // �ڡڡ� 5�� 30�� ���� Ŭ����
						data[level][no].achievement = 3;
					else if ((now - start) <= 12.5 * 60 * CLOCKS_PER_SEC)// �ڡ� 12�� 30�� ���� Ŭ���� 
						data[level][no].achievement = 2;
					else data[level][no].achievement = 1;                // �� 
				}
				data[level][no].timeStorage = (now - start) + 1;
				gameWorks_showClearPopup(data, level, no); // Ŭ���� ȭ���� ����Ѵ�
				return CLEAR;
			}
		}
		else if (duration < 0) // 30�� ���� ������ ������ ���ߴٸ�
		{
			// ���� �����͸� �ʱ�ȭ �ϰ�
			for (row = 0; row < pictureSize; row++) 
				for (col = 0; col < pictureSize; col++)
					data[level][no].userData[row][col] = 0;
		
			return gameWorks_showGameOverPopup(data, level, no); // game over ȭ���� ����Ѵ�
		}

		oldduration = duration; // �ð��� 1�ʿ� �ѹ��� ����ϱ� ���� �۾��̴�

		// ���� ��ġ�� �迭 ��� ���� �ؼ��Ͽ� �����Ǵ� �����ڵ带 ��������� �����Ѵ�
		gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
		setColor(BLACK, BRIGHT_YELLOW);
		ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);

		// ���� ��ġ�� ���� ���� �ش��ϴ� upkey�� ��������� �����Ѵ�
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

		// ���� ��ġ�� ���� �࿡ �ش��ϴ� sidekeys�� ��������� �����Ѵ�
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
			ch = _getch(); // Ű �Է�

			if (ch == ESC) // ESC ��� ��
			{
				data[level][no].timeStorage = duration;
				return gameWorks_showPopup(data, level, no);
			}
			else if (ch == 'r' || ch == 'R') // �ʱ�ȭ ��� ��
			{
				// ���� ��ġ�� ���� ���� �ش��ϴ� upkey�� ������ �����Ѵ�
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

				// ���� ��ġ�� ���� �࿡ �ش��ϴ� sidekeys�� ������ �����Ѵ�
				for (i = 0; i < data[level][no].sideColSize; i++)
				{
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * i, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					if (data[level][no].sidekeys[row][i] == 0 && i != data[level][no].sideColSize - 1)
						fprintf(stdout, "%s", "  ");
					else if (data[level][no].sidekeys[row][i] >= 0 && data[level][no].sidekeys[row][i] <= 9)
						fprintf(stdout, "%s", changeIntegerToStr[data[level][no].sidekeys[row][i]]);
					else fprintf(stdout, "%d", data[level][no].sidekeys[row][i]);
				}

				// �÷��̾� �����͸� �ʱ�ȭ ��Ű��
				for (row = 0; row < pictureSize; row++) 
					for (col = 0; col < pictureSize; col++) 
						data[level][no].userData[row][col] = 0; 

				// ���� ���带 ����� �Ѵ�
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
			else if (ch == 'a' || ch == 'A') // ��ĥ ��� ��
			{
				if (data[level][no].userData[row][col] == 0) // �� -> ��
				{
					data[level][no].userData[row][col] = 1;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
					cntColoringBoxes++; // ��ĥ ���� ������ ������Ų��
					if (data[level][no].ansData[row][col] == 1) // �����̰�, ��ĥ�ߴٸ� cntAnsNum ������ ������Ų��
						cntAnsNum++;
				}
				else if (data[level][no].userData[row][col] == 1) // �� -> ��
				{
					data[level][no].userData[row][col] = 0;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
					cntColoringBoxes--; // ��ĥ ���� ������ ���ҽ�Ų��
					if (data[level][no].ansData[row][col] == 1) // �����̰�, ��ĥ�� ����ߴٸ� cntAnsNum ������ ���ҽ�Ų��
						cntAnsNum--; 
				}
			}
			else if (ch == 'd' || ch == 'D') // ��ǥ�� ��� ��
			{
				if (data[level][no].userData[row][col] == 2) // �� -> ��
				{
					data[level][no].userData[row][col] = 0;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
				}
				else if (data[level][no].userData[row][col] == 0) // �� -> ��
				{
					data[level][no].userData[row][col] = 2;
					gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
					ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
				}
			}
			else if (ch != UP && ch != DOWN && ch != LEFT && ch != RIGHT) continue;

			// ��ġ�̵� ��� ��
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if ((row / 5 + col / 5) % 2 == 0) setColor(BLACK, WHITE);
			else setColor(BLACK, GRAY);
			if (data[level][no].userData[row][col] == 0)fputs("��", stdout);
			else if (data[level][no].userData[row][col] == 1) fputs("��", stdout);
			else fputs("��", stdout);

			// ���� ��ġ�� ���� ���� �ش��ϴ� upkey�� ������ �����Ѵ�
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

			// ���� ��ġ�� ���� �࿡ �ش��ϴ� sidekeys�� ������ �����Ѵ�
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

// ��ü ������ �Ѱ��ϴ� �Լ�
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