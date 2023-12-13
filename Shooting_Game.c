
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

int Delay = 30; //속도
int minDelay = 20; // 최소 속도
int maxDelay = 70; // 최대 속도


int frame_count = 0; // game 진행 frame count 로 속도 조절용으로 사용된다.
int p1_frame_sync = 4; //플레이어의 이동속도

// 플레이어 이동 좌표 표시
//게임맵 넓이
#define WIDTH 120  //  콘솔 가로 길이
#define HEIGHT 30  //  콘솔 세로 길이

#define UX (WIDTH / 2)   //시작 유저의 x좌표
#define UY (HEIGHT / 2)  //시작 유저의 y좌표

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
        if (oldx > 15) {  // 이동 가능한 최소 x 좌표
            newx = oldx - 1;
            move_flag = 1;
        }
        break;
    case RIGHT:
        if (oldx < WIDTH - 30) {  // 이동 가능한 최대 x 좌표
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
    int exist; // 존재 여부
    int x, y; // 적의 좌표
    int number;
    int move;  // 이동경로
    int type; // 적 모양
} Enemy[MAXENEMY];

char* Enemyunit[] = { "⊙★⊙", "◈▒◈", "♨▲♨", "◐▼◑", "◆▣◆", "♬♩♬" }; // 추가적인 적 모양

// 적을 초기 위치에 배치하는 함수
void showenemy() {
    int i;
    int location, direct, changeDir;
    int overlap;
    textcolor(RED1, BLACK);
    for (i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == FALSE) {
            overlap = 0; // 충돌 여부를 확인하는 변수 초기화
            location = rand() % 2;
            direct = 15 + rand() % 75; // x 좌표 범위 변경 (15 이상 90 미만)

            if (location == 1) {
                Enemy[i].x = direct;
                Enemy[i].y = 1 + rand() % 10; // y 좌표 범위 변경 (10 이하)


                // 적의 이동 방향 설정
                if (Enemy[i].x <= WIDTH / 2) { // 적이 화면 왼쪽에 생성된 경우
                    Enemy[i].move = 1; // 오른쪽으로 이동
                }
                else {
                    Enemy[i].move = -1; // 왼쪽으로 이동
                }

                // 적의 모양 설정 (랜덤하게 선택)
                Enemy[i].type = rand() % 6; // 0부터 5까지의 값 중에서 랜덤 선택

                // 이전에 생성된 적들과 위치 비교하여 겹치는지 확인
                for (int j = 0; j < i; j++) {
                    if (Enemy[i].x == Enemy[j].x && Enemy[i].y == Enemy[j].y) {
                        overlap = 1; // 겹치는 경우, overlap을 1로 설정
                        break;
                    }
                }

                // 겹치지 않는 위치에 적 생성
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
            // 이전 위치 지우기
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf("          "); // 이전 위치에 적이 있던 공간을 공백으로 채움

            // 적의 이동 경로 설정
            Enemy[i].x += Enemy[i].move;

            // 화면 경계에 도달하면 방향을 변경하고 적의 위치를 조정하는 부분
            if (Enemy[i].x <= 20 || Enemy[i].x >= 90) {
                Enemy[i].move *= -1; // 이동 방향을 반대로 변경

                // 적이 화면을 넘어가는 것을 방지하고자 할 때, 반대편으로 이동하도록 설정
                if (Enemy[i].x <= 20) {
                    Enemy[i].x = 21 + abs(Enemy[i].move); // 화면 좌측 경계에 닿았을 때 우측 끝으로 이동
                }
                else if (Enemy[i].x >= 90) {
                    Enemy[i].x = 89 - abs(Enemy[i].move); // 화면 우측 경계에 닿았을 때 좌측 끝으로 이동
                }
            }


            // 새로운 위치에 적 출력
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf(Enemyunit[Enemy[i].type]);
        }
    }
}







/*///////////////////////////////////////////////////////////////////////
                             적 총알 부분
 //////////////////////////////////////////////////////////////////////*/
#define MAXENEMYBULLET 100 // 적 최대 총알 수

int enemybulletuse = 10; //적 총알 1초마다 생성
int enemybullet_frame_sync = 10;  //적 총알 속도조절

struct {
    int exist;
    int x, y;
}EnemyBullet[MAXENEMYBULLET];

void EnemyBulletshow() {
    static int frame_count = 0; // 프레임 카운트 변수 추가
    frame_count++;

    if (frame_count >= enemybullet_frame_sync) {
        frame_count = 0; // 프레임 카운트 초기화

        for (int i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == TRUE) {
                for (int j = 0; j < enemybulletuse; j++) {
                    for (int k = 0; k < MAXENEMYBULLET; k++) {
                        if (EnemyBullet[k].exist == FALSE) {
                            EnemyBullet[k].x = Enemy[i].x + 2; // 적 총알 x 좌표 설정
                            EnemyBullet[k].y = Enemy[i].y + 1; // 적 총알 y 좌표 설정
                            EnemyBullet[k].exist = TRUE;
                            break; // 총알 생성 후 반복문 종료
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
    printf("☆");
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
                             총알 부분
 //////////////////////////////////////////////////////////////////////*/
 
 //총알 구현 부분
#define MAXBULLET 6//플레이어의 최대 총알 수
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
                             충돌 부분
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
                // 총알 위치를 지움
                gotoxy(Bullet[j].x, Bullet[j].y);
                printf("   ");
                Bullet[j].exist = FALSE;

                // 점수를 증가시키고 적을 맞췄으니 사라지도록 설정
                score += 10;
                Enemy[i].exist = FALSE;
                Enemy[i].type = -1;

                // 화면에서 적을 지우기
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf("         ");

                // 새로운 랜덤 위치에 적 생성
                showenemy();
                break; // 적이 한 번에 한 발의 총알에만 맞을 수 있도록
            }
        }
    }
}


//내가 적의 총알에 맞았을 때
void playerfall() {
    int i;
    for (i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            if (EnemyBullet[i].y == newy && abs(EnemyBullet[i].x - newx) <= 3) {
                EnemyBullet[i].exist = FALSE;
                gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
                printf("    ");
                heart--; // 하트 감소
                break; //1개의 하트만 감소하도록 break문 입력

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
        exit(0); // 하트가 0 이하일 때 게임 종료
    }
}




void info() {
    textcolor(YELLOW2, BLACK);
    textcolor(WHITE, BLACK);
    gotoxy(100, 28); printf("점수: %d", score);
    gotoxy(5, 28);
    printf("목숨:");
    if (heart >= 4) {
        heart = 4;
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("♥♥♥♥");
    }
    else if (heart == 3) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("♥♥♥");
    }
    else if (heart == 2) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("♥♥");
    }
    else if (heart == 1) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("♥");
    }
    else {
        gotoxy(10, 28);
        printf("  ");
    }

}


/*///////////////////////////////////////////////////////////////////////
                             게임 출력 부분
 //////////////////////////////////////////////////////////////////////*/
#define WIDTH 120  // 변경된 콘솔 가로 길이
#define HEIGHT 30  // 변경된 콘솔 세로 길이


 //게임화면
void gamestart(){
    
    system("cls");

    unsigned char ch;
    init_game();

    //생명 표시
    info();

    while (1) {
        

        //적생성, 적 총알 발사
        showenemy();
        Enemymove();

        EnemyBulletshow();
        EnemyBulletMove();

        playermove(0);

        processDirectionInput(&ch); //방향키
        
        // 방향키 입력에 따라 플레이어 이동
        if (ch != 0) {
            playermove(ch);
        }

        processSpeedAndFireInput(); //q,e,space


        bulletmove(); //총알 움직임
        
        // 충돌 감지 및 게임 정보 출력
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
                printf("입력 오류!\a\n\n");
                system("pause");
                system("cls");
            }
        }
        return 0;
    }