#ifndef CONSOLE_FUNC_H
#define CONSOLE_FUNC_H

typedef enum {BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, GRAY, BRIGHT_BLUE, 
              BRIGHT_GREEN, BRIGHT_CYAN, BRIGHT_RED, BRIGHT_MAGENTA, BRIGHT_YELLOW, DEEP_WHITE} Color;

typedef enum {LEFT = 0x4b, RIGHT = 0X4d, UP = 0x48, DOWN = 0x50} ControlKeys;

void removeCursor(void);                 // Ŀ�� ���� �Լ�						 
void showCursor(void);                   // Ŀ�� ���� �Լ�
void gotoxy(int x, int y);               // Ŀ�� �̵� �Լ�
void setColor(int text, int background); // ����, ���� ���� �Լ�							 
void resizeFont(int size);               // ��Ʈ ������ ���� �Լ�							 
void clearReadBuffer();                  // ���� ���� �Լ�									 
void clearScreen();                      // ȭ���� �ؽ�Ʈ�� ���� ����� �Լ�

#endif
