#ifndef SET_BOARD_H
#define SET_BOARD_H

#include <time.h>
typedef struct
{
	int **ansData;      // 정답 데이터
	int **upkeys;       // upkeys 
	int **sidekeys;     // sidekeys
	int upRowSize;      // upkeys의 전체 행 개수
	int sideColSize;    // sidekeys의 전체 열 개수 
	int **userData;     // 사용자의 플레이 정보 데이터  
	int cntAns;         // 색칠 면의 개수 
	int achievement;    // 달성 여부 (미달성: 0, 하: 1, 중: 2, 상: 3)
	time_t timeStorage; // 남은 시간 데이터 -> 평점을 계산하는 척도
}Level;

#define THERE_IS_NO_GAME -1

// 전체 난이도의 라운드 별 데이터를 담고 있는 구조체 배열을 초기화하는 함수
void setBoard_initStructure(Level(*data)[9]);

// 파일로부터 해당 번째 라운드의 정답 데이터를 가져오는 함수 
void setBoard_importAnsData(Level(*data)[9], int level, int no);

// 게임 보드를 출력하는 함수                       
int setBoard(Level(*data)[9], int level, int no);

#endif