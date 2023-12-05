#ifndef PLAYER_FUNCTIONS_H
#define PLATER_FUNCTIONS_H
//색 정의
#define BLACK 0
#define BLUE1 1
#define GREEN1 2
#define CYAN1 3
#define RED1 4
#define MAGENTA1 5
#define YELLOW1 6
#define GRAY1 7
#define GRAY2 8
#define BLUE2 9
#define GREEN2 10
#define CYAN2 11
#define RED2 12
#define MAGENTA2 13
#define YELLOW2 14
#define WHITE 15

void textcolor(int fg_color, int bg_color); //색변경 함수 만들기
void eraseCursor(void); // 커서 숨기기
void gotoxy(int x, int y); //X,Y 이동함수

#endif /* PLAYER_FUNCTION_H */