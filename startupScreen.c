#include <stdio.h> 
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include "startupScreen.h"
#include "consoleFunc.h"
#include "playSound.h"

extern char changeIntegerToStr[10][3];

// ���Ϸκ��� Ÿ��Ʋ �����͸� �������� �Լ� 
void startupScreen_importTitleDataFromFile(Title *data)
{
	char *fileName = "StartAnsData.txt";
	FILE *fp = NULL;
	int row = 0, col = 0;

	// ���� ����
	fopen_s(&fp, fileName, "rt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", fileName); exit(-1); }

	// ����ü ��� tutorial_ansData�� ���� ��ġ ������ ��������
	data->ansData = (int**)malloc(sizeof(int*) * 30);
	for (row = 0; row < 30; row++)
		data->ansData[row] = (int*)malloc(sizeof(int) * 30);
	if (data->ansData == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	for (row = 0; row < 30; row++)
		for (col = 0; col < 30; col++)
			fscanf_s(fp, "%d", &data->ansData[row][col]);

	// ����ü ��� upRowSize�� upkeys �� ���� ���� ������ ��������
	fscanf_s(fp, "%d", &data->upRowSize);

	// ����ü ��� upkeys�� upkeys ������ ��������		
	data->upkeys = (int**)malloc(sizeof(int*)*data->upRowSize);
	for (row = 0; row < data->upRowSize; row++)
		data->upkeys[row] = (int*)malloc(sizeof(int) * 30);
	if (data->upkeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	for (row = 0; row < data->upRowSize; row++)
		for (col = 0; col < 30; col++)
			fscanf_s(fp, "%2d", &data->upkeys[row][col]);

	// ����ü ��� sideColSize�� �� ���� ���� ������ ��������			
	fscanf_s(fp, "%d", &data->sideColSize);

	// ����ü ��� sidekeys�� sidekeys ������ ��������
	data->sidekeys = (int**)malloc(sizeof(int*) * 30);
	for (row = 0; row < 30; row++)
		data->sidekeys[row] = (int*)malloc(sizeof(int)*data->sideColSize);
	if (data->sidekeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	for (row = 0; row < 30; row++)
		for (col = 0; col < data->sideColSize; col++)
			fscanf_s(fp, "%2d", &data->sidekeys[row][col]);

	fclose(fp);
}

// upkeys ���
void startupScreen_printUpkeys(Title *data, char(*changeIntegerToStr)[3])
{
	int row = 0, col = 0;

	for (row = 0; row < data->upRowSize; row++)
	{
		gotoxy(2 * data->sideColSize + 1, row + 2);
		for (col = 0; col < 30; col++)
		{
			if (data->upkeys[row][col] == 0 && row != data->upRowSize - 1)
				fputs("  ", stdout);
			else if (data->upkeys[row][col] >= 0 && data->upkeys[row][col] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data->upkeys[row][col]]);
			else fprintf(stdout, "%d", data->upkeys[row][col]);
		}
	}
}

// sidekeys ���
void startupScreen_printSidekeys(Title *data, char(*changeIntegerToStr)[3])
{
	int row = 0, col = 0;

	for (row = 0; row < 30; row++)
	{
		gotoxy(1, data->upRowSize + 2 + row);
		for (col = 0; col < data->sideColSize; col++)
		{
			if (data->sidekeys[row][col] == 0 && col != data->sideColSize - 1)
				fputs("  ", stdout);
			else if (data->sidekeys[row][col] >= 0 && data->sidekeys[row][col] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data->sidekeys[row][col]]);
			else fprintf(stdout, "%d", data->sidekeys[row][col]);
		}
	}
}

// �����̴� Ÿ��Ʋ ���
void startupScreen_showMovingTitle(Title *data)
{
	int row, col, i, j, cnt;
	row = col = i = j = cnt = 0;

	// ���� �پ��� �׸��� ���·� ����Ѵ�
	do {
		// ��� ���
		gotoxy((2 * data->sideColSize + 1) + (2 * col), data->upRowSize + 2 + row);
		setColor(BLACK, GRAY);
		for (j = col; j < 30 - cnt; j++)
		{
			if (data->ansData[row][j] == 0) fputs("��", stdout);
			else fputs("��", stdout);
		}
		setColor(WHITE, BLACK);

		// ��, ���� ���
		for (i = row + 1; i < (30 - cnt) - 1; i++)
		{
			gotoxy((2 * data->sideColSize + 1) + (2 * col), data->upRowSize + 2 + i);
			setColor(BLACK, WHITE);
			if (data->ansData[i][col] == 0) fputs("��", stdout);
			else fputs("��", stdout);
			setColor(WHITE, BLACK);
			
			gotoxy((2 * data->sideColSize + 1) + (2 * (30 - cnt - 1)), data->upRowSize + 2 + i);
			setColor(BLACK, WHITE);
			if (data->ansData[i][(30 - cnt) - 1] == 0) fputs("��", stdout);
			else fputs("��", stdout); 
			setColor(WHITE, BLACK);
		}

		// �ϴ� ���
		gotoxy((2 * data->sideColSize + 1) + (2 * col), data->upRowSize + 2 + ((30 - cnt) - 1));
		setColor(BLACK, GRAY);
		for (j = col; j < 30 - cnt; j++)
		{
			if (data->ansData[(30 - cnt) - 1][j] == 0) fputs("��", stdout);
			else fputs("��", stdout);
		}
		setColor(WHITE, BLACK);

		Sleep(200);
		row++; col++; cnt++;
	} while (cnt != (30 + 1) / 2);
	setColor(BLACK, WHITE);
}

// X ǥ�ø� ������ ���� ���
void startupScreen_showCompleteAns(Title *data) 
{
	int row = 0, col = 0;

	for (row = 0; row < 30; row++)
	{
		gotoxy(2 * data->sideColSize + 1, data->upRowSize + 2 + row);
		for (col = 0; col < 30; col++)
		{
			if (data->ansData[row][col] == 0) fputs("  ", stdout);
			else if (row > 10 && data->ansData[row][col] == 1)
			{
				setColor(BLACK, BLACK);
				fputs("  ", stdout);
				setColor(BLACK, WHITE);
			}
			else if (data->ansData[row][col] == 1)
			{
				fputs("��", stdout);
			}
		}
	}
}

// ���� ���� �޼��� ���
void startupScreen_showStartMsg() 
{
	while (!_kbhit()) 
	{
		gotoxy(84, 25);
		setColor(WHITE, BLACK);
		fputs("Press any key to start!", stdout);
		Sleep(300);
		setColor(DEEP_WHITE, BLACK);
		gotoxy(84, 25);
		fputs("Press any key to start!", stdout);
		Sleep(300);
	}

	// ȭ�� ���� �����
	gotoxy(84, 25);
	setColor(WHITE, BLACK);
	fputs("                       ", stdout);
	_getch(); // ���� ����
}

// �ʱ� ȭ��
void startupScreen(Title *data)
{
	int row = 0, col = 0;
	
	system("mode con:cols=111 lines=41"); // �ܼ�â ũ�� ����
	resizeFont(13);                       // �۲� ũ�� 13pt
	clearScreen();

	startupScreen_importTitleDataFromFile(data);  // Ÿ��Ʋ �����͸� �������� �Լ� 
	playSound_startupScreen_repeatMainMusicPlayback();
	startupScreen_printUpkeys(data, changeIntegerToStr);   // upkeys ���
	startupScreen_printSidekeys(data, changeIntegerToStr); // sidekeys ���
	startupScreen_showMovingTitle(data);  // Ÿ��Ʋ ���
	Sleep(200);
	startupScreen_showCompleteAns(data);  // X ǥ�ø� ������ ���� ���
	startupScreen_showStartMsg();         // ���� ���� �޼��� ���
}

// �ΰ� ���
void startupScreen_showTitle(Title *data)
{
	startupScreen_printUpkeys(data, changeIntegerToStr);   // upkeys ���
	startupScreen_printSidekeys(data, changeIntegerToStr); // sidekeys ���
	setColor(BLACK, WHITE);
	startupScreen_showCompleteAns(data); // �׸� ���
}