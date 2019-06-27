#include <Windows.h>
#include <stdio.h>
#include "consoleFunc.h"

// 커서 제거 함수
void removeCursor(void)
{ 
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 커서 등장 함수
void showCursor(void) 
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 커서 이동 함수
void gotoxy(int x, int y)
{
	COORD pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 글자, 배경색 변경 함수
void setColor(int text, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (background << 4));
}

// 폰트 사이즈 변경 함수
void resizeFont(int size) 
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = size; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

// 버퍼 제거 함수
void clearReadBuffer()
{
	fseek(stdin, 0, SEEK_END);
}

// 화면의 텍스트를 전부 지우는 함수
void clearScreen()
{
	setColor(WHITE, BLACK);
	system("cls");
}