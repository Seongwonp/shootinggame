/*
    2023-11-08 C언어 기말 프로젝트 시작 (우주선 슈팅게임)
    코드는 여러 블로그 구글링, GPT의 도움을 통해 학습하여서 제작하였습니다.
    c프로그래밍 (1분반) 이론보고서 참조
    https://dongkyung.tistory.com/15 블로그 참조
    https://coding-factory.tistory.com/663 색정의 블로그 참조
    https://blog.naver.com/noksek0615/221555514567 커서 설정 블로그 참조
    https://hyomyo.tistory.com/27 gotoxy정의 블로그 참조
    chat GPT 로 오류수정

    2023-11-11 시작화면 완성  
    2023-11-12 시작화면 아스키 아트 수정 및 색추가, 도움말 화면 완성 
                gamestart 부분 수정중에 kbhit이 비쥬얼에서는 작동하지 않는다. 
                -> GetAsyncKeyState로 키를 누르고 있을때 작동하로고 설정 
                방향키 이동 구현 (맵끝까지 이동시 벽에 튕겨 반대로 가는 것을 추가로 구현 하였다.)
                방향키 이동할때 캐릭터가 무한생성 오류 발생 
    2023-11-19 q,e 속도조절 키워드 추가 
                space 총알 구현
    2023-11-25 캐릭터 잔상 조금 해결
                적 랜덤생성 구현
                적 생성후 잔상문제 해결





*/
# define _CRT_SECURE_NO_WARNINGS //비쥬얼 오류 무시
#include<stdio.h>          //기본 입출력을 위한 라이브러리
#include<Windows.h>    //글자색, 배경색을 바꾸기 위한 라이브러리
#include<time.h>          //게임에 시간흐름을 나타내기 위한 라이브러리
#include<stdlib.h>        // 난수를 발생시키기 위한 라이브러리
#include<stdbool.h>     // 논리형 자료를 쓰기 위한 라이브러리
#include "player_functions.h" // 색변경,커서 숨기기, x.y 이동 함수 
#include "game_functions.h" //시작화면, help화면 출력 등 함수


//    키보드 입력값을 위한 전역변수
//    방향키도 특수키로 간주
//    16진수로 선언
#define E 0x45   //속도 증가
#define Q 0x51  //속도 감소
#define SPACE 0x20   //총알
#define UP 0x48    
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

int Delay = 70; //속도
int minDelay = 30; // 최소 속도
int maxDelay = 100; // 최대 속도


int frame_count = 0; // game 진행 frame count 로 속도 조절용으로 사용된다.
int p1_frame_sync = 4; //플레이어의 이동속도

// 플레이어 이동 좌표 표시
//게임맵 넓이
#define WIDTH 62  
#define HEIGHT 48

#define UX 30  //시작 유저의 x좌표
#define UY 45  //시작 유저의 y좌표

int called = 0;

int oldx = UX;
int oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int keep_moving = 1;  //1:계속이동



void gamestart(); //게임 화면 출력
void init_game(); //종료후 화면 초기화
void playermove(unsigned char ch); //사용자 움직이기




// 속도 감소 함수 (Q)
void decreaseSpeed() {
    if (Delay < maxDelay) {
        Delay += 15; // 속도 감소
    }
}

// 속도 증가 함수 (E)
void increaseSpeed() {
    if (Delay > minDelay) {
        Delay -= 15; // 속도 증가
    }
}


//사용자 움직임 
void playermove(unsigned char ch) {
    int move_flag = 0;
    static unsigned char last_ch = 0;
    // 이동 가능한 최대 y 좌표
    int maxY = HEIGHT - 2;

    // 이전 위치를 기억
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
        if (oldy > 15) {  // 이동 가능한 최소 y 좌표
            newy = oldy - 1;
            move_flag = 1;
        }
        break;
    case DOWN:
        if (oldy < HEIGHT - 3) {  // 이동 가능한 최대 y 좌표
            newy = oldy + 1;
            move_flag = 1;
        }
        else {
            newy = oldy;
            move_flag = 0; // 아래쪽 벽면에 닿으면 움직임 플래그를 비활성화하여 캐릭터 생성 방지
        }
        break;

    case LEFT:
        if (oldx > 2) {  // 이동 가능한 최소 x 좌표
            newx = oldx - 1;
            move_flag = 1;
        }
        break;
    case RIGHT:
        if (oldx < WIDTH - 6) {  // 이동 가능한 최대 x 좌표
            newx = oldx + 1;
            move_flag = 1;
        }
        break;
    }
    if (oldy >= maxY) {
        newy = prevy;
        move_flag = 0; // 움직임 플래그 비활성화
    }
    if (move_flag) {
        erasePlayer(oldx, oldy);
        playerdraw(newx, newy); // 새로운 위치에서 플레이어 표시
        oldx = newx; // 마지막 위치 기억
        oldy = newy;
    }

    
}

/*게임이 종료된 후 게임이 다시 시작될 때
    변수 값들을 초기화해줌!!            */

void init_game() {
    system("cls");
    gotoxy(27, 27);
    eraseCursor();
   
}

/*///////////////////////////////////////////////////////////////////////
                             적 구현 부분
 //////////////////////////////////////////////////////////////////////*/

#define MAXENEMY 6

struct {
    int exist; //존재 여부
    int x, y; //적의 좌표
    int number;
    int move;  //이동경로
    int type; //적 모양
}Enemy[MAXENEMY];

char* Enemyunit[] = { "⊙★⊙","◈▒◈","♨▲♨","◐▼◑" };

//난수를 이용해 적 위치 랜덤
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
            // 현재 적의 이전 위치 지우기
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf("          "); // 이전 위치에 적이 있던 공간을 공백으로 채움

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

                // 새로운 위치에 적 출력
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf(Enemyunit[Enemy[i].type]);
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             적 총알 부분
 //////////////////////////////////////////////////////////////////////*/
#define MAXENEMYBULLET 20 // 적 최대 총알 수

int enemybulletuse = 1; //적 총알 1초마다 생성
int enemybullet_frame_sync = 15;  //적 총알 속도조절

struct {
    int exist;
    int x, y;
}EnemyBullet[MAXENEMYBULLET];

void EnemyBulletdraw(int i) {
    textcolor(RED2, BLACK);
    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
    printf("☆");
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
                             총알 부분
 //////////////////////////////////////////////////////////////////////*/
 
 //총알 구현 부분
#define MAXBULLET 8//플레이어의 최대 총알 수
#define TRUE 1
#define FALSE 0

struct {
    int exist;  //총알 존재여부 결정
    int x, y;
}Bullet[MAXBULLET];

void DrawBullet(int i) {
    textcolor(GREEN1, BLACK);
    gotoxy(Bullet[i].x, Bullet[i].y); printf("▲");
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
            else { // 맵 밖이아니라면  다시 그림
                Bullet[i].y--;
                DrawBullet(i);
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             키 입력처리 부분
 //////////////////////////////////////////////////////////////////////*/

// 방향키 입력 처리
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

// 속도 조절 및 총알 발사 입력 처리
void processSpeedAndFireInput() {
    if (GetAsyncKeyState(0x51) & 0x8000) { // 'Q' 키 입력 확인
        decreaseSpeed(); // 속도 감소 함수 호출
    }
    else if (GetAsyncKeyState(0x45) & 0x8000) { // 'E' 키 입력 확인
        increaseSpeed(); // 속도 증가 함수 호출
    }
    else if (GetAsyncKeyState(0x20) & 0x8000) { // 총알 발사
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
                             게임 출력 부분
 //////////////////////////////////////////////////////////////////////*/

 //게임화면
void gamestart(){
    
    system("cls");

    unsigned char ch;
    init_game();

    

    while (1) {

        //적생성, 적 총알 발사
        showenemy();
        Enemymove();
        EnemyBulletMove();

        playermove(0);

        processDirectionInput(&ch); //방향키
        
        // 방향키 입력에 따라 플레이어 이동
        if (ch != 0) {
            playermove(ch);
        }

        processSpeedAndFireInput(); //q,e,space


        bulletmove(); //총알 움직임
            
        
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
        printf("C언어를 이용한 슈팅게임!!");
        Sleep(2500);  //2.5초동안 작동
        system("cls");
 
        for (int i = 0; i <= 2; i++) {
            printf("로딩중▷▷▷▷");
            Sleep(300);
            system("cls");
            printf("로딩중▶▷▷▷");
            Sleep(300);
            system("cls");
            printf("로딩중▶▶▷▷");
            Sleep(300);
            system("cls");
            printf("로딩중▶▶▶▷");
            Sleep(300);
            system("cls");
            printf("로딩중▶▶▶▶");
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
                printf("입력 오류!\a\n\n");
                system("pause");
                system("cls");
            }
        }
        return 0;
    }