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

    printf("\n");
    textcolor(RED1, BLACK);
            printf("\t\t\t��==================================================��\n");
            printf("\t\t\t|  �ܡܡ�   ��   ��  �ܡܡ�   �ܡܡ�  �ܡܡܡܡ�  �ܡܡ�  ��   ��  �ܡܡ�  |\n");
            printf("\t\t\t| ��      ��   �� ��   �� ��   ��   ��     ��   �ܡ�  �� ��     |\n");
    textcolor(YELLOW1, BLACK);
            printf("\t\t\t|  �ܡܡ�   �ܡܡܡܡ� ��   �� ��   ��   ��     ��   �� �� �� ��  �ܡ� |\n");
            printf("\t\t\t|     ��  ��   �� ��   �� ��   ��   ��     ��   ��  �ܡ� ��   �� |\n");
            printf("\t\t\t|  �ܡܡ�   ��   ��  �ܡܡ�   �ܡܡ�    ��    �ܡܡ�  ��   ��  �ܡܡܡ� |\n");
    textcolor(GREEN1, BLACK);
            printf("\t\t\t|                                                  |\n");
            printf("\t\t\t|\t      �ܡܡ�    ��   ��   ��  �ܡܡܡܡ�      \t   |\n");
            printf("\t\t\t|\t     ��      �� ��  �ܡ� �ܡ�  ��           \t   |\n");
   textcolor(BLUE2, BLACK);
            printf("\t\t\t|\t     ��  �ܡ� �ܡܡܡܡ� �� �� ��  �ܡܡܡ�      \t   |\n");
            printf("\t\t\t|\t     ��   �� ��   �� ��   ��  ��           \t   |\n");
            printf("\t\t\t|\t      �ܡܡ�  ��   �� ��   ��  �ܡܡܡܡ�       \t   |\n");
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
            printf("\t\t\t��==================================================��\n");
        textcolor(WHITE, BLACK);
        printf("\t\t\t��ȣ�� �Է��Ͻÿ�: ");
}