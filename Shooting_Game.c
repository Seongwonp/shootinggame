
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

int Delay = 30; //�ӵ�
int minDelay = 20; // �ּ� �ӵ�
int maxDelay = 70; // �ִ� �ӵ�


int frame_count = 0; // game ���� frame count �� �ӵ� ���������� ���ȴ�.
int p1_frame_sync = 4; //�÷��̾��� �̵��ӵ�

// �÷��̾� �̵� ��ǥ ǥ��
//���Ӹ� ����
#define WIDTH 120  //  �ܼ� ���� ����
#define HEIGHT 30  //  �ܼ� ���� ����

#define UX (WIDTH / 2)   //���� ������ x��ǥ
#define UY (HEIGHT / 2)  //���� ������ y��ǥ

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
        if (oldx > 15) {  // �̵� ������ �ּ� x ��ǥ
            newx = oldx - 1;
            move_flag = 1;
        }
        break;
    case RIGHT:
        if (oldx < WIDTH - 30) {  // �̵� ������ �ִ� x ��ǥ
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
    int exist; // ���� ����
    int x, y; // ���� ��ǥ
    int number;
    int move;  // �̵����
    int type; // �� ���
} Enemy[MAXENEMY];

char* Enemyunit[] = { "���ڢ�", "�¢Ƣ�", "�͡��", "�ġ��", "�ߢá�", "�ݢۢ�" }; // �߰����� �� ���

// ���� �ʱ� ��ġ�� ��ġ�ϴ� �Լ�
void showenemy() {
    int i;
    int location, direct, changeDir;
    int overlap;
    textcolor(RED1, BLACK);
    for (i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == FALSE) {
            overlap = 0; // �浹 ���θ� Ȯ���ϴ� ���� �ʱ�ȭ
            location = rand() % 2;
            direct = 15 + rand() % 75; // x ��ǥ ���� ���� (15 �̻� 90 �̸�)

            if (location == 1) {
                Enemy[i].x = direct;
                Enemy[i].y = 1 + rand() % 10; // y ��ǥ ���� ���� (10 ����)


                // ���� �̵� ���� ����
                if (Enemy[i].x <= WIDTH / 2) { // ���� ȭ�� ���ʿ� ������ ���
                    Enemy[i].move = 1; // ���������� �̵�
                }
                else {
                    Enemy[i].move = -1; // �������� �̵�
                }

                // ���� ��� ���� (�����ϰ� ����)
                Enemy[i].type = rand() % 6; // 0���� 5������ �� �߿��� ���� ����

                // ������ ������ ����� ��ġ ���Ͽ� ��ġ���� Ȯ��
                for (int j = 0; j < i; j++) {
                    if (Enemy[i].x == Enemy[j].x && Enemy[i].y == Enemy[j].y) {
                        overlap = 1; // ��ġ�� ���, overlap�� 1�� ����
                        break;
                    }
                }

                // ��ġ�� �ʴ� ��ġ�� �� ����
                if (!overlap) {
                    Enemy[i].exist = TRUE;
                }
            }
        }
    }
}






void Enemymove() {
    for (int i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == TRUE) {
            // ���� ��ġ �����
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf("          "); // ���� ��ġ�� ���� �ִ� ������ �������� ä��

            // ���� �̵� ��� ����
            Enemy[i].x += Enemy[i].move;

            // ȭ�� ��迡 �����ϸ� ������ �����ϰ� ���� ��ġ�� �����ϴ� �κ�
            if (Enemy[i].x <= 20 || Enemy[i].x >= 90) {
                Enemy[i].move *= -1; // �̵� ������ �ݴ�� ����

                // ���� ȭ���� �Ѿ�� ���� �����ϰ��� �� ��, �ݴ������� �̵��ϵ��� ����
                if (Enemy[i].x <= 20) {
                    Enemy[i].x = 21 + abs(Enemy[i].move); // ȭ�� ���� ��迡 ����� �� ���� ������ �̵�
                }
                else if (Enemy[i].x >= 90) {
                    Enemy[i].x = 89 - abs(Enemy[i].move); // ȭ�� ���� ��迡 ����� �� ���� ������ �̵�
                }
            }


            // ���ο� ��ġ�� �� ���
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf(Enemyunit[Enemy[i].type]);
        }
    }
}







/*///////////////////////////////////////////////////////////////////////
                             �� �Ѿ� �κ�
 //////////////////////////////////////////////////////////////////////*/
#define MAXENEMYBULLET 100 // �� �ִ� �Ѿ� ��

int enemybulletuse = 10; //�� �Ѿ� 1�ʸ��� ����
int enemybullet_frame_sync = 10;  //�� �Ѿ� �ӵ�����

struct {
    int exist;
    int x, y;
}EnemyBullet[MAXENEMYBULLET];

void EnemyBulletshow() {
    static int frame_count = 0; // ������ ī��Ʈ ���� �߰�
    frame_count++;

    if (frame_count >= enemybullet_frame_sync) {
        frame_count = 0; // ������ ī��Ʈ �ʱ�ȭ

        for (int i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == TRUE) {
                for (int j = 0; j < enemybulletuse; j++) {
                    for (int k = 0; k < MAXENEMYBULLET; k++) {
                        if (EnemyBullet[k].exist == FALSE) {
                            EnemyBullet[k].x = Enemy[i].x + 2; // �� �Ѿ� x ��ǥ ����
                            EnemyBullet[k].y = Enemy[i].y + 1; // �� �Ѿ� y ��ǥ ����
                            EnemyBullet[k].exist = TRUE;
                            break; // �Ѿ� ���� �� �ݺ��� ����
                        }
                    }
                }
            }
        }
    }
}


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
    for (int i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            EnemyBulleterase(i);
            if (EnemyBullet[i].y > HEIGHT - 3) {
                EnemyBullet[i].exist = FALSE;
            }
            else {
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
#define MAXBULLET 6//�÷��̾��� �ִ� �Ѿ� ��
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
                             �浹 �κ�
 //////////////////////////////////////////////////////////////////////*/

int score = 0;
int heart = 3;



void Enemyfall() {
    for (int i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == FALSE || Enemy[i].type == -1) {
            continue;
        }

        for (int j = 0; j < MAXBULLET; j++) {
            if (Bullet[j].exist == FALSE) {
                continue;
            }

            if (Enemy[i].y == Bullet[j].y && abs(Enemy[i].x - Bullet[j].x) <= 3) {
                // �Ѿ� ��ġ�� ����
                gotoxy(Bullet[j].x, Bullet[j].y);
                printf("   ");
                Bullet[j].exist = FALSE;

                // ������ ������Ű�� ���� �������� ��������� ����
                score += 10;
                Enemy[i].exist = FALSE;
                Enemy[i].type = -1;

                // ȭ�鿡�� ���� �����
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf("         ");

                // ���ο� ���� ��ġ�� �� ����
                showenemy();
                break; // ���� �� ���� �� ���� �Ѿ˿��� ���� �� �ֵ���
            }
        }
    }
}


//���� ���� �Ѿ˿� �¾��� ��
void playerfall() {
    int i;
    for (i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            if (EnemyBullet[i].y == newy && abs(EnemyBullet[i].x - newx) <= 3) {
                EnemyBullet[i].exist = FALSE;
                gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
                printf("    ");
                heart--; // ��Ʈ ����
                break; //1���� ��Ʈ�� �����ϵ��� break�� �Է�

            }
        }
    }
    if (heart <= 0) {
        system("cls");
        gotoxy(27, 13);
        textcolor(BLACK, WHITE);
        printf("The End\n");
        gotoxy(27, 16);
        printf("Score: %d", score);
        Sleep(2000);
        textcolor(WHITE, BLACK);
        system("cls");
        exit(0); // ��Ʈ�� 0 ������ �� ���� ����
    }
}




void info() {
    textcolor(YELLOW2, BLACK);
    textcolor(WHITE, BLACK);
    gotoxy(100, 28); printf("����: %d", score);
    gotoxy(5, 28);
    printf("���:");
    if (heart >= 4) {
        heart = 4;
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("��������");
    }
    else if (heart == 3) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("������");
    }
    else if (heart == 2) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("����");
    }
    else if (heart == 1) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("��");
    }
    else {
        gotoxy(10, 28);
        printf("  ");
    }

}


/*///////////////////////////////////////////////////////////////////////
                             ���� ��� �κ�
 //////////////////////////////////////////////////////////////////////*/
#define WIDTH 120  // ����� �ܼ� ���� ����
#define HEIGHT 30  // ����� �ܼ� ���� ����


 //����ȭ��
void gamestart(){
    
    system("cls");

    unsigned char ch;
    init_game();

    //���� ǥ��
    info();

    while (1) {
        

        //������, �� �Ѿ� �߻�
        showenemy();
        Enemymove();

        EnemyBulletshow();
        EnemyBulletMove();

        playermove(0);

        processDirectionInput(&ch); //����Ű
        
        // ����Ű �Է¿� ���� �÷��̾� �̵�
        if (ch != 0) {
            playermove(ch);
        }

        processSpeedAndFireInput(); //q,e,space


        bulletmove(); //�Ѿ� ������
        
        // �浹 ���� �� ���� ���� ���
        Enemyfall();
        playerfall();
        
        info();
        

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
                gotoxy(27, 13);
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