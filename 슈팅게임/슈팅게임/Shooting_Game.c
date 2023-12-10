/*
    2023-11-08 C¾ğ¾î ±â¸» ÇÁ·ÎÁ§Æ® ½ÃÀÛ (¿ìÁÖ¼± ½´ÆÃ°ÔÀÓ)

    2023-11-11 ½ÃÀÛÈ­¸é ¿Ï¼º  
    2023-11-12 ½ÃÀÛÈ­¸é ¾Æ½ºÅ° ¾ÆÆ® ¼öÁ¤ ¹× »öÃß°¡, µµ¿ò¸» È­¸é ¿Ï¼º 
                gamestart ºÎºĞ ¼öÁ¤Áß¿¡ kbhitÀÌ ºñÁê¾ó¿¡¼­´Â ÀÛµ¿ÇÏÁö ¾Ê´Â´Ù. 
                -> GetAsyncKeyState·Î Å°¸¦ ´©¸£°í ÀÖÀ»¶§ ÀÛµ¿ÇÏ·Î°í ¼³Á¤ 
                ¹æÇâÅ° ÀÌµ¿ ±¸Çö (¸Ê³¡±îÁö ÀÌµ¿½Ã º®¿¡ Æ¨°Ü ¹İ´ë·Î °¡´Â °ÍÀ» Ãß°¡·Î ±¸Çö ÇÏ¿´´Ù.)
                ¹æÇâÅ° ÀÌµ¿ÇÒ¶§ Ä³¸¯ÅÍ°¡ ¹«ÇÑ»ı¼º ¿À·ù ¹ß»ı 
    2023-11-19 q,e ¼ÓµµÁ¶Àı Å°¿öµå Ãß°¡ 
                space ÃÑ¾Ë ±¸Çö
    2023-11-25 Ä³¸¯ÅÍ ÀÜ»ó Á¶±İ ÇØ°á
                Àû ·£´ı»ı¼º ±¸Çö
                Àû »ı¼ºÈÄ ÀÜ»ó¹®Á¦ ÇØ°á
    
    2023-11-31 ÄÜ¼Ö Å©±â º¯°æÀ¸·Î Ä³¸¯ÅÍ, Àû ÀÜ»ó ÇØ°á
                ÀûÀÌ ¿òÁ÷ÀÌ¸é¼­ ·£´ıÀ¸·Î ÃÑ¾Ë ¹ß»ç 
                ÀûÀÌ ½ğ ÃÑ¾Ë¿¡ ¸ÂÀ¸¸é ¸ñ¼û °¨¼Ò ±¸Çö
                Á¡¼ö ±¸Çö
                ÇØ°á ÇØ¾ßÇÒ¹®Á¦: Àû¿¡°Ô ÃÑ¾ËÀ» ¸Â­ŸÀ»¶§ ¿¹¿Ü ¹ß»ı
                ÇØ°á¿Ï·á
                ÀûÀ» ¸ÂÃèÀ»½Ã +10 Ç¥½Ã

    2023-12-03 Àû »ı¼º À§Ä¡ ¼öÁ¤ ¿Ï·á
               ÀûÀ» ¸ÂÃß¸é +10 Ç¥½Ã Á¦°Å
               ÀûÀ» ¸ÂÃèÀ»¶§ ³²Àº ÀÜ»ó Á¦°Å
               »ç¿ëÀÚ ¿òÁ÷ÀÓ °ø°£ ÁÙÀÓ
               ÃÑ¾Ë Ãâ·Â ¹æ½Ä º¯°æ






*/
# define _CRT_SECURE_NO_WARNINGS //ºñÁê¾ó ¿À·ù ¹«½Ã
#include<stdio.h>          //±âº» ÀÔÃâ·ÂÀ» À§ÇÑ ¶óÀÌºê·¯¸®
#include<Windows.h>    //±ÛÀÚ»ö, ¹è°æ»öÀ» ¹Ù²Ù±â À§ÇÑ ¶óÀÌºê·¯¸®
#include<time.h>          //°ÔÀÓ¿¡ ½Ã°£Èå¸§À» ³ªÅ¸³»±â À§ÇÑ ¶óÀÌºê·¯¸®
#include<stdlib.h>        // ³­¼ö¸¦ ¹ß»ı½ÃÅ°±â À§ÇÑ ¶óÀÌºê·¯¸®
#include<stdbool.h>     // ³í¸®Çü ÀÚ·á¸¦ ¾²±â À§ÇÑ ¶óÀÌºê·¯¸®
#include "player_functions.h" // »öº¯°æ,Ä¿¼­ ¼û±â±â, x.y ÀÌµ¿ ÇÔ¼ö 
#include "game_functions.h" //½ÃÀÛÈ­¸é, helpÈ­¸é Ãâ·Â µî ÇÔ¼ö


//    Å°º¸µå ÀÔ·Â°ªÀ» À§ÇÑ Àü¿ªº¯¼ö
//    ¹æÇâÅ°µµ Æ¯¼öÅ°·Î °£ÁÖ
//    16Áø¼ö·Î ¼±¾ğ
#define E 0x45   //¼Óµµ Áõ°¡
#define Q 0x51  //¼Óµµ °¨¼Ò
#define SPACE 0x20   //ÃÑ¾Ë
#define UP 0x48    
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d

int Delay = 30; //¼Óµµ
int minDelay = 20; // ÃÖ¼Ò ¼Óµµ
int maxDelay = 70; // ÃÖ´ë ¼Óµµ


int frame_count = 0; // game ÁøÇà frame count ·Î ¼Óµµ Á¶Àı¿ëÀ¸·Î »ç¿ëµÈ´Ù.
int p1_frame_sync = 4; //ÇÃ·¹ÀÌ¾îÀÇ ÀÌµ¿¼Óµµ

// ÇÃ·¹ÀÌ¾î ÀÌµ¿ ÁÂÇ¥ Ç¥½Ã
//°ÔÀÓ¸Ê ³ĞÀÌ
#define WIDTH 120  //  ÄÜ¼Ö °¡·Î ±æÀÌ
#define HEIGHT 30  //  ÄÜ¼Ö ¼¼·Î ±æÀÌ

#define UX (WIDTH / 2)   //½ÃÀÛ À¯ÀúÀÇ xÁÂÇ¥
#define UY (HEIGHT / 2)  //½ÃÀÛ À¯ÀúÀÇ yÁÂÇ¥

int called = 0;

int oldx = UX;
int oldy = UY; // ÇÃ·¹ÀÌ¾îÀÇ old ÁÂÇ¥
int newx = UX, newy = UY; //ÇÃ·¹ÀÌ¾îÀÇ new ÁÂÇ¥
int keep_moving = 1;  //1:°è¼ÓÀÌµ¿



void gamestart(); //°ÔÀÓ È­¸é Ãâ·Â
void init_game(); //Á¾·áÈÄ È­¸é ÃÊ±âÈ­
void playermove(unsigned char ch); //»ç¿ëÀÚ ¿òÁ÷ÀÌ±â




// ¼Óµµ °¨¼Ò ÇÔ¼ö (Q)
void decreaseSpeed() {
    if (Delay < maxDelay) {
        Delay += 15; // ¼Óµµ °¨¼Ò
    }
}

// ¼Óµµ Áõ°¡ ÇÔ¼ö (E)
void increaseSpeed() {
    if (Delay > minDelay) {
        Delay -= 15; // ¼Óµµ Áõ°¡
    }
}


//»ç¿ëÀÚ ¿òÁ÷ÀÓ 
void playermove(unsigned char ch) {
    int move_flag = 0;
    static unsigned char last_ch = 0;
    // ÀÌµ¿ °¡´ÉÇÑ ÃÖ´ë y ÁÂÇ¥
    int maxY = HEIGHT - 2;

    // ÀÌÀü À§Ä¡¸¦ ±â¾ï
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
        if (oldy > 15) {  // ÀÌµ¿ °¡´ÉÇÑ ÃÖ¼Ò y ÁÂÇ¥
            newy = oldy - 1;
            move_flag = 1;
        }
        break;
    case DOWN:
        if (oldy < HEIGHT - 3) {  // ÀÌµ¿ °¡´ÉÇÑ ÃÖ´ë y ÁÂÇ¥
            newy = oldy + 1;
            move_flag = 1;
        }
        else {
            newy = oldy;
            move_flag = 0; // ¾Æ·¡ÂÊ º®¸é¿¡ ´êÀ¸¸é ¿òÁ÷ÀÓ ÇÃ·¡±×¸¦ ºñÈ°¼ºÈ­ÇÏ¿© Ä³¸¯ÅÍ »ı¼º ¹æÁö
        }
        break;

    case LEFT:
        if (oldx > 15) {  // ÀÌµ¿ °¡´ÉÇÑ ÃÖ¼Ò x ÁÂÇ¥
            newx = oldx - 1;
            move_flag = 1;
        }
        break;
    case RIGHT:
        if (oldx < WIDTH - 30) {  // ÀÌµ¿ °¡´ÉÇÑ ÃÖ´ë x ÁÂÇ¥
            newx = oldx + 1;
            move_flag = 1;
        }
        break;
    }
    if (oldy >= maxY) {
        newy = prevy;
        move_flag = 0; // ¿òÁ÷ÀÓ ÇÃ·¡±× ºñÈ°¼ºÈ­
    }
    if (move_flag) {
        erasePlayer(oldx, oldy);
        playerdraw(newx, newy); // »õ·Î¿î À§Ä¡¿¡¼­ ÇÃ·¹ÀÌ¾î Ç¥½Ã
        oldx = newx; // ¸¶Áö¸· À§Ä¡ ±â¾ï
        oldy = newy;
    }

    
}

/*°ÔÀÓÀÌ Á¾·áµÈ ÈÄ °ÔÀÓÀÌ ´Ù½Ã ½ÃÀÛµÉ ¶§
    º¯¼ö °ªµéÀ» ÃÊ±âÈ­ÇØÁÜ!!            */

void init_game() {
    system("cls");
    gotoxy(27, 27);
    eraseCursor();
   
}


/*///////////////////////////////////////////////////////////////////////
                             Àû ±¸Çö ºÎºĞ
 //////////////////////////////////////////////////////////////////////*/

#define MAXENEMY 6

struct {
    int exist; // Á¸Àç ¿©ºÎ
    int x, y; // ÀûÀÇ ÁÂÇ¥
    int number;
    int move;  // ÀÌµ¿°æ·Î
    int type; // Àû ¸ğ¾ç
} Enemy[MAXENEMY];

char* Enemyunit[] = { "¢Á¡Ú¢Á", "¢Â¢Æ¢Â", "¢Í¡ã¢Í", "¢Ä¡å¢Å", "¡ß¢Ã¡ß", "¢İ¢Û¢İ" }; // Ãß°¡ÀûÀÎ Àû ¸ğ¾ç

// ÀûÀ» ÃÊ±â À§Ä¡¿¡ ¹èÄ¡ÇÏ´Â ÇÔ¼ö
void showenemy() {
    int i;
    int location, direct, changeDir;
    int overlap;
    textcolor(RED1, BLACK);
    for (i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == FALSE) {
            overlap = 0; // Ãæµ¹ ¿©ºÎ¸¦ È®ÀÎÇÏ´Â º¯¼ö ÃÊ±âÈ­
            location = rand() % 2;
            direct = 15 + rand() % 75; // x ÁÂÇ¥ ¹üÀ§ º¯°æ (15 ÀÌ»ó 90 ¹Ì¸¸)

            if (location == 1) {
                Enemy[i].x = direct;
                Enemy[i].y = 1 + rand() % 10; // y ÁÂÇ¥ ¹üÀ§ º¯°æ (10 ÀÌÇÏ)


                // ÀûÀÇ ÀÌµ¿ ¹æÇâ ¼³Á¤
                if (Enemy[i].x <= WIDTH / 2) { // ÀûÀÌ È­¸é ¿ŞÂÊ¿¡ »ı¼ºµÈ °æ¿ì
                    Enemy[i].move = 1; // ¿À¸¥ÂÊÀ¸·Î ÀÌµ¿
                }
                else {
                    Enemy[i].move = -1; // ¿ŞÂÊÀ¸·Î ÀÌµ¿
                }

                // ÀûÀÇ ¸ğ¾ç ¼³Á¤ (·£´ıÇÏ°Ô ¼±ÅÃ)
                Enemy[i].type = rand() % 6; // 0ºÎÅÍ 5±îÁöÀÇ °ª Áß¿¡¼­ ·£´ı ¼±ÅÃ

                // ·£´ıÇÏ°Ô ¹æÇâ º¯°æ
                changeDir = rand() % 2; // 0 ¶Ç´Â 1ÀÇ °ªÀ¸·Î ¹«ÀÛÀ§ ¹æÇâ ÀüÈ¯
                if (changeDir == 1) {
                    Enemy[i].move *= -1; // ÇöÀç ¹æÇâÀÇ ¹İ´ë ¹æÇâÀ¸·Î º¯°æ
                }

                // ÀÌÀü¿¡ »ı¼ºµÈ Àûµé°ú À§Ä¡ ºñ±³ÇÏ¿© °ãÄ¡´ÂÁö È®ÀÎ
                for (int j = 0; j < i; j++) {
                    if (Enemy[i].x == Enemy[j].x && Enemy[i].y == Enemy[j].y) {
                        overlap = 1; // °ãÄ¡´Â °æ¿ì, overlapÀ» 1·Î ¼³Á¤
                        break;
                    }
                }

                // °ãÄ¡Áö ¾Ê´Â À§Ä¡¿¡ Àû »ı¼º
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
            // ÀÌÀü À§Ä¡ Áö¿ì±â
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf("          "); // ÀÌÀü À§Ä¡¿¡ ÀûÀÌ ÀÖ´ø °ø°£À» °ø¹éÀ¸·Î Ã¤¿ò

            // ÀûÀÇ ÀÌµ¿ °æ·Î ¼³Á¤
            Enemy[i].x += Enemy[i].move;

            // È­¸é °æ°è¿¡ µµ´ŞÇÏ¸é ¹æÇâÀ» º¯°æÇÏ°í ÀûÀÇ À§Ä¡¸¦ Á¶Á¤ÇÏ´Â ºÎºĞ
            if (Enemy[i].x <= 20 || Enemy[i].x >= 90) {
                Enemy[i].move *= -1; // ÀÌµ¿ ¹æÇâÀ» ¹İ´ë·Î º¯°æ

                // ÀûÀÌ È­¸éÀ» ³Ñ¾î°¡´Â °ÍÀ» ¹æÁöÇÏ°íÀÚ ÇÒ ¶§, ¹İ´ëÆíÀ¸·Î ÀÌµ¿ÇÏµµ·Ï ¼³Á¤
                if (Enemy[i].x <= 20) {
                    Enemy[i].x = 21 + abs(Enemy[i].move); // È­¸é ÁÂÃø °æ°è¿¡ ´ê¾ÒÀ» ¶§ ¿ìÃø ³¡À¸·Î ÀÌµ¿
                }
                else if (Enemy[i].x >= 90) {
                    Enemy[i].x = 89 - abs(Enemy[i].move); // È­¸é ¿ìÃø °æ°è¿¡ ´ê¾ÒÀ» ¶§ ÁÂÃø ³¡À¸·Î ÀÌµ¿
                }
            }


            // »õ·Î¿î À§Ä¡¿¡ Àû Ãâ·Â
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf(Enemyunit[Enemy[i].type]);
        }
    }
}







/*///////////////////////////////////////////////////////////////////////
                             Àû ÃÑ¾Ë ºÎºĞ
 //////////////////////////////////////////////////////////////////////*/
#define MAXENEMYBULLET 100 // Àû ÃÖ´ë ÃÑ¾Ë ¼ö

int enemybulletuse = 10; //Àû ÃÑ¾Ë 1ÃÊ¸¶´Ù »ı¼º
int enemybullet_frame_sync = 10;  //Àû ÃÑ¾Ë ¼ÓµµÁ¶Àı

struct {
    int exist;
    int x, y;
}EnemyBullet[MAXENEMYBULLET];

void EnemyBulletshow() {
    static int frame_count = 0; // ÇÁ·¹ÀÓ Ä«¿îÆ® º¯¼ö Ãß°¡
    frame_count++;

    if (frame_count >= enemybullet_frame_sync) {
        frame_count = 0; // ÇÁ·¹ÀÓ Ä«¿îÆ® ÃÊ±âÈ­

        for (int i = 0; i < MAXENEMY; i++) {
            if (Enemy[i].exist == TRUE) {
                for (int j = 0; j < enemybulletuse; j++) {
                    for (int k = 0; k < MAXENEMYBULLET; k++) {
                        if (EnemyBullet[k].exist == FALSE) {
                            EnemyBullet[k].x = Enemy[i].x + 2; // Àû ÃÑ¾Ë x ÁÂÇ¥ ¼³Á¤
                            EnemyBullet[k].y = Enemy[i].y + 1; // Àû ÃÑ¾Ë y ÁÂÇ¥ ¼³Á¤
                            EnemyBullet[k].exist = TRUE;
                            break; // ÃÑ¾Ë »ı¼º ÈÄ ¹İº¹¹® Á¾·á
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
    printf("¡Ù");
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
                             ÃÑ¾Ë ºÎºĞ
 //////////////////////////////////////////////////////////////////////*/
 
 //ÃÑ¾Ë ±¸Çö ºÎºĞ
#define MAXBULLET 6//ÇÃ·¹ÀÌ¾îÀÇ ÃÖ´ë ÃÑ¾Ë ¼ö
#define TRUE 1
#define FALSE 0

struct {
    int exist;  //ÃÑ¾Ë Á¸Àç¿©ºÎ °áÁ¤
    int x, y;
}Bullet[MAXBULLET];

void DrawBullet(int i) {
    textcolor(GREEN1, BLACK);
    gotoxy(Bullet[i].x, Bullet[i].y); printf("¡ã");
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
            else { // ¸Ê ¹ÛÀÌ¾Æ´Ï¶ó¸é  ´Ù½Ã ±×¸²
                Bullet[i].y--;
                DrawBullet(i);
            }
        }
    }
}

/*///////////////////////////////////////////////////////////////////////
                             Å° ÀÔ·ÂÃ³¸® ºÎºĞ
 //////////////////////////////////////////////////////////////////////*/

// ¹æÇâÅ° ÀÔ·Â Ã³¸®
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

// ¼Óµµ Á¶Àı ¹× ÃÑ¾Ë ¹ß»ç ÀÔ·Â Ã³¸®
void processSpeedAndFireInput() {
    if (GetAsyncKeyState(0x51) & 0x8000) { // 'Q' Å° ÀÔ·Â È®ÀÎ
        decreaseSpeed(); // ¼Óµµ °¨¼Ò ÇÔ¼ö È£Ãâ
    }
    else if (GetAsyncKeyState(0x45) & 0x8000) { // 'E' Å° ÀÔ·Â È®ÀÎ
        increaseSpeed(); // ¼Óµµ Áõ°¡ ÇÔ¼ö È£Ãâ
    }
    else if (GetAsyncKeyState(0x20) & 0x8000) { // ÃÑ¾Ë ¹ß»ç
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
                             Ãæµ¹ ºÎºĞ
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
                // ÃÑ¾Ë À§Ä¡¸¦ Áö¿ò
                gotoxy(Bullet[j].x, Bullet[j].y);
                printf("   ");
                Bullet[j].exist = FALSE;

                // Á¡¼ö¸¦ Áõ°¡½ÃÅ°°í ÀûÀ» ¸ÂÃèÀ¸´Ï »ç¶óÁöµµ·Ï ¼³Á¤
                score += 10;
                Enemy[i].exist = FALSE;
                Enemy[i].type = -1;

                // È­¸é¿¡¼­ ÀûÀ» Áö¿ì±â
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf("         ");

                // »õ·Î¿î ·£´ı À§Ä¡¿¡ Àû »ı¼º
                showenemy();
                break; // ÀûÀÌ ÇÑ ¹ø¿¡ ÇÑ ¹ßÀÇ ÃÑ¾Ë¿¡¸¸ ¸ÂÀ» ¼ö ÀÖµµ·Ï
            }
        }
    }
}


//³»°¡ ÀûÀÇ ÃÑ¾Ë¿¡ ¸Â¾ÒÀ» ¶§
void playerfall() {
    int i;
    for (i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            if (EnemyBullet[i].y == newy && abs(EnemyBullet[i].x - newx) <= 3) {
                EnemyBullet[i].exist = FALSE;
                gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
                printf("    ");
                heart--; // ÇÏÆ® °¨¼Ò
                break; //1°³ÀÇ ÇÏÆ®¸¸ °¨¼ÒÇÏµµ·Ï break¹® ÀÔ·Â

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
        exit(0); // ÇÏÆ®°¡ 0 ÀÌÇÏÀÏ ¶§ °ÔÀÓ Á¾·á
    }
}




void info() {
    textcolor(YELLOW2, BLACK);
    textcolor(WHITE, BLACK);
    gotoxy(100, 28); printf("Á¡¼ö: %d", score);
    gotoxy(5, 28);
    printf("¸ñ¼û:");
    if (heart >= 4) {
        heart = 4;
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("¢¾¢¾¢¾¢¾");
    }
    else if (heart == 3) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("¢¾¢¾¢¾");
    }
    else if (heart == 2) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("¢¾¢¾");
    }
    else if (heart == 1) {
        gotoxy(10, 28); printf("       ");
        gotoxy(10, 28); printf("¢¾");
    }
    else {
        gotoxy(10, 28);
        printf("  ");
    }

}

////////////////////////////////////////////
/*°ÔÀÓ È­¸é °»½Å ÇÔ¼ö (¸Å ÇÁ·¹ÀÓ¸¶´Ù È£ÃâµÊ)*/
/////////////////////////////////////////////

void updateScreen() {
    erasePlayer(oldx, oldy); // ÀÌÀü ÇÃ·¹ÀÌ¾î À§Ä¡ Áö¿ì±â
    playerdraw(newx, newy); // »õ·Î¿î ÇÃ·¹ÀÌ¾î À§Ä¡ Ç¥½Ã

    for (int i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == TRUE && Enemy[i].type != -1) {
            gotoxy(Enemy[i].x, Enemy[i].y);
            printf(Enemyunit[Enemy[i].type]); // ÀûÀÇ À§Ä¡ °»½Å
        }
    }

    for (int i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            EnemyBulleterase(i); // ÀÌÀü Àû ÃÑ¾Ë À§Ä¡ Áö¿ì±â
            if (EnemyBullet[i].y < HEIGHT - 3) {
                EnemyBullet[i].y++;
                EnemyBulletdraw(i); // »õ·Î¿î Àû ÃÑ¾Ë À§Ä¡ Ç¥½Ã
            }
            else {
                EnemyBullet[i].exist = FALSE; // È­¸éÀ» ¹ş¾î³­ Àû ÃÑ¾Ë Á¦°Å
            }
        }
    }

    for (int i = 0; i < MAXBULLET; i++) {
        if (Bullet[i].exist == TRUE) {
            EraseBullet(i); // ÀÌÀü ÇÃ·¹ÀÌ¾î ÃÑ¾Ë À§Ä¡ Áö¿ì±â
            if (Bullet[i].y > 0) {
                Bullet[i].y--; // ÃÑ¾Ë À§·Î ÀÌµ¿
                DrawBullet(i); // »õ·Î¿î ÃÑ¾Ë À§Ä¡ Ç¥½Ã
            }
            else {
                Bullet[i].exist = FALSE; // È­¸éÀ» ¹ş¾î³­ ÃÑ¾Ë Á¦°Å
            }
        }
    }
}


/*///////////////////////////////////////////////////////////////////////
                             °ÔÀÓ Ãâ·Â ºÎºĞ
 //////////////////////////////////////////////////////////////////////*/
#define WIDTH 120  // º¯°æµÈ ÄÜ¼Ö °¡·Î ±æÀÌ
#define HEIGHT 30  // º¯°æµÈ ÄÜ¼Ö ¼¼·Î ±æÀÌ


 //°ÔÀÓÈ­¸é
void gamestart(){
    
    system("cls");

    unsigned char ch;
    init_game();

    //»ı¸í Ç¥½Ã
    info();

    while (1) {
        

        //Àû»ı¼º, Àû ÃÑ¾Ë ¹ß»ç
        showenemy();
        Enemymove();

        EnemyBulletshow();
        EnemyBulletMove();

        playermove(0);

        processDirectionInput(&ch); //¹æÇâÅ°
        
        // ¹æÇâÅ° ÀÔ·Â¿¡ µû¶ó ÇÃ·¹ÀÌ¾î ÀÌµ¿
        if (ch != 0) {
            playermove(ch);
        }

        processSpeedAndFireInput(); //q,e,space


        bulletmove(); //ÃÑ¾Ë ¿òÁ÷ÀÓ
        
        // Ãæµ¹ °¨Áö ¹× °ÔÀÓ Á¤º¸ Ãâ·Â
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
        printf("C¾ğ¾î¸¦ ÀÌ¿ëÇÑ ½´ÆÃ°ÔÀÓ!!");
        Sleep(2500);  //2.5ÃÊµ¿¾È ÀÛµ¿
        system("cls");
 
        for (int i = 0; i <= 2; i++) {
            printf("·ÎµùÁß¢¹¢¹¢¹¢¹");
            Sleep(300);
            system("cls");
            printf("·ÎµùÁß¢º¢¹¢¹¢¹");
            Sleep(300);
            system("cls");
            printf("·ÎµùÁß¢º¢º¢¹¢¹");
            Sleep(300);
            system("cls");
            printf("·ÎµùÁß¢º¢º¢º¢¹");
            Sleep(300);
            system("cls");
            printf("·ÎµùÁß¢º¢º¢º¢º");
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
                printf("ÀÔ·Â ¿À·ù!\a\n\n");
                system("pause");
                system("cls");
            }
        }
        return 0;
    }