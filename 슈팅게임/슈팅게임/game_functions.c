#include "game_functions.h"
#include "player_functions.h"
#include<Windows.h> 
#include<stdio.h> 

//�÷��̾� ������
void playerdraw(int x, int y) {
    textcolor(GREEN1, BLACK);
    gotoxy(x, y);
    printf("<=^=>");
}
// �����ΰ� ����� �� ��� �ݺ����� �����̴°� ó�� ǥ��
//�����
void erasePlayer(int x, int y) {
    gotoxy(x, y);
    printf("      ");
}

void help() {
    system("cls");
    printf("<<����>>\n\n");
    printf("���� �Ѿ��� ���ϸ鼭 �Ѿ��� �̿��� ������ ����ġ�ʼ�!!\n");
    printf("����� 4��!!\n\n");
    printf("<<���۹�>>\n\n");
    printf("����� : �÷��̾� �̵�\n\n");
    printf("SPACE : �Ѿ� �߻� \n\n");
    printf("Q : �ӵ� 15 ���� \n\n");
    printf("E : �ӵ� 15 ���� \n\n");
    printf("\n\n����� ���ϴ�. GOOD LUCK :)\n\n");
    system("pause");
}

void startmenu() {

    
        textcolor(RED1, BLACK);
        gotoxy(25, 5);
         printf("�����\t������\t�����");  //stg (shooting game ����)
        gotoxy(25, 6);
        printf("��    \t  ��  \t��  ");

        textcolor(YELLOW1, BLACK);
        gotoxy(25, 7);
        printf("�����\t  ��  \t��  ����");
        gotoxy(25, 8);
        printf("   ��\t  ��  \t��   ��");

        textcolor(BLUE1, BLACK);
        gotoxy(25, 9);
        printf("�����\t  ��  \t������");

        textcolor(GREEN1, BLACK);
        gotoxy(27, 14);
        printf("Game Start (1)\n\n\n\n");

        textcolor(BLUE2, BLACK);
        gotoxy(27, 18);
        printf("   HELP (2)  \n\n\n\n");

        textcolor(RED2, BLACK);
        gotoxy(27, 23);
        printf("   EXIT (3)\n\n\n\n");

        textcolor(WHITE, BLACK);
        gotoxy(26, 27);
        printf("��ȣ�� �Է��Ͻÿ�: ");
       
}