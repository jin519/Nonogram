#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"

// 정답 데이터를 기반으로 upkeys, minUpRow를 계산하고 값이 저장된 배열의 주소를 반환하는 함수
int** update_getUpkeysFromAnsData(int **dataArr, int *minUpRow, int *level) 
{
	int **upArr = NULL, row = 0, col = 0, upRowIdx = 0, cnt = 0;

	// upArr[(pictureSize + 1) / 2][pictureSize]를 저장하기 위한 메모리 동적할당
	upArr = (int**)malloc(sizeof(int*)*((*level + 1) / 2));
	for (row = 0; row < ((*level + 1) / 2); row++) upArr[row] = (int*)malloc(sizeof(int)**level);
	if (upArr == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// 배열의 요소를 0으로 초기화
	for (row = 0; row < (*level + 1) / 2; row++) 
		for (col = 0; col < *level; col++) 
			upArr[row][col] = 0; 

	// dataArr의 하단에서 상단 방향으로 같은 열 내 연속된 1의 개수를 센다 
	for (col = 0; col < *level; col++)
	{
		upRowIdx = (*level + 1) / 2 - 1;
		cnt = 0;

		for (row = *level - 1; row >= 0; row--)
		{
			if (dataArr[row][col] == 1) cnt++;
			else if (dataArr[row][col] == 0 && cnt != 0)
			{
				*minUpRow = (upRowIdx < *minUpRow) ? upRowIdx : *minUpRow;
				upArr[upRowIdx--][col] = cnt; cnt = 0;
			}
		}
		if (cnt != 0)
		{
			*minUpRow = (upRowIdx < *minUpRow) ? upRowIdx : *minUpRow;
			upArr[upRowIdx][col] = cnt;
		}
	}

	return upArr;
}

// 정답 데이터를 기반으로 sidekeys, minSideCol을 계산하고 값이 저장된 배열의 주소를 반환하는 함수
int** update_getSidekeysFromAnsData(int **dataArr, int *minSideCol, int *level) 
{
	int **sideArr = NULL, row = 0, col = 0, sideColIdx = 0, cnt = 0;

	// sideArr[pictureSize][(pictureSize + 1) / 2]를 저장하기 위한 메모리 동적할당
	sideArr = (int**)malloc(sizeof(int*)**level); 
	for (row = 0; row < *level; row++) sideArr[row] = (int*)malloc(sizeof(int)*((*level + 1) / 2));
	if (sideArr == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// 배열의 요소를 0으로 초기화
	for (row = 0; row < *level; row++) 
		for (col = 0; col < (*level + 1) / 2; col++) 
			sideArr[row][col] = 0;

	// dataArr의 우측에서부터 좌측으로 같은 행 내 연속된 1의 개수를 센다 
	for (row = 0; row < *level; row++)
	{
		sideColIdx = (*level + 1) / 2 - 1;
		cnt = 0;

		for (col = *level - 1; col >= 0; col--)
		{
			if (dataArr[row][col] == 1) cnt++;
			else if (dataArr[row][col] == 0 && cnt != 0)
			{
				*minSideCol = (sideColIdx < *minSideCol) ? sideColIdx : *minSideCol;
				sideArr[row][sideColIdx--] = cnt; cnt = 0;
			}
		}
		if (cnt != 0)
		{
			*minSideCol = (sideColIdx < *minSideCol) ? sideColIdx : *minSideCol;
			sideArr[row][sideColIdx] = cnt;
		}
	}

	return sideArr;
}

// 정답 데이터를 분석하여 파일에 저장하는 함수 
void update_AnalyzeAnsDataAndSaveToFile(int **dataArr, char *answerFile, int pictureSize) 
{
	FILE *fp = NULL;
	int **upArr = NULL, **sideArr = NULL;
	int minUpRow, minSideCol, row = 0, col = 0, cnt = 0;
	minUpRow = minSideCol = (pictureSize + 1) / 2 - 1; 
	// minUpRow: 0이 아닌 수가 존재하는 Upkeys 배열의 최소 row값, 화면 출력시 공간 낭비를 줄이기 위해 설정했다
	// minSideCol: 0이 아닌 수가 존재하는 SideKeys 배열의 최소 col값

	upArr = update_getUpkeysFromAnsData(dataArr, &minUpRow, &pictureSize);
	sideArr = update_getSidekeysFromAnsData(dataArr, &minSideCol, &pictureSize);

	fopen_s(&fp, answerFile, "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile); exit(-1); }

	// 정답 데이터를 파일에 출력한다
	for (row = 0; row < pictureSize; row++)
	{
		for (col = 0; col < pictureSize; col++)
		{
			if (dataArr[row][col] == 1) cnt++;
			fprintf(fp, "%d ", dataArr[row][col]);
		}
		fputc('\n', fp);
	}

	// minUpRow를 고려하여 upkeys의 총 행의 개수를 출력한다
	fprintf(fp, "%d\n", (pictureSize + 1) / 2 - minUpRow);

	// upkeys 데이터를 파일에 출력하고, upArr에 할당된 메모리를 반환한다
	for (row = minUpRow; row < (pictureSize + 1) / 2; row++)
	{
		for (col = 0; col < pictureSize; col++) fprintf(fp, "%2d ", upArr[row][col]);
		fputc('\n', fp);
	}
	for (row = 0; row < (pictureSize + 1) / 2; row++) free(upArr[row]);
	free(upArr);

	// minSideCol을 고려하여 sidekeys 총 열의 개수를 출력한다
	fprintf(fp, "%d\n", (pictureSize + 1) / 2 - minSideCol);

	// sidekeys 데이터를 파일에 출력하고, sideArr에 할당된 메모리를 반환한다
	for (row = 0; row < pictureSize; row++) 
	{
		for (col = minSideCol; col < (pictureSize + 1) / 2; col++) fprintf(fp, "%2d ", sideArr[row][col]);
		if(row != pictureSize - 1) fputc('\n', fp);
	}
	for (row = 0; row < pictureSize; row++) free(sideArr[row]);
	free(sideArr);

	// 전체 정답의 수를 출력한다
	fprintf(fp, "\n%d", cnt);

	fclose(fp);
}