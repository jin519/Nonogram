#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "update.h"

// ���� �����͸� ������� upkeys, minUpRow�� ����ϰ� ���� ����� �迭�� �ּҸ� ��ȯ�ϴ� �Լ�
int** update_getUpkeysFromAnsData(int **dataArr, int *minUpRow, int *level) 
{
	int **upArr = NULL, row = 0, col = 0, upRowIdx = 0, cnt = 0;

	// upArr[(pictureSize + 1) / 2][pictureSize]�� �����ϱ� ���� �޸� �����Ҵ�
	upArr = (int**)malloc(sizeof(int*)*((*level + 1) / 2));
	for (row = 0; row < ((*level + 1) / 2); row++) upArr[row] = (int*)malloc(sizeof(int)**level);
	if (upArr == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// �迭�� ��Ҹ� 0���� �ʱ�ȭ
	for (row = 0; row < (*level + 1) / 2; row++) 
		for (col = 0; col < *level; col++) 
			upArr[row][col] = 0; 

	// dataArr�� �ϴܿ��� ��� �������� ���� �� �� ���ӵ� 1�� ������ ���� 
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

// ���� �����͸� ������� sidekeys, minSideCol�� ����ϰ� ���� ����� �迭�� �ּҸ� ��ȯ�ϴ� �Լ�
int** update_getSidekeysFromAnsData(int **dataArr, int *minSideCol, int *level) 
{
	int **sideArr = NULL, row = 0, col = 0, sideColIdx = 0, cnt = 0;

	// sideArr[pictureSize][(pictureSize + 1) / 2]�� �����ϱ� ���� �޸� �����Ҵ�
	sideArr = (int**)malloc(sizeof(int*)**level); 
	for (row = 0; row < *level; row++) sideArr[row] = (int*)malloc(sizeof(int)*((*level + 1) / 2));
	if (sideArr == NULL) { puts("Memory Allocation Failure"); exit(-1); }

	// �迭�� ��Ҹ� 0���� �ʱ�ȭ
	for (row = 0; row < *level; row++) 
		for (col = 0; col < (*level + 1) / 2; col++) 
			sideArr[row][col] = 0;

	// dataArr�� ������������ �������� ���� �� �� ���ӵ� 1�� ������ ���� 
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

// ���� �����͸� �м��Ͽ� ���Ͽ� �����ϴ� �Լ� 
void update_AnalyzeAnsDataAndSaveToFile(int **dataArr, char *answerFile, int pictureSize) 
{
	FILE *fp = NULL;
	int **upArr = NULL, **sideArr = NULL;
	int minUpRow, minSideCol, row = 0, col = 0, cnt = 0;
	minUpRow = minSideCol = (pictureSize + 1) / 2 - 1; 
	// minUpRow: 0�� �ƴ� ���� �����ϴ� Upkeys �迭�� �ּ� row��, ȭ�� ��½� ���� ���� ���̱� ���� �����ߴ�
	// minSideCol: 0�� �ƴ� ���� �����ϴ� SideKeys �迭�� �ּ� col��

	upArr = update_getUpkeysFromAnsData(dataArr, &minUpRow, &pictureSize);
	sideArr = update_getSidekeysFromAnsData(dataArr, &minSideCol, &pictureSize);

	fopen_s(&fp, answerFile, "wt");
	if (fp == NULL) { printf("\"%s\" Load Failed\n", answerFile); exit(-1); }

	// ���� �����͸� ���Ͽ� ����Ѵ�
	for (row = 0; row < pictureSize; row++)
	{
		for (col = 0; col < pictureSize; col++)
		{
			if (dataArr[row][col] == 1) cnt++;
			fprintf(fp, "%d ", dataArr[row][col]);
		}
		fputc('\n', fp);
	}

	// minUpRow�� ����Ͽ� upkeys�� �� ���� ������ ����Ѵ�
	fprintf(fp, "%d\n", (pictureSize + 1) / 2 - minUpRow);

	// upkeys �����͸� ���Ͽ� ����ϰ�, upArr�� �Ҵ�� �޸𸮸� ��ȯ�Ѵ�
	for (row = minUpRow; row < (pictureSize + 1) / 2; row++)
	{
		for (col = 0; col < pictureSize; col++) fprintf(fp, "%2d ", upArr[row][col]);
		fputc('\n', fp);
	}
	for (row = 0; row < (pictureSize + 1) / 2; row++) free(upArr[row]);
	free(upArr);

	// minSideCol�� ����Ͽ� sidekeys �� ���� ������ ����Ѵ�
	fprintf(fp, "%d\n", (pictureSize + 1) / 2 - minSideCol);

	// sidekeys �����͸� ���Ͽ� ����ϰ�, sideArr�� �Ҵ�� �޸𸮸� ��ȯ�Ѵ�
	for (row = 0; row < pictureSize; row++) 
	{
		for (col = minSideCol; col < (pictureSize + 1) / 2; col++) fprintf(fp, "%2d ", sideArr[row][col]);
		if(row != pictureSize - 1) fputc('\n', fp);
	}
	for (row = 0; row < pictureSize; row++) free(sideArr[row]);
	free(sideArr);

	// ��ü ������ ���� ����Ѵ�
	fprintf(fp, "\n%d", cnt);

	fclose(fp);
}