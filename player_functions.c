#include "player_functions.h"
#include <Windows.h>
#include<stdio.h>


//������ �Լ� �����
void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);    //�ܼ� �ؽ�Ʈ�� �Ӽ��� �����ϴµ� ���
}

// Ŀ�� �����
void eraseCursor(void)
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //���� Ŀ��  ���� �ҷ����� 
    cursorInfo.bVisible = 0;  //Ŀ�� �����
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //Ŀ�� ����
}

//X,Y �̵��Լ�
void gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);  //windows.h �� ���̺귯�� �Լ�
}