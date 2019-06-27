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

char changeIntegerToStr[10][3] = { "０", "１", "２", "３", "４", "５", "６", "７", "８", "９" };

// 전체 난이도의 라운드 별 데이터를 담고 있는 구조체 배열을 초기화하는 함수
void setBoard_initStructure(Level(*data)[9])
{
	int row = 0, col = 0;

	for (row = 0; row < 4; row++) { for (col = 0; col < 9; col++)
	{
		data[row][col].ansData = NULL;  // 정답 데이터
		data[row][col].upkeys = NULL;   // upkeys
		data[row][col].sidekeys = NULL; // sidekeys
		data[row][col].upRowSize = 0;   // upkeys의 전체 행 개수
		data[row][col].sideColSize = 0; // sidekeys의 전체 열 개수 
		data[row][col].userData = NULL; // 사용자의 플레이 정보 데이터
		data[row][col].cntAns = 0;      // 색칠 면의 개수
		data[row][col].timeStorage = 0; // 남은 시간 데이터 
		data[row][col].achievement = 0; // 달성 여부
	}}
}

// 파일로부터 해당 번째 라운드의 정답 데이터를 가져오는 함수 -> 로그인 완성하고 수정할 것
void setBoard_importAnsData(Level(*data)[9], int level, int no)
{
	FILE *fp = NULL;
	int row = 0, col = 0, rd = 0, tmp = 0, pictureSize;
	pictureSize = (level + 1) * 5;

	// 파일 오픈
	fopen_s(&fp, answerFile[level][no], "rt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile[level][no]); exit(-1); }

	rd = fscanf_s(fp, "%d", &tmp); // 파일이 비어있는지 여부를 확인한다 

	// 빈 파일이 아니라면 
	if (rd == 1) 
	{
		// 그리고 레벨 번호에 해당하는 구조체 내 정답 데이터가 없다면
		if (data[level][no].ansData == NULL)
		{
			// 구조체 내 정답 데이터를 저장할 메모리를 동적으로 할당한다
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

		// 구조체 멤버 upRowSize에 upkeys 총 행의 개수 데이터 가져오기
		fscanf_s(fp, "%d", &data[level][no].upRowSize);

		// 구조체 멤버 upkeys에 upkeys 데이터 가져오기		
		data[level][no].upkeys = (int**)malloc(sizeof(int*)*data[level][no].upRowSize);
		for (row = 0; row < data[level][no].upRowSize; row++)
			data[level][no].upkeys[row] = (int*)malloc(sizeof(int)*pictureSize);
		if (data[level][no].upkeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

		for (row = 0; row < data[level][no].upRowSize; row++)
			for (col = 0; col < pictureSize; col++)
				fscanf_s(fp, "%2d", &data[level][no].upkeys[row][col]);

		// 구조체 멤버 sideColSize에 총 열의 개수 데이터 가져오기			
		fscanf_s(fp, "%d", &data[level][no].sideColSize);

		// 구조체 멤버 sidekeys에 sidekeys 데이터 가져오기
		data[level][no].sidekeys = (int**)malloc(sizeof(int*)*pictureSize);
		for (row = 0; row < pictureSize; row++)
			data[level][no].sidekeys[row] = (int*)malloc(sizeof(int)*pictureSize);
		if (data[level][no].sidekeys == NULL) { puts("Memory Allocation Failure"); exit(-1); }

		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < data[level][no].sideColSize; col++)
				fscanf_s(fp, "%2d", &data[level][no].sidekeys[row][col]);

		// 구조체 멤버 cntAns에 정답 개수 데이터 가져오기
		fscanf_s(fp, "%d", &data[level][no].cntAns);

		// 구조체 멤버 userdata 초기화   -> 추후 수정
		if (data[level][no].userData == NULL) // 유저 데이터가 없다면 
		{
			// 데이터를 저장할 메모리를 동적할당 하고
			data[level][no].userData = (int**)malloc(sizeof(int*)*pictureSize);
			for (row = 0; row < pictureSize; row++)
				data[level][no].userData[row] = (int*)malloc(sizeof(int)*pictureSize);
			if (data[level][no].userData == NULL) { puts("Memory Allocation Failure"); exit(-1); }

			// 배열 요소의 값을 0으로 초기화 한다
			for (row = 0; row < pictureSize; row++)
				for (col = 0; col < pictureSize; col++)
					data[level][no].userData[row][col] = 0;
		}
	}
	fclose(fp);
}

// 게임 보드를 출력하는 함수                       
int setBoard(Level(*data)[9], int level, int no)
{
	int row = 0, col = 0, pictureSize = (level + 1) * 5;
	
	if (data[level][no].ansData == NULL) // 게임이 없을 때
	{
		gameWorks_noFileAlertPopup(); // "게임을 제작중입니다." 알림 창 출력
		return THERE_IS_NO_GAME;
	}
	
	if (data[level][no].achievement != 0) // 클리어 한 상태에서 재도전을 하려고 들어온 경우
	{
		data[level][no].timeStorage = 30 * 60 * CLOCKS_PER_SEC; // 플레이 시간을 30분으로 제한한다
	    // 유저 데이터를 초기화 한다
		for (row = 0; row < pictureSize; row++)
			for (col = 0; col < pictureSize; col++)
				data[level][no].userData[row][col] = 0;
	}

	// 배경 출력
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

	// upkeys 출력  
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

	// sidekeys 출력
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

	// 화면 출력
	for (row = 0; row < pictureSize; row++)
		for (col = 0; col < pictureSize; col++)
		{
			gotoxy((106 - 2 * (pictureSize + data[level][no].sideColSize)) / 2 + 2 * data[level][no].sideColSize + 2 * col, (44 - (pictureSize + data[level][no].upRowSize)) / 2 + data[level][no].upRowSize + row);
			if ((row / 5 + col / 5) % 2 == 0) setColor(BLACK, WHITE);
			else setColor(BLACK, GRAY);
			ansGenerator_aboutGenerate_printIntegerToUnicode(data[level][no].userData, &row, &col);
		}

	// 제어키 출력
	setColor(WHITE, BLACK);
	gotoxy(90, 15); fputs("Ａ          Ｄ", stdout);
	gotoxy(88, 16); fputs("┏━┓      ┏━┓", stdout);
	gotoxy(88, 17); fputs("┃Ｏ┃      ┃Ｘ┃", stdout);
	gotoxy(88, 18); fputs("┗━┛      ┗━┛", stdout);
	gotoxy(94, 21); fputs("┏━┓", stdout);
	gotoxy(94, 22); fputs("┃↑┃", stdout);
	gotoxy(94, 23); fputs("┗━┛", stdout);
	gotoxy(88, 24); fputs("┏━┓┏━┓┏━┓", stdout);
	gotoxy(88, 25); fputs("┃←┃┃↓┃┃→┃", stdout);
	gotoxy(88, 26); fputs("┗━┛┗━┛┗━┛", stdout);
	gotoxy(8, 21); fputs("Ｓ", stdout); gotoxy(8, 25); fputs("Ｒ", stdout);
	gotoxy(13, 17); fputs("ESC", stdout);
	gotoxy(13, 21); fputs("SAVE", stdout);
	gotoxy(13, 25); fputs("RESET", stdout);

	return 0;
}