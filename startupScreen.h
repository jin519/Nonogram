#ifndef START_UP_SCREEN_H
#define START_UP_SCREEN_H

typedef struct
{
	int **ansData;      // ��ġȭ�� ���� ������
	int **upkeys;       // upkeys 
	int **sidekeys;     // sidekeys
	int upRowSize;      // upkeys�� ��ü �� ����
	int sideColSize;    // sidekeys�� ��ü �� ���� 
}Title;

// ���Ϸκ��� Ÿ��Ʋ �����͸� �������� �Լ� 
void startupScreen_importTitleDataFromFile(Title *data);

// upkeys ���
void startupScreen_printUpkeys(Title *data, char(*changeIntegerToStr)[3]);

// sidekeys ���
void startupScreen_printSidekeys(Title *data, char(*changeIntegerToStr)[3]);

// �����̴� Ÿ��Ʋ ���
void startupScreen_showMovingTitle(Title *data);

// X ǥ�ø� ������ ���� ���
void startupScreen_showCompleteAns(Title *data);

// ���� ���� �޼��� ���
void startupScreen_showStartMsg();

// �ʱ� ȭ��
void startupScreen(Title *data);

// �ΰ� ���
void startupScreen_showTitle(Title *data);

#endif