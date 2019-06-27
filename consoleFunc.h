#ifndef CONSOLE_FUNC_H
#define CONSOLE_FUNC_H

typedef enum {BLACK = 0, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE, GRAY, BRIGHT_BLUE, 
              BRIGHT_GREEN, BRIGHT_CYAN, BRIGHT_RED, BRIGHT_MAGENTA, BRIGHT_YELLOW, DEEP_WHITE} Color;

typedef enum {LEFT = 0x4b, RIGHT = 0X4d, UP = 0x48, DOWN = 0x50} ControlKeys;

void removeCursor(void);                 // 커서 제거 함수						 
void showCursor(void);                   // 커서 등장 함수
void gotoxy(int x, int y);               // 커서 이동 함수
void setColor(int text, int background); // 글자, 배경색 변경 함수							 
void resizeFont(int size);               // 폰트 사이즈 변경 함수							 
void clearReadBuffer();                  // 버퍼 제거 함수									 
void clearScreen();                      // 화면의 텍스트를 전부 지우는 함수

#endif
