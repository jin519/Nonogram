#include <Windows.h>
#include <stdio.h>
#include "consoleFunc.h"

// Ŀ�� ���� �Լ�
void removeCursor(void)
{ 
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// Ŀ�� ���� �Լ�
void showCursor(void) 
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// Ŀ�� �̵� �Լ�
void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// ����, ���� ���� �Լ�
void setColor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}

// ��Ʈ ������ ���� �Լ�
void resizeFont(int size) 
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = size; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

// ���� ���� �Լ�
void clearReadBuffer()
{
	fseek(stdin, 0, SEEK_END);
}

// ȭ���� �ؽ�Ʈ�� ���� ����� �Լ�
void clearScreen()
{
	setColor(WHITE, BLACK);
	system("cls");
}