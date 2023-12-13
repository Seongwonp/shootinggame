#include "game_functions.h"
#include "player_functions.h"
#include<Windows.h> 
#include<stdio.h> 

//플레이어 디자인
void playerdraw(int x, int y) {
    textcolor(GREEN1, BLACK);
    gotoxy(x, y);
    printf("<-○->");
}
// 디자인과 지우기 를 계속 반복시켜 움직이는것 처럼 표시
//지우기
void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("      ");
}

void help() {
    system("cls");
    printf("<<도움말>>\n\n");
    printf("적의 총알을 피하면서 총알을 이용해 적들을 물리치십쇼!!\n");
    printf("목숨은 4개!!\n\n");
    printf("<<조작법>>\n\n");
    printf("←↑→↓ : 플레이어 이동\n\n");
    printf("SPACE : 총알 발사 \n\n");
    printf("Q : 속도 15 감소 \n\n");
    printf("E : 속도 15 증가 \n\n");
    printf("\n\n행운을 빕니다. GOOD LUCK :)\n\n");
    system("pause");
}

void startmenu() {
    system("cls");

    printf("\n");
    textcolor(RED1, BLACK);
            printf("\t\t\t★==================================================★\n");
            printf("\t\t\t|  ●●●   ●   ●  ●●●   ●●●  ●●●●●  ●●●  ●   ●  ●●●  |\n");
            printf("\t\t\t| ●      ●   ● ●   ● ●   ●   ●     ●   ●●  ● ●     |\n");
    textcolor(YELLOW1, BLACK);
            printf("\t\t\t|  ●●●   ●●●●● ●   ● ●   ●   ●     ●   ● ● ● ●  ●● |\n");
            printf("\t\t\t|     ●  ●   ● ●   ● ●   ●   ●     ●   ●  ●● ●   ● |\n");
            printf("\t\t\t|  ●●●   ●   ●  ●●●   ●●●    ●    ●●●  ●   ●  ●●●● |\n");
    textcolor(GREEN1, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|\t      ●●●    ●   ●   ●  ●●●●●      \t   |\n");
            printf("\t\t\t|\t     ●      ● ●  ●● ●●  ●           \t   |\n");
   textcolor(BLUE2, BLACK);
            printf("\t\t\t|\t     ●  ●● ●●●●● ● ● ●  ●●●●      \t   |\n");
            printf("\t\t\t|\t     ●   ● ●   ● ●   ●  ●           \t   |\n");
            printf("\t\t\t|\t      ●●●  ●   ● ●   ●  ●●●●●       \t   |\n");
   textcolor(MAGENTA1, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|--------------------------------------------------|\n");
            printf("\t\t\t|                                                  |\n");
   textcolor(GREEN2, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|\t\t   Game Start (1)\t\t   |\n");
            printf("\t\t\t|                                                  |\n");
   textcolor(YELLOW1, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|\t\t      HELP (2)\t\t\t   |\n");
            printf("\t\t\t|                                                  |\n");
   textcolor(RED2, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|\t\t      EXIT (3)\t\t\t   |\n");
   textcolor(RED1, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t★==================================================★\n");
        textcolor(WHITE, BLACK);
        printf("\t\t\t번호를 입력하시오: ");
}