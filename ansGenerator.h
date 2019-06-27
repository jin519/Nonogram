#ifndef ANS_GENERATOR_H
#define ANS_GENERATOR_H

#define ESC 0x1b

// 정답의 생성/삭제 여부를 선택하는 메뉴 출력
int ansGenerator_selectDeleteOrGenerateOption();

// 파일로부터 해당 라운드의 전체 정답 데이터를 구조체로 가져오는 함수
void ansGenerator_aboutDelete_importAnsDataToStructure(Level(*data)[9], int level);

// 해당 번호의 정답 데이터를 보여주고, 삭제 여부를 선택하는 함수 -> 제작중
int ansGenerator_aboutDelete_selectAndDeleteData(Level(*data)[9], int level);

// 해당 번호의 정답 데이터 삭제
void ansGenerator_aboutDelete_deleteData(Level(*data)[9], int level, int no);

// 타이틀 출력
void ansGenerator_aboutGenerate_printTitle();

// 제어키 출력
void ansGenerator_aboutGenerate_printControlKeys(int level);

// board 배열을 저장할 메모리를 동적할당하고, 파일로부터 데이터를 가져와서 요소 값을 초기화하는 함수
int** ansGenerator_aboutGenerate_dynamicMemoryAllocation(int level);

// 수치를 해석하여 해당 유니코드 값을 출력하는 함수
void ansGenerator_aboutGenerate_printIntegerToUnicode(int **board, int *row, int *col);

// 편집 화면을 출력하는 함수
void ansGenerator_aboutGenerate_setBoard(int **board, int level);

// 데이터를 파일에 저장하는 함수
void ansGenerator_aboutGenerate_saveDataToFile(int **board, int level);

// 팝업창 출력 함수
int ansGenerator_aboutGenerate_showPopup(int level);

// 동적으로 할당받은 메모리를 해제하는 함수
void ansGenerator_freeMemory(int **board, int level);

// 데이터 편집 함수
int ansGenerator_aboutGenerate_editData(int **board, int level);

// 해당 레벨의 정답 파일을 순차적으로 탐색하여 비어있는 곳에 생성한 정답 데이터를 입력하는 함수 
void ansGenerator_aboutGenerate_generateAnswer(int **board, int level);

#endif