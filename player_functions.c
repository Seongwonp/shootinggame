#include "player_functions.h"
#include <Windows.h>
#include<stdio.h>


//색변경 함수 만들기
void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);    //콘솔 텍스트의 속성을 설정하는데 사용
}

// 커서 숨기기
void eraseCursor(void)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //현재 커서  정보 불러오기 
    cursorInfo.bVisible = 0;  //커서 숨기기
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //커서 설정
}

//X,Y 이동함수
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  //windows.h 의 라이브러리 함수
}