/*
    2023-11-08 C��� �⸻ ������Ʈ ���� (���ּ� ���ð���)
    �ڵ�� ���� ��α� ���۸�, GPT�� ������ ���� �н��Ͽ��� �����Ͽ����ϴ�.
    c���α׷��� (1�й�) �̷к��� ����
    https://dongkyung.tistory.com/15 ��α� ����
    https://coding-factory.tistory.com/663 ������ ��α� ����
    https://blog.naver.com/noksek0615/221555514567 Ŀ�� ���� ��α� ����
    https://hyomyo.tistory.com/27 gotoxy���� ��α� ����
    chat GPT �� ��������

    2023-11-11 ����ȭ�� �ϼ�  
    2023-11-12 ����ȭ�� �ƽ�Ű ��Ʈ ���� �� ���߰�, ���� ȭ�� �ϼ� 
                gamestart �κ� �����߿� kbhit�� ����󿡼��� �۵����� �ʴ´�. 
                -> GetAsyncKeyState�� Ű�� ������ ������ �۵��Ϸΰ� ���� 
                ����Ű �̵� ���� (�ʳ����� �̵��� ���� ƨ�� �ݴ�� ���� ���� �߰��� ���� �Ͽ���.)
                ����Ű �̵��Ҷ� ĳ���Ͱ� ���ѻ��� ���� �߻� 
    2023-11-19 q,e �ӵ����� Ű���� �߰� 
                space �Ѿ� ����
    2023-11-25 ĳ���� �ܻ� ���� �ذ�
                �� �������� ����
                �� ������ �ܻ��� �ذ�





*/
# define _CRT_SECURE_NO_WARNINGS //����� ���� ����
#include<stdio.h>          //�⺻ ������� ���� ���̺귯��
#include<Windows.h>    //���ڻ�, ������ �ٲٱ� ���� ���̺귯��
#include<time.h>          //���ӿ� �ð��帧�� ��Ÿ���� ���� ���̺귯��
#include<stdlib.h>        // ������ �߻���Ű�� ���� ���̺귯��
#include<stdbool.h>     // ���� �ڷḦ ���� ���� ���̺귯��
#include "player_functions.h" // ������,Ŀ�� �����, x.y �̵� �Լ� 
#include "game_functions.h" //����ȭ��, helpȭ�� ��� �� �Լ�


//    Ű���� �Է°��� ���� ��������
//    ����Ű�� Ư��Ű�� ����
//    16������ ����
#define E 0x45   //�ӵ� ����
#define Q 0x51  //�ӵ� ����
#define SPACE 0x20   //�Ѿ�
#define UP 0x48    
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

int Delay = 70; //�ӵ�
int minDelay = 30; // �ּ� �ӵ�
int maxDelay = 100; // �ִ� �ӵ�


int frame_count = 0; // game ���� frame count �� �ӵ� ���������� ���ȴ�.
int p1_frame_sync = 4; //�÷��̾��� �̵��ӵ�

// �÷��̾� �̵� ��ǥ ǥ��
//���Ӹ� ����
#define WIDTH 62  
#define HEIGHT 48

#define UX 30  //���� ������ x��ǥ
#define UY 45  //���� ������ y��ǥ

int called = 0;

int oldx = UX;
int oldy = UY; // �÷��̾��� old ��ǥ
int newx = UX, newy = UY; //�÷��̾��� new ��ǥ
int keep_moving = 1;  //1:����̵�



void gamestart(); //���� ȭ�� ���
void init_game(); //������ ȭ�� �ʱ�ȭ
void playermove(unsigned char ch); //����� �����̱�




// �ӵ� ���� �Լ� (Q)
void decreaseSpeed() {
    if (Delay < maxDelay) {
        Delay += 15; // �ӵ� ����
    }
}

// �ӵ� ���� �Լ� (E)
void increaseSpeed() {
    if (Delay > minDelay) {
        Delay -= 15; // �ӵ� ����
    }
}


//����� ������ 
void playermove(unsigned char ch) {
    int move_flag = 0;
    static unsigned char last_ch = 0;
    // �̵� ������ �ִ� y ��ǥ
    int maxY = HEIGHT - 2;

    // ���� ��ġ�� ���
    int prevx = oldx;
    int prevy = oldy;

    if (called == 0) {
        eraseCursor();
        playerdraw(oldx, oldy);
        called = 1;
    }

    if (keep_moving && ch == 0)
        ch = last_ch;
    last_ch = ch;


    switch (ch) {
    case UP:
        if (oldy > 15) {  // �̵� ������ �ּ� y ��ǥ
            newy = oldy - 1;
            move_flag = 1;
        }
        break;
    case DOWN:
        if (oldy < HEIGHT - 3) {  // �̵� ������ �ִ� y ��ǥ
            newy = oldy + 1;
            move_flag = 1;
        }
        else {
            newy = oldy;
            move_flag = 0; // �Ʒ��� ���鿡 ������ ������ �÷��׸� ��Ȱ��ȭ�Ͽ� ĳ���� ���� ����
        }
        break;

    case LEFT:
        if (oldx > 2) {  // �̵� ������ �ּ� x ��ǥ
            newx = oldx - 1;
            move_flag = 1;
        }
        break;
    case RIGHT:
        if (oldx < WIDTH - 6) {  // �̵� ������ �ִ� x ��ǥ
            newx = oldx + 1;
            move_flag = 1;
        }
        break;
    }
    if (oldy >= maxY) {
        newy = prevy;
        move_flag = 0; // ������ �÷��� ��Ȱ��ȭ
    }
    if (move_flag) {
        erasePlayer(oldx, oldy);
        playerdraw(newx, newy); // ���ο� ��ġ���� �÷��̾� ǥ��
        oldx = newx; // ������ ��ġ ���
        oldy = newy;
    }

    
}

/*������ ����� �� ������ �ٽ� ���۵� ��
    ���� ������ �ʱ�ȭ����!!            */

void init_game() {
    system("cls");
    gotoxy(27, 27);
    eraseCursor();
   
}

/*///////////////////////////////////////////////////////////////////////
                             �� ���� �κ�
 //////////////////////////////////////////////////////////////////////*/

#define MAXENEMY 6

struct {
    int exist; //���� ����
    int x, y; //���� ��ǥ
    int number;
    int move;  //�̵����
    int type; //�� ���
}Enemy[MAXENEMY];

char* Enemyunit[] = { "���ڢ�","�¢Ƣ�","�͡��","�ġ��" };

//������ �̿��� �� ��ġ ����
#define MAXENEMY 6
void showenemy() {
    int i, location, direct, hieght;
    textcolor(RED1, BLACK);
    location = rand() % 2;
    direct = 5 + rand() % 55;
    hieght = 1 + rand() % 8;
    for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) {}
    if (i != MAXENEMY) {
        if (location == 1) {
            Enemy[i].x = direct;
            Enemy[i].y = hieght;
            Enemy[i].move = 1;
        }
        else {
            Enemy[i].x = direct;
            Enemy[i].y = hieght;
            Enemy[i].move = -1;
        }
        Enemy[i].type = rand() % 4;
        Enemy[i].exist = TRUE;
    }
}

void Enemymove() {
    for (int i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == TRUE) {
            // ���� ���� ���� ��ġ �����
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf("          "); // ���� ��ġ�� ���� �ִ� ������ �������� ä��

            if (Enemy[i].type == -1) {
                Enemy[i].exist = FALSE;
            }
            else {
                if (Enemy[i].x >= 3 && Enemy[i].x <= 52) {
                    Enemy[i].x += Enemy[i].move;
                }
                else {
                    Enemy[i].move *= -1;
                    Enemy[i].x += Enemy[i].move;
                }

                // ���ο� ��ġ�� �� ���
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf(Enemyunit[Enemy[i].type]);
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             �� �Ѿ� �κ�
 //////////////////////////////////////////////////////////////////////*/
#define MAXENEMYBULLET 20 // �� �ִ� �Ѿ� ��

int enemybulletuse = 1; //�� �Ѿ� 1�ʸ��� ����
int enemybullet_frame_sync = 15;  //�� �Ѿ� �ӵ�����

struct {
    int exist;
    int x, y;
}EnemyBullet[MAXENEMYBULLET];

void EnemyBulletdraw(int i) {
    textcolor(RED2, BLACK);
    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
    printf("��");
}
void EnemyBulleterase(int i) {
    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
    printf(" ");
}

void EnemyBulletMove() {
    int random;
    random = 1;
    for (int i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            EnemyBulleterase(i);
            if (EnemyBullet[i].y > HEIGHT - 3) {
                EnemyBullet[i].exist = FALSE;
            }
            else {
                if (random) {
                    if (EnemyBullet[i].x <= newx)
                        EnemyBullet[i].x++;
                    else
                        EnemyBullet[i].x--;
                }
                EnemyBullet[i].y++;
                EnemyBulletdraw(i);
            }
        }
    }
}




/*///////////////////////////////////////////////////////////////////////
                             �Ѿ� �κ�
 //////////////////////////////////////////////////////////////////////*/
 
 //�Ѿ� ���� �κ�
#define MAXBULLET 8//�÷��̾��� �ִ� �Ѿ� ��
#define TRUE 1
#define FALSE 0

struct {
    int exist;  //�Ѿ� ���翩�� ����
    int x, y;
}Bullet[MAXBULLET];

void DrawBullet(int i) {
    textcolor(GREEN1, BLACK);
    gotoxy(Bullet[i].x, Bullet[i].y); printf("��");
}

void EraseBullet(int i) {
    gotoxy(Bullet[i].x, Bullet[i].y); printf("  ");
}

void bulletmove() {
    int i;

    for (i = 0; i < MAXBULLET; i++) {
        if (Bullet[i].exist == TRUE) {
            EraseBullet(i); 
            if (Bullet[i].y == 0) {
                Bullet[i].exist = FALSE;
            }
            else { // �� ���̾ƴ϶��  �ٽ� �׸�
                Bullet[i].y--;
                DrawBullet(i);
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             Ű �Է�ó�� �κ�
 //////////////////////////////////////////////////////////////////////*/

// ����Ű �Է� ó��
void processDirectionInput(unsigned char* ch) {
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        *ch = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        *ch = DOWN;
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        *ch = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        *ch = RIGHT;
    }
}

// �ӵ� ���� �� �Ѿ� �߻� �Է� ó��
void processSpeedAndFireInput() {
    if (GetAsyncKeyState(0x51) & 0x8000) { // 'Q' Ű �Է� Ȯ��
        decreaseSpeed(); // �ӵ� ���� �Լ� ȣ��
    }
    else if (GetAsyncKeyState(0x45) & 0x8000) { // 'E' Ű �Է� Ȯ��
        increaseSpeed(); // �ӵ� ���� �Լ� ȣ��
    }
    else if (GetAsyncKeyState(0x20) & 0x8000) { // �Ѿ� �߻�
        for (int i = 0; i < MAXBULLET; i++) {

            if (Bullet[i].exist == FALSE) {
                Bullet[i].x = newx + 3;
                Bullet[i].y = newy - 1;
                Bullet[i].exist = TRUE;
                DrawBullet(i);
                break;
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             ���� ��� �κ�
 //////////////////////////////////////////////////////////////////////*/

 //����ȭ��
void gamestart(){
    
    system("cls");

    unsigned char ch;
    init_game();

    

    while (1) {

        //������, �� �Ѿ� �߻�
        showenemy();
        Enemymove();
        EnemyBulletMove();

        playermove(0);

        processDirectionInput(&ch); //����Ű
        
        // ����Ű �Է¿� ���� �÷��̾� �̵�
        if (ch != 0) {
            playermove(ch);
        }

        processSpeedAndFireInput(); //q,e,space


        bulletmove(); //�Ѿ� ������
            
        
        Sleep(Delay);
        
        frame_count++;
        }
    
}

    int main(){

        time_t seed = time(NULL);
        unsigned int seed_as_uint = (unsigned int)(seed % UINT_MAX);
        srand(seed_as_uint);

        srand(time(NULL));
        textcolor(YELLOW2, BLACK);
        eraseCursor();
        gotoxy(50, 5);
        printf("C�� �̿��� ���ð���!!");
        Sleep(2500);  //2.5�ʵ��� �۵�
        system("cls");
 
        for (int i = 0; i <= 2; i++) {
            printf("�ε��ߢ�������");
            Sleep(300);
            system("cls");
            printf("�ε��ߢ�������");
            Sleep(300);
            system("cls");
            printf("�ε��ߢ�������");
            Sleep(300);
            system("cls");
            printf("�ε��ߢ�������");
            Sleep(300);
            system("cls");
            printf("�ε��ߢ�������");
            Sleep(300);
            system("cls");
        
        }


        system("cls");
        system("mode con: cols=120 lines=30"); //MAX X : 120 MAX Y: 30
        int i;
        while (1) {
            startmenu();
            scanf("%d", &i);
            if (i == 1) {
                gamestart();
                break;
            }
            else if (i == 2) {
                help();
                system("cls");
            }
            else if (i == 3) {
                system("cls");
                gotoxy(27, 18);
                textcolor(BLACK, WHITE);
                printf("The End");
                Sleep(1500);
                textcolor(WHITE, BLACK);
                system("cls");
                break;
            }
            else {
                system("cls");
                printf("�Է� ����!\a\n\n");
                system("pause");
                system("cls");
            }
        }
        return 0;
    }