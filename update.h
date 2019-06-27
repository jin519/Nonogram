#ifndef UPDATE_H
#define UPDATE_H

// 정답 데이터를 기반으로 upkeys, minUpRow를 계산하고 값이 저장된 배열의 주소를 반환하는 함수
int** update_getUpkeysFromAnsData(int **dataArr, int *minUpRow, int *level);

// 정답 데이터를 기반으로 sidekeys, minSideCol을 계산하고 값이 저장된 배열의 주소를 반환하는 함수
int** update_getSidekeysFromAnsData(int **dataArr, int *minSideCol, int *level);

// 정답 데이터를 분석하여 파일에 저장하는 함수 
void update_AnalyzeAnsDataAndSaveToFile(int **dataArr, char *answerFile, int level);

#endif