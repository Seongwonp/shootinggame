#include "game_functions.h"
#include "player_functions.h"
#include<Windows.h> 
#include<stdio.h> 

//�÷��̾� ������
void playerdraw(int x, int y) {
    textcolor(GREEN1, BLACK);
    gotoxy(x, y);
    printf("<-��->");
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
    system("cls");
    int x = 27; // ����� �޴��� x ��ǥ
    int y = 5; // �޴��� ���� y ��ǥ
    int gap = 4; // �޴� ���� ����
    
        textcolor(RED1, BLACK);
        gotoxy(x, y++);
         printf("�����\t������\t�����");  //stg (shooting game ����)
        gotoxy(x, y++);
        printf("��      �� \t��  ");

        textcolor(YELLOW1, BLACK);
        gotoxy(x, y++);
        printf("�����\t  ��  \t��  ����");
        gotoxy(x, y++);
        printf("   ��\t  ��  \t��   ��");

        textcolor(BLUE1, BLACK);
        gotoxy(x, y++);
        printf("�����\t  ��  \t������");

        y += gap;
        textcolor(GREEN1, BLACK);
        gotoxy(x, y++);
        printf("Game Start (1)\n\n\n\n");

        textcolor(BLUE2, BLACK);
        gotoxy(x, y++);
        printf("   HELP (2)  \n\n\n\n");

        textcolor(RED2, BLACK);
        gotoxy(x, y++);
        printf("   EXIT (3)\n\n\n\n");

        textcolor(WHITE, BLACK);
        gotoxy(x-1, y + gap +3);
        printf("��ȣ�� �Է��Ͻÿ�: ");
       
}