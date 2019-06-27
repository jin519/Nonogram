#ifndef SET_BOARD_H
#define SET_BOARD_H

#include <time.h>
typedef struct
{
	int **ansData;      // ���� ������
	int **upkeys;       // upkeys 
	int **sidekeys;     // sidekeys
	int upRowSize;      // upkeys�� ��ü �� ����
	int sideColSize;    // sidekeys�� ��ü �� ���� 
	int **userData;     // ������� �÷��� ���� ������  
	int cntAns;         // ��ĥ ���� ���� 
	int achievement;    // �޼� ���� (�̴޼�: 0, ��: 1, ��: 2, ��: 3)
	time_t timeStorage; // ���� �ð� ������ -> ������ ����ϴ� ô��
}Level;

#define THERE_IS_NO_GAME -1

// ��ü ���̵��� ���� �� �����͸� ��� �ִ� ����ü �迭�� �ʱ�ȭ�ϴ� �Լ�
void setBoard_initStructure(Level(*data)[9]);

// ���Ϸκ��� �ش� ��° ������ ���� �����͸� �������� �Լ� 
void setBoard_importAnsData(Level(*data)[9], int level, int no);

// ���� ���带 ����ϴ� �Լ�                       
int setBoard(Level(*data)[9], int level, int no);

#endif