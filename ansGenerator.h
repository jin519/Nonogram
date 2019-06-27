#ifndef ANS_GENERATOR_H
#define ANS_GENERATOR_H

#define ESC 0x1b

// ������ ����/���� ���θ� �����ϴ� �޴� ���
int ansGenerator_selectDeleteOrGenerateOption();

// ���Ϸκ��� �ش� ������ ��ü ���� �����͸� ����ü�� �������� �Լ�
void ansGenerator_aboutDelete_importAnsDataToStructure(Level(*data)[9], int level);

// �ش� ��ȣ�� ���� �����͸� �����ְ�, ���� ���θ� �����ϴ� �Լ� -> ������
int ansGenerator_aboutDelete_selectAndDeleteData(Level(*data)[9], int level);

// �ش� ��ȣ�� ���� ������ ����
void ansGenerator_aboutDelete_deleteData(Level(*data)[9], int level, int no);

// Ÿ��Ʋ ���
void ansGenerator_aboutGenerate_printTitle();

// ����Ű ���
void ansGenerator_aboutGenerate_printControlKeys(int level);

// board �迭�� ������ �޸𸮸� �����Ҵ��ϰ�, ���Ϸκ��� �����͸� �����ͼ� ��� ���� �ʱ�ȭ�ϴ� �Լ�
int** ansGenerator_aboutGenerate_dynamicMemoryAllocation(int level);

// ��ġ�� �ؼ��Ͽ� �ش� �����ڵ� ���� ����ϴ� �Լ�
void ansGenerator_aboutGenerate_printIntegerToUnicode(int **board, int *row, int *col);

// ���� ȭ���� ����ϴ� �Լ�
void ansGenerator_aboutGenerate_setBoard(int **board, int level);

// �����͸� ���Ͽ� �����ϴ� �Լ�
void ansGenerator_aboutGenerate_saveDataToFile(int **board, int level);

// �˾�â ��� �Լ�
int ansGenerator_aboutGenerate_showPopup(int level);

// �������� �Ҵ���� �޸𸮸� �����ϴ� �Լ�
void ansGenerator_freeMemory(int **board, int level);

// ������ ���� �Լ�
int ansGenerator_aboutGenerate_editData(int **board, int level);

// �ش� ������ ���� ������ ���������� Ž���Ͽ� ����ִ� ���� ������ ���� �����͸� �Է��ϴ� �Լ� 
void ansGenerator_aboutGenerate_generateAnswer(int **board, int level);

#endif