#ifndef TUTORIAL_H
#define TUTORIAL_H

// 타이틀, 조작키를 제외하고 화면의 나머지 부분을 지우는 함수
void tutorial_clearScreenExceptTitleAndButton();

// 화면에서 설명문을 지우는 함수
void tutorial_clearOnlyInstructions();

// 첫번째 페이지를 출력하는 함수
void tutorial_printFirstPage();

// 두번째 페이지를 출력하는 함수
void tutorial_printSecondPage();

// 세번째 페이지를 출력하는 함수
void tutorial_printThirdPage();

// 튜토리얼을 실행하는 함수
void tutorial_runTutorial();

#endif