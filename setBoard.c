#include <stdio.h>
#include <stdlib.h>
#include "setBoard.h"
#include "consoleFunc.h"
#include "gameWorks.h"
#include "ansGenerator.h"
#include "playSound.h"

char *answerFile[4][9] = { { "ansData_5_1.txt", "ansData_5_2.txt", "ansData_5_3.txt", "ansData_5_4.txt", "ansData_5_5.txt", "ansData_5_6.txt", "ansData_5_7.txt", "ansData_5_8.txt", "ansData_5_9.txt" },
						   { "ansData_10_1.txt", "ansData_10_2.txt", "ansData_10_3.txt", "ansData_10_4.txt", "ansData_10_5.txt", "ansData_10_6.txt", "ansData_10_7.txt", "ansData_10_8.txt", "ansData_10_9.txt" },
						   { "ansData_15_1.txt", "ansData_15_2.txt", "ansData_15_3.txt", "ansData_15_4.txt", "ansData_15_5.txt", "ansData_15_6.txt", "ansData_15_7.txt", "ansData_15_8.txt", "ansData_15_9.txt" },
						   { "ansData_20_1.txt", "ansData_20_2.txt", "ansData_20_3.txt", "ansData_20_4.txt", "ansData_20_5.txt", "ansData_20_6.txt", "ansData_20_7.txt", "ansData_20_8.txt", "ansData_20_9.txt" } };

char changeIntegerToStr[10][3] = { "��", "��", "��", "��", "��", "��", "��", "��", "��", "��" };

// ��ü ���̵��� ���� �� �����͸� ��� �ִ� ����ü �迭�� �ʱ�ȭ�ϴ� �Լ�
void setBoard_initStructure(Level(*data)[9])
{
	int row = 0, col = 0;

	for (row = 0; row < 4; row++) { for (col = 0; col < 9; col++)
	{
		data[row][col].ansData = NULL;  // ���� ������
		data[row][col].upkeys = NULL;   // upkeys
		data[row][col].sidekeys = NULL; // sidekeys
		data[row][col].upRowSize = 0;   // upkeys�� ��ü �� ����
		data[row][col].sideColSize = 0; // sidekeys�� ��ü �� ���� 
		data[row][col].userData = NULL; // ������� �÷��� ���� ������
		data[row][col].cntAns = 0;      // ��ĥ ���� ����
		data[row][col].timeStorage = 0; // ���� �ð� ������ 
		data[row][col].achievement = 0; // �޼� ����
	}}
}

// ���Ϸκ��� �ش� ��° ������ ���� �����͸� �������� �Լ� -> �α��� �ϼ��ϰ� ������ ��
void setBoard_importAnsData(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	int row = 0, col = 0, rd = 0, tmp = 0, pictureSize;
	pictureSize = (level + 1) * 5;

	// ���� ����
	fopen_s(&fp, answerFile[level][no], "rt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }

	rd = fscanf_s(fp, "%d", &tmp); // ������ ����ִ��� ���θ� Ȯ���Ѵ� 

	// �� ������ �ƴ϶�� 
	if (rd == 1) 
	{
		// �׸��� ���� ��ȣ�� �ش��ϴ� ����ü �� ���� �����Ͱ� ���ٸ�
		if (data[level][no].ansData == NULL)
		{
			// ����ü �� ���� �����͸� ������ �޸𸮸� �������� �Ҵ��Ѵ�
			data[level][no].ansData = (int**)malloc(sizeof(int*)*pictureSize);
			for (row = 0; row < pictureSize; row++)
				data[level][no].ansData[row] = (int*)malloc(sizeof(int)*pictureSize);
			if (data[level][no].ansData == NULL) { puts("Memory Allocation Failure"); exit(-1); }
		}
		data[level][no].ansData[0][0] = tmp;
		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < pictureSize; col++)
			{
				if (row == 0 && col == 0) continue;
				fscanf_s(fp, "%d", &data[level][no].ansData[row][col]);
			}

		// ����ü ��� upRowSize�� upkeys �� ���� ���� ������ ��������
		fscanf_s(fp, "%d", &data[level][no].upRowSize);

		// ����ü ��� upkeys�� upkeys ������ ��������		
		data[level][no].upkeys = (int**)malloc(sizeof(int*)*data[level][no].upRowSize);
		for (row = 0; row < data[level][no].upRowSize; row++)
			data[level][no].upkeys[row] = (int*)malloc(sizeof(int)*pictureSize);
		if (data[level][no].upkeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

		for (row = 0; row < data[level][no].upRowSize; row++)
			for (col = 0; col < pictureSize; col++)
				fscanf_s(fp, "%2d", &data[level][no].upkeys[row][col]);

		// ����ü ��� sideColSize�� �� ���� ���� ������ ��������			
		fscanf_s(fp, "%d", &data[level][no].sideColSize);

		// ����ü ��� sidekeys�� sidekeys ������ ��������
		data[level][no].sidekeys = (int**)malloc(sizeof(int*)*pictureSize);
		for (row = 0; row < pictureSize; row++)
			data[level][no].sidekeys[row] = (int*)malloc(sizeof(int)*pictureSize);
		if (data[level][no].sidekeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < data[level][no].sideColSize; col++)
				fscanf_s(fp, "%2d", &data[level][no].sidekeys[row][col]);

		// ����ü ��� cntAns�� ���� ���� ������ ��������
		fscanf_s(fp, "%d", &data[level][no].cntAns);

		// ����ü ��� userdata �ʱ�ȭ   -> ���� ����
		if (data[level][no].userData == NULL) // ���� �����Ͱ� ���ٸ� 
		{
			// �����͸� ������ �޸𸮸� �����Ҵ� �ϰ�
			data[level][no].userData = (int**)malloc(sizeof(int*)*pictureSize);
			for (row = 0; row < pictureSize; row++)
				data[level][no].userData[row] = (int*)malloc(sizeof(int)*pictureSize);
			if (data[level][no].userData == NULL) { puts("Memory Allocation Failure"); exit(-1); }

			// �迭 ����� ���� 0���� �ʱ�ȭ �Ѵ�
			for (row = 0; row < pictureSize; row++)
				for (col = 0; col < pictureSize; col++)
					data[level][no].userData[row][col] = 0;
		}
	}
	fclose(fp);
}

// ���� ���带 ����ϴ� �Լ�                       
int setBoard(Level(*data)[9], int level, int no)
{
	int row = 0, col = 0, pictureSize = (level + 1) * 5;
	
	if (data[level][no].ansData == NULL) // ������ ���� ��
	{
		gameWorks_noFileAlertPopup(); // "������ �������Դϴ�." �˸� â ���
		return THERE_IS_NO_GAME;
	}
	
	if (data[level][no].achievement != 0) // Ŭ���� �� ���¿��� �絵���� �Ϸ��� ���� ���
	{
		data[level][no].timeStorage = 30 * 60 * CLOCKS_PER_SEC; // �÷��� �ð��� 30������ �����Ѵ�
	    // ���� �����͸� �ʱ�ȭ �Ѵ�
		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < pictureSize; col++)
				data[level][no].userData[row][col] = 0;
	}

	// ��� ���
	setColor(BLACK, WHITE);
	for (row = 0; row < pictureSize + data[level][no].upRowSize + 2; row++)
	{
		gotoxy((104 - 2 * (pictureSize + data[level][no].sideColSize)) / 2, (42 - (pictureSize + data[level][no].upRowSize)) / 2 + row);
		for (col = 0; col < pictureSize + data[level][no].sideColSize + 2; col++)
		{
			if (col == pictureSize + data[level][no].sideColSize + 1) fputs(" ", stdout);
			else fputs("  ", stdout);
		}
	}

	// upkeys ���  
	for (row = 0; row < data[level][no].upRowSize; row++)
		for (col = 0; col < pictureSize; col++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + row);
			if (data[level][no].upkeys[row][col] == 0 && row != data[level][no].upRowSize - 1)
				fprintf(stdout, "%s", "  ");
			else if (data[level][no].upkeys[row][col] >= 0 && data[level][no].upkeys[row][col] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data[level][no].upkeys[row][col]]);
			else
				fprintf(stdout, "%d", data[level][no].upkeys[row][col]);
		}

	// sidekeys ���
	for (row = 0; row < pictureSize; row++)
		for (col = 0; col < data[level][no].sideColSize; col++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if (data[level][no].sidekeys[row][col] == 0 && col != data[level][no].sideColSize - 1)
				fprintf(stdout, "%s", "  ");
			else if (data[level][no].sidekeys[row][col] >= 0 && data[level][no].sidekeys[row][col] <= 9)
				fprintf(stdout, "%s", changeIntegerToStr[data[level][no].sidekeys[row][col]]);
			else fprintf(stdout, "%d", data[level][no].sidekeys[row][col]);
		}

	// ȭ�� ���
	for (row = 0; row < pictureSize; row++)
		for (col = 0; col < pictureSize; col++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if ((row / 5 + col / 5) % 2 == 0) setColor(BLACK, WHITE);
			else setColor(BLACK, GRAY);
			ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
		}

	// ����Ű ���
	setColor(WHITE, BLACK);
	gotoxy(90, 15); fputs("��          ��", stdout);
	gotoxy(88, 16); fputs("������      ������", stdout);
	gotoxy(88, 17); fputs("���Ϧ�      ���ئ�", stdout);
	gotoxy(88, 18); fputs("������      ������", stdout);
	gotoxy(94, 21); fputs("������", stdout);
	gotoxy(94, 22); fputs("���覭", stdout);
	gotoxy(94, 23); fputs("������", stdout);
	gotoxy(88, 24); fputs("������������������", stdout);
	gotoxy(88, 25); fputs("���禭���馭���榭", stdout);
	gotoxy(88, 26); fputs("������������������", stdout);
	gotoxy(8, 21); fputs("��", stdout); gotoxy(8, 25); fputs("��", stdout);
	gotoxy(13, 17); fputs("ESC", stdout);
	gotoxy(13, 21); fputs("SAVE", stdout);
	gotoxy(13, 25); fputs("RESET", stdout);

	return 0;
}