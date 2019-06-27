#include <stdio.h>                 
#include <Windows.h> 
#include "consoleFunc.h"
#include "update.h"
#include "gameWorks.h" // 해상도: 1920*1080 환경에서 정상 작동

int main(void) 
{
	Title gameLogo;
	Level round[4][9]; // 5*5, 10*10, 15*15, 20*20
	
	setBoard_initStructure(round); // 전체 난이도의 라운드 별 데이터를 담고 있는 구조체 배열을 초기화한다

	system("title GODJIN"); // 타이틀을 GODJIN으로 변경한다
	removeCursor(); // 커서를 제거한다
	clearScreen(); // 화면 텍스트와, 배경 색상을 default로 지정한다

	startupScreen(&gameLogo); // 초기 화면을 출력한다
	gameWorks(round, &gameLogo); // 게임을 진행한다

	return 0;
}