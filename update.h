#ifndef UPDATE_H
#define UPDATE_H

// ���� �����͸� ������� upkeys, minUpRow�� ����ϰ� ���� ����� �迭�� �ּҸ� ��ȯ�ϴ� �Լ�
int** update_getUpkeysFromAnsData(int **dataArr, int *minUpRow, int *level);

// ���� �����͸� ������� sidekeys, minSideCol�� ����ϰ� ���� ����� �迭�� �ּҸ� ��ȯ�ϴ� �Լ�
int** update_getSidekeysFromAnsData(int **dataArr, int *minSideCol, int *level);

// ���� �����͸� �м��Ͽ� ���Ͽ� �����ϴ� �Լ� 
void update_AnalyzeAnsDataAndSaveToFile(int **dataArr, char *answerFile, int level);

#endif