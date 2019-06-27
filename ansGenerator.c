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

char numberInString[9][5][11] = { { "    ��    ", "  ���    ", "    ��    ", "    ��    ", "  ����  " },  // 1
								  { "  ����  ", "      ��  ", "  ����  ", "  ��      ", "  ����  " },     // 2
								  { "  ����  ", "      ��  ", "  ����  ", "      ��  ", "  ����  " },     // 3
								  { "  ��  ��  ", "  ��  ��  ", "  ����  ", "      ��  ", "      ��  " },   // 4
								  { "  ����  ", "  ��      ", "  ����  ", "      ��  ", "  ����  " },     // 5
								  { "  ����  ", "  ��      ", "  ����  ", "  ��  ��  ", "  ����  " },      // 6
								  { "  ����  ", "  ��  ��  ", "  ��  ��  ", "      ��  ", "      ��  " },   // 7
								  { "  ����  ", "  ��  ��  ", "  ����  ", "  ��  ��  ", "  ����  " },       // 8
								  { "  ����  ", "  ��  ��  ", "  ����  ", "      ��  ", "  ����  " } };    // 9

char *editorFile[4] = { "editorData_5.txt", "editorData_10.txt", "editorData_15.txt", "editorData_20.txt" };

// �������� �Ҵ���� �޸𸮸� �����ϴ� �Լ�
void ansGenerator_freeMemory(int **board, int level)
{
	int row = 0;
	level = (level + 1) * 5;

	for (row = 0; row < level; row++) free(board[row]);
	free(board);
}

// ������ ����/���� ���θ� �����ϴ� �޴� ���
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
		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��

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

	// ȭ�� ���� �����
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

// ���Ϸκ��� �ش� ������ ��ü ���� �����͸� ����ü�� �������� �Լ�
void ansGenerator_aboutDelete_importAnsDataToStructure(Level(*data)[9], int level) 
{
	FILE *fp = NULL;
	int pictureSize = (level + 1) * 5;
	int i = 0, row = 0, col = 0, rd = 0, tmp = 0;

	for (i = 0; i < 9; i++)
	{
		fopen_s(&fp, answerFile[level][i], "rt");
		if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][i]); exit(-1); }

		rd = fscanf_s(fp, "%d", &tmp); // ������ ����ִ��� ���θ� Ȯ���Ѵ� 
		if (rd == 1) // ������� �ʴٸ�
		{
			// �ش� ��ȣ�� ����ü �迭 ��ҿ� ���� �����͸� �־��ش� 
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

// �ش� ��ȣ�� ���� �����͸� �����ְ�, ���� ���θ� �����ϴ� �Լ� -> ���� �ʿ�(ù���� �׸� ���� �� ���α׷� ����)
int ansGenerator_aboutDelete_selectAndDeleteData(Level(*data)[9], int level)
{
	char ch = '\0';
	int row = 0, col = 0, tmp = 0, i = 0;
	int pictureSize = (level + 1) * 5, xPos, backgroundSize;
	if (level % 2) { xPos = 13; backgroundSize = 22; }
	else { xPos = 14; backgroundSize = 21; }

	ansGenerator_aboutDelete_importAnsDataToStructure(data, level); // ���Ϸκ��� �ش� ������ ��ü ���� �����͸� ����ü�� �����´�

    // ESC ��ư ���
	gotoxy(73 + backgroundSize, 17 + backgroundSize); fputs("ESC", stdout);

	// ��ư ���
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

	// ���� ȭ�� ��� ��� 
	setColor(WHITE, GRAY);
	for (row = 0; row < backgroundSize; row++)
	{
		gotoxy(xPos + 41, 16 + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
	}

	// ���� ȭ�� ���
	setColor(WHITE, WHITE);
	for (row = 0; row < pictureSize; row++)
		for (col = 0; col < pictureSize; col++)
		{
			gotoxy(xPos + 41 + (backgroundSize - pictureSize) + 2 * col, 16 + (backgroundSize - pictureSize) / 2 + row);
			if (data[level][0].ansData[row][col]) { setColor(WHITE, BLACK); fputs("  ", stdout); setColor(WHITE, WHITE); }
			else fputs("  ", stdout);
		}

	// ��ư ����
	row = 0; 
	while (1)
	{
		tmp = row / 3;
		ch = _getch();
		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��
		else if (ch == ESC) { return -1; }

		// ����Ű �Է� ��
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

// �ش� ��ȣ�� ���� ������ ���� -> ������ �ִ� ��
void ansGenerator_aboutDelete_deleteData(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	int i = 0, pictureSize = (level + 1) * 5;

	// ����ü �� ���� �����͸� �Ҹ��Ų��
	if (data[level][no].ansData != NULL) // ���� �����Ͱ� �����Ѵٸ�
	{
		ansGenerator_freeMemory(data[level][no].ansData, level);
		data[level][no].ansData = NULL;
	}

	// ���� ������ �����ϰ� �����͸� �Ҹ��Ų��
	fopen_s(&fp, answerFile[level][no], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }
	fputs("", stdout);
	fclose(fp);

	// ��ŷ ������ �����ϰ� �����͸� �Ҹ��Ų��
	fopen_s(&fp, rankFile[level][no], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }
	fputs("", stdout);
	fclose(fp);
}

// Ÿ��Ʋ ���
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

// ����Ű ���
void ansGenerator_aboutGenerate_printControlKeys(int level) 
{
	int xPos1, xPos2, xPos3;
	if (level % 2 == 0) { xPos1 = 12; xPos2 = 17; xPos3 = 19; } // 5*5, 15*15
	else { xPos1 = 10; xPos2 = 15; xPos3 = 17; } // 10*10, 20*20

	gotoxy(xPos1, 4); fputs("ESC", stdout);
	gotoxy(xPos2, 33); fputs("��������������������������������", stdout);
	gotoxy(xPos2, 34); fputs("���Ϧ����ӣ��֣Ŧ����ңţӣţԦ�", stdout);
	gotoxy(xPos2, 35); fputs("��������������������������������", stdout);
	gotoxy(xPos3, 37); fputs("��       ��           ��", stdout);
	gotoxy(78, 33); fputs("������", stdout);
	gotoxy(72, 34); fputs("���覭", stdout);
	gotoxy(78, 35); fputs("������", stdout);
	gotoxy(72, 36); fputs("������������������", stdout);
	gotoxy(72, 37); fputs("���禭���馭���榭", stdout);
	gotoxy(72, 38); fputs("������������������", stdout);
}

// board �迭�� ������ �޸𸮸� �����Ҵ��ϰ�, ���Ϸκ��� �����͸� �����ͼ� ��� ���� �ʱ�ȭ�ϴ� �Լ�
int** ansGenerator_aboutGenerate_dynamicMemoryAllocation(int level) 
{
	FILE *fp = NULL;
	int **board = NULL;
	int row = 0, col = 0, rd = 0, pictureSize;
	pictureSize = (level + 1) * 5;
	
	// �޸� �����Ҵ�
	board = (int**)malloc(sizeof(int*)*pictureSize);
	for (row = 0; row < pictureSize; row++) board[row] = (int*)malloc(sizeof(int)*pictureSize);
	if (board == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// ���� ����
	fopen_s(&fp, editorFile[level], "rt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", editorFile[level]); exit(-1); }

	// ���Ϸκ��� �����͸� �����´�
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

	// ������ ����ִٸ� ��� ��Ҹ� 0���� �ʱ�ȭ�Ѵ�
	if (rd == EOF)
	{
		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < pictureSize; col++)
				board[row][col] = 0;
	}

	fclose(fp); // ������ �ݰ�
	return board; // board �ּҸ� ��ȯ�Ѵ�
}

// ��ġ�� �ؼ��Ͽ� �ش� �����ڵ� ���� ����ϴ� �Լ�
void ansGenerator_aboutGenerate_printIntegerToUnicode(int **board, int *row, int *col)
{
	if (board[*row][*col] == 0) fputs("��", stdout);      // �� : 0  
	else if (board[*row][*col] == 1) fputs("��", stdout); // �� : 1
	else fputs("��", stdout);                            // �� : 2
}

// ���� ȭ���� ����ϴ� �Լ�
void ansGenerator_aboutGenerate_setBoard(int **board, int level)
{
	int row = 0, col = 0, x, y, backgroundSize;
	if (level % 2) { x = 10; y = 9; backgroundSize = 22; }
	else { x = 12; y = 9; backgroundSize = 21; }

	system("cls");
	ansGenerator_aboutGenerate_printControlKeys(level); // ����Ű ���
	ansGenerator_aboutGenerate_printTitle(); // Ÿ��Ʋ ���
	
	// background ���
	setColor(WHITE, GRAY);
	for (row = 0; row < backgroundSize; row++)
	{
		gotoxy(x, y + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
		gotoxy(x + 2 * backgroundSize + 5, y + row);
		for (col = 0; col < backgroundSize; col++) fputs("  ", stdout);
	}

	level = (level + 1) * 5;

	// board ���
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

// �����͸� ���Ͽ� �����ϴ� �Լ�
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

// �˾�â ��� �Լ�
int ansGenerator_aboutGenerate_showPopup(int level) 
{
	int row = 0, col = 0, x, y, backgroundSize, gapX, gapY;
	char ch = '\0';
	char *menu[3] = { "     Previous Page     ", 
		              "    Generate Answer    ", 
		              "   Back To Main Menu   " };

	if (level % 2) { x = 12; y = 9; backgroundSize = 21; gapX = 3; gapY = 11; }
	else { x = 10; y = 9; backgroundSize = 22; gapX = 4; gapY = 12; }

	// �⺻ Ʋ ���
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
	gotoxy(x + 4 * backgroundSize + 1, y + 1); setColor(BLACK, WHITE); fputs("��", stdout);

	// �ɼ� ��ư ����
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
	
	// �ɼ� ����
	col = 0;
	while (1) 
	{
		ch = _getch(); // Ű �Է�

		if (ch == 13 || ch == ' ') break; // enter, spacebar �Է� �� �ݺ� Ż��
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

// ������ ���� �Լ� 
int ansGenerator_aboutGenerate_editData(int **board, int level)
{
	char ch = '\0';
	int row = 0, col = 0, x, y, backgroundSize, pictureSize;
	if (level % 2) { x = 10; y = 9; backgroundSize = 22; } // 10*10, 20*20
	else { x = 12; y = 9; backgroundSize = 21; } // 5*5, 15*15
	pictureSize = (level + 1) * 5;

	while (1) 
	{
		// �迭 ����� ���� �ؼ��Ͽ� �����Ǵ� �����ڵ� ���
		gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
		setColor(BRIGHT_YELLOW, BLACK);
		ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);  

		ch = _getch(); // Ű �Է�
		if (ch == ESC) // ESC �Է� �� 
			return ansGenerator_aboutGenerate_showPopup(pictureSize);
		else if (ch == 'r' || ch == 'R') // �ʱ�ȭ ��� �� 
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
		else if (ch == 's' || ch == 'S') // ���� ��� �� 
			ansGenerator_aboutGenerate_saveDataToFile(board, level);
		else if (ch == 'a' || ch == 'A') // ��ĥ ��� ��
		{
			if (board[row][col] == 0) // �� -> ��
			{
				board[row][col] = 1;
				gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("��", stdout);
				setColor(WHITE, WHITE);
				gotoxy(x + backgroundSize - pictureSize + 2 * backgroundSize + 5 + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("  ", stdout);
			}
			else if (board[row][col] == 1) // �� -> ��
			{
				board[row][col] = 0; 
				gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("��", stdout);
				setColor(WHITE, BLACK);
				gotoxy(x + backgroundSize - pictureSize + 2 * backgroundSize + 5 + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
				fputs("  ", stdout);
			}
		}
		else if (ch != 0x48 && ch != 0x50 && ch != 0x4b && ch != 0X4d) continue;

		// ��ġ�̵� ��� ��
		setColor(WHITE, BLACK);
		gotoxy(x + (backgroundSize - pictureSize) + (2 * col), y + row + (backgroundSize - pictureSize) / 2);
		
		switch (ch)
		{
		case 0x48: // ����� Ű
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			row--; break;
		case 0x50: // �Ϲ��� Ű
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			row++; break;
		case 0x4b: // �¹��� Ű
			ansGenerator_aboutGenerate_printIntegerToUnicode(board, &row, &col);
			col--; break;
		case 0X4d: // ����� Ű
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

// �ش� ������ ���� ������ ���������� Ž���Ͽ� ����ִ� ���� ������ ���� �����͸� �Է��ϴ� �Լ� -> ������ ������ض�� �����ִ� �� �����
void ansGenerator_aboutGenerate_generateAnswer(int **board, int level) 
{
	FILE *fp = NULL;
	int row = 0, col = 0, no = 1, tmp = 0, pictureSize;
	pictureSize = (level + 1) * 5;

	for (row = 0; row < 9; row++) 
	{
		// �ش� ������ ���� ���ϵ��� ���������� �����Ѵ� 
		fopen_s(&fp, answerFile[level][row], "rt"); 
		if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][row]); exit(-1); }

		if (fscanf_s(fp, "%d", &tmp) != EOF) { fclose(fp); continue; } // �� ������ �ƴ϶��
		else 
		{ // ������ ���� �����͸� �м��Ͽ� ������ ���� �Է��Ѵ�
			fclose(fp);
			update_AnalyzeAnsDataAndSaveToFile(board, answerFile[level][row], pictureSize);
			break;
		}
	}

	// �ش� ������ ������ ������ �ʱ�ȭ �Ѵ�
	fopen_s(&fp, editorFile[level], "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", editorFile[level]); exit(-1); }
	fputs("", fp);

	fclose(fp);
}