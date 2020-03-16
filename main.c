#include <stdio.h>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsolePosition() 함수 사용
#include <conio.h> //getch()와 kbhit() 함수 사용
#include <time.h>

#define ESC 27 //게임 종료
#define LEFT 75 //왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80 //아래 화살표 키 ASCII값
#define UP 72

#define BOARD_HEIGHT 22 //게임 보드 높이
#define BOARD_WIDTH  12 //게임 보드 넓이 

//게임 보드 그리기 시작 위치
#define BOARD_STARTX 20  
#define BOARD_STARTY 2

//다음 블럭 그리기 시작 위치
#define NEXTBLOCK_STARTX  50  
#define NEXTBLOCK_STARTY  3

//점수 그리기 시작 위치
#define SCORE_STARTX 50
#define SCORE_STARTY 23

enum gameAction { MOVE_LEFT = 1, MOVE_RIGHT, MOVE_DOWN, MOVE_DROP, GAME_QUIT, CHANGE };

//MOVE_LEFT: 블럭 왼쪽 1칸 이동, MOVE_RIGHT: 블럭 오른쪽 1칸 이동, MOVE_DOWN: 블럭 아래 1칸 이동
//MOVE_DROP: 블럭 아래 1칸 자동 이동, GAME_QUIT: 게임종료



int board[12][22];
int times, times_s,Type, Rotation;
int X, Y; // 보드 안의 X,Y 위치, 블록 그리기위치
int exX, exY, extype, exrotation;//보드 안의 전 블럭의 위치  
int gameAction; //행동 정의
int flag, collisions; // 충돌했을시 collisions = 1 
int getGameAction(void); // 게임의 기능을 선택하는 함수
int gameScore;

void initGame(); //게임 초기화
void gotoXY(int x, int y); //콘솔 화면에서 커서를 특정 위치로 이동
void drawGame(int X, int Y, int type, int rotation); // 게임 화면을 그리는 함수
void eraseGame(int exX, int exY, int extype, int exrotation);
void save(void);
void lineerase(void);
void count(void);
void control(int X, int Y, int type, int rotation);
void collision(int X, int Y, int type, int rotations);
void reset(void);
void clear(void);

/*
★★★★ 완료
by 2020.03.14

Type 수정(완)
★★
★★ 완료


★★
  ★★ 완료

  ★★
★★   완료
  by 2020.03.15

 ★
 ★★★
		완료
	 ★
 ★★★	완료

   ★
 ★★★  완료
 by 2020.03.16

*/

int main(void)
{
	initGame();
	srand((unsigned)time(NULL));
	X = 4, Y = 1; Type = 0; Rotation = 0;
	exX = 4; exY = 4; flag = 0; collisions = 0;

	while (gameAction != GAME_QUIT)
	{
		if (times == 20)
		{
			gameAction = getGameAction();
			
			control(X,Y,Type, Rotation);
			collision(X, Y, Type, Rotation);
			lineerase();
			eraseGame(exX, exY, extype, exrotation);
			save();
			if (times_s == 100)
			{
				clear();
				times_s = 0;
			}
			drawGame(X, Y, Type, Rotation);
			Y++;
			times = 0;
		}
		count();
	}
	return 0;
}

void drawGame(int X, int Y, int type, int rotation) // 게임 화면을 그리는 함수
{
	switch (type)
	{
	case(0):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * X, Y);
			for (int i = 0; i < 4; i++)
			{
				printf("★");
			}
			break;
		case(1):
			gotoXY(2 * X, Y);
			for (int i = 1; i < 4; i++)
			{
				printf("★");
				gotoXY(2 * X, Y + i);
			}
			printf("★");
			break;
		case(2):
			gotoXY(2 * X, Y);
			for (int i = 0; i < 4; i++)
			{
				printf("★");
			}
			break;
		case(3):
			gotoXY(2 * X, Y);
			for (int i = 0; i < 4; i++)
			{
				printf("★");
				gotoXY(2 * X, Y + i);
			}
			printf("★");
			break;
		}
		break;
	}
	case(1):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;
		case(1):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;
		case(2):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;
		case(3):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;

		}
		break;
	}
	case(2):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * (X + 1), Y + 1);
			printf("★★");
			break;
		case(1):
			gotoXY(2 * (X + 1), Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * X, Y + 2);
			printf("★");
			break;
		case(2):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * (X + 1), Y + 1);
			printf("★★");
			break;
		case(3):
			gotoXY(2 * (X + 1), Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * X, Y + 2);
			printf("★");
			break;

		}
		break;
	}
	case(3):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * (X+1), Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;
		case(1):
			gotoXY(2 * X , Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * (X+1), Y + 2);
			printf("★");
			break;
		case(2):
			gotoXY(2 * (X + 1), Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			break;
		case(3):
			gotoXY(2 * X, Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * (X + 1), Y + 2);
			printf("★");
			break;

		}
		break;
	}
	case(4):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * X, Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★★");
			break;
		case(1):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * X, Y + 1);
			printf("★");
			gotoXY(2 * X, Y + 2);
			printf("★");
			break;
		case(2):
			gotoXY(2 *X, Y);
			printf("★★★");
			gotoXY(2 * (X+2), Y + 1);
			printf("★");
			break;
		case(3):
			gotoXY(2 * (X + 1), Y);
			printf("★");
			gotoXY(2 * (X + 1), Y + 1);
			printf("★");
			gotoXY(2 * X, Y+2);
			printf("★★");
			break;
		}
		break;
	}
	case(5):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * (X+2), Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★★");
			break;
		case(1):
			gotoXY(2 *X, Y);
			printf("★");
			gotoXY(2 * X , Y + 1);
			printf("★");
			gotoXY(2 * X, Y + 2);
			printf("★★");
			break;
		case(2):
			gotoXY(2 * X, Y);
			printf("★★★");
			gotoXY(2 * X, Y + 1);
			printf("★");
			break;
		case(3):
			gotoXY(2 * X, Y);
			printf("★★");
			gotoXY(2 * (X+1), Y + 1);
			printf("★");
			gotoXY(2 * (X+1), Y + 2);
			printf("★");
			break;
		}
		break;
	}
	case(6):
	{
		switch (rotation)
		{
		case(0):
			gotoXY(2 * (X + 1), Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★★");
			break;
		case(1):
			gotoXY(2 * X, Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * X, Y + 2);
			printf("★");
			break;
		case(2):
			gotoXY(2 * X, Y);
			printf("★★★");
			gotoXY(2 * (X+1), Y + 1);
			printf("★");
			break;
		case(3):
			gotoXY(2 * (X+1), Y);
			printf("★");
			gotoXY(2 * X, Y + 1);
			printf("★★");
			gotoXY(2 * (X + 1), Y + 2);
			printf("★");
			break;
		}
		break;
	}
	break;
	}
}
void eraseGame(int exX, int exY, int extype, int exrotation)
{
	switch (extype)
	{
	case(0):
	{
		switch (exrotation)
		{
		case(0):
		{
			gotoXY(2 * exX, exY);
			for (int i = 0; i < 4; i++)
			{
				printf("  ");
			}
			break;
		}
		case(1):
		{
			gotoXY(2 * exX, exY);
			for (int i = 0; i < 4; i++)
			{
				printf("  ");
				gotoXY(2 * exX, exY + i);
			}
			break;
		}
		case(2):
		{
			gotoXY(2 * exX, exY);
			for (int i = 0; i < 4; i++)
			{
				printf("  ");
			}
			break;
		}
		case(3):
		{
			gotoXY(2 * exX, exY);
			for (int i = 0; i < 4; i++)
			{
				printf("  ");
				gotoXY(2 * exX, exY + i);
			}
			break;
		}
		break;
		}
		break;
	}
	case(1):
	{
		switch (exrotation)
		{
		case(0):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		}
		case(1):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		}
		case(2):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		}
		case(3):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		}

		break;
		}
		break;
	}
	case(2):
	{
		switch (exrotation)
		{
		case(0):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 1);
			printf("    ");
			break;
		}
		case(1):
		{
			gotoXY(2 * (exX + 1), exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * exX, exY + 2);
			printf("  ");
			break;
		}
		case(2):
		{
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 1);
			printf("    ");
			break;
		}
		case(3):
		{
			gotoXY(2 * (exX + 1), exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * exX, exY + 2);
			printf("  ");
			break;
		}
		break;
		}
		break;
	}
	case(3):
	{
		switch (exrotation)
		{
		case(0):
			gotoXY(2 * (exX + 1), exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		case(1):
			gotoXY(2 * exX, exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 2);
			printf("  ");
			break;
		case(2):
			gotoXY(2 * (exX + 1), exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			break;
		case(3):
			gotoXY(2 * exX, exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 2);
			printf("  ");
			break;
		}
		break;
	}
	case(4):
	{
		switch (exrotation)
		{
		case(0):
			gotoXY(2 * exX, exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("      ");
			break;
		case(1):
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * exX, exY + 1);
			printf("  ");
			gotoXY(2 * exX, exY + 2);
			printf("  ");
			break;
		case(2):
			gotoXY(2 * exX, exY);
			printf("      ");
			gotoXY(2 * (exX + 2), exY + 1);
			printf("  ");
			break;
		case(3):
			gotoXY(2 * (exX + 1), exY);
			printf("  ");
			gotoXY(2 * (exX + 1), exY + 1);
			printf("  ");
			gotoXY(2 * exX, exY + 2);
			printf("    ");
			break;
		}
		break;
	}
	case(5):
	{
		switch (exrotation)
		{
		case(0):
			gotoXY(2 * (exX + 2), exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("      ");
			break;
		case(1):
			gotoXY(2 * exX, exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("  ");
			gotoXY(2 * exX, exY + 2);
			printf("    ");
			break;
		case(2):
			gotoXY(2 * exX, exY);
			printf("      ");
			gotoXY(2 * exX, exY + 1);
			printf("  ");
			break;
		case(3):
			gotoXY(2 * exX, exY);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 1);
			printf("  ");
			gotoXY(2 * (exX + 1), exY + 2);
			printf("  ");
			break;
		}
		break;
	}
	case(6):
	{
		switch (exrotation)
		{
		case(0):
			gotoXY(2 * (exX + 1), exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("      ");
			break;
		case(1):
			gotoXY(2 * exX, exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * exX, exY + 2);
			printf("  ");
			break;
		case(2):
			gotoXY(2 * exX, exY);
			printf("      ");
			gotoXY(2 * (exX + 1), exY + 1);
			printf("  ");
			break;
		case(3):
			gotoXY(2 * (exX + 1), exY);
			printf("  ");
			gotoXY(2 * exX, exY + 1);
			printf("    ");
			gotoXY(2 * (exX + 1), exY + 2);
			printf("  ");
			break;
		}
		break;
	}
	}
}
void control(int x, int y, int type, int rotation)
{
	switch (gameAction)
	{
	case MOVE_LEFT:
	{
		X--;
		if (board[x - 1][y] == 1)X++;
		break;
	}
	case MOVE_RIGHT:
	{
		switch (type)
		{
		case (0):
		{
			switch (rotation)
			{
			case(0):
				X++;
				if (board[x + 4][y] == 1) X--;
				break;
			case(1):
				X++;
				if (board[x + 1][y] == 1 || board[x + 1][y + 1] == 1 || board[x + 1][y + 2] == 1 || board[x + 1][y + 3] == 1) X--;
				break;
			case(2):
				X++;
				if (board[x + 4][y] == 1) X--;
				break;
			case(3):
				X++;
				if (board[x + 1][y] == 1 || board[x + 1][y + 1] == 1 || board[x + 1][y + 2] == 1 || board[x + 1][y + 3] == 1) X--;
				break;
			}
		}
		break;
		case (1):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1) X--;
				break;
			}
			}
			break;
		}
		break;
		case (2):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 3][y + 1] == 1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 1][y + 2] == 1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 3][y + 1] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 1][y + 2] == 1) X--;
				break;
			}
			}
			break;
		}
		break;
		case (3):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x + 3][y] == 1 || board[x + 2][y] == 1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x + 1][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 1][y + 2] == 1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x + 3][y] == 1 || board[x + 2][y] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x + 1][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 1][y + 2] == 1) X--;
				break;
			}
			}
			break;
		}
		break;
		case (4):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x+1][y] == 1 || board[x+3][y+1]==1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x+2][y] == 1 || board[x + 1][y + 1] == 1||board[x+1][y+2]==1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x+3][y] == 1 || board[x+3][y+1] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x+1][y] == 1 || board[x + 1][y + 1] == 1||board[x+2][y+2]==1) X--;
				break;
			}
			}
			break;
		}
		break;
		case (5):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x+3][y] == 1 || board[x + 3][y + 1] == 1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x+1][y] == 1 || board[x + 1][y + 1] == 1||board[x+2][y+2]==1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x+3][y] == 1 || board[x + 1][y + 1] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x+2][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 2][y + 2] == 1) X--;
				break;
			}
			}
			break;
		}
		break;
		case (6):
		{
			switch (rotation)
			{
			case(0):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 3][y + 1] == 1) X--;
				break;
			}
			case(1):
			{
				X++;
				if (board[x + 1][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 1][y + 2] == 1) X--;
				break;
			}
			case(2):
			{
				X++;
				if (board[x + 3][y] == 1 || board[x + 2][y + 1] == 1) X--;
				break;
			}
			case(3):
			{
				X++;
				if (board[x + 2][y] == 1 || board[x + 2][y + 1] == 1 || board[x + 2][y + 2] == 1) X--;
				break;
			}
			}
			break;
		}
		break;
		}
		break;
	}
	case MOVE_DOWN:
	{
		Y++;
		if (Y > 12)Y--;
		break;
	}
	case CHANGE:
	{
		Rotation++;
		if (Rotation == 4)
			Rotation = 0;
		break;
	}
	break;
	}
}
void collision(int x, int y, int type, int rotation)
{
	switch (type)
	{
	case(0):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 1] == 1 || board[x + 2][y + 1] == 1 || board[x + 3][y + 1] == 1)
			{
				for (int i = 0; i < 4; i++)
					board[x + i][y] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 4] == 1)
			{
				for (int i = 0; i < 4; i++)
					board[x][y + i] = 1;
				reset();
			}
			break;
		}
		case(2):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 1] == 1 || board[x + 2][y + 1] == 1 || board[x + 3][y + 1] == 1)
			{
				for (int i = 0; i < 4; i++)
					board[x + i][y] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 4] == 1)
			{
				for (int i = 0; i < 4; i++)
					board[x][y + i] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	case(1):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++)
						board[x + i][y + j] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++)
						board[x + i][y + j] = 1;
				reset();
			}			break;
		}
		case(2):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++)
						board[x + i][y + j] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					for (int j = 0; j < 2; j++)
						board[x + i][y + j] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	case(2):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					board[x + i][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i + 1][y + 1] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 2] == 1)
			{
				board[x + 1][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				board[x][y + 2] = 1;
				reset();
			}
			break;
		}
		case(2):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					board[x + i][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i + 1][y + 1] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 2] == 1)
			{
				board[x + 1][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				board[x][y + 2] = 1;
				reset();
			}	break;
		}
		}
		break;
	}
	case(3):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					board[x + i + 1][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 3] == 1)
			{
				board[x][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				board[x + 1][y + 2] = 1;
				reset();
			}			break;
		}
		case(2):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 2; i++)
					board[x + i + 1][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 3] == 1)
			{
				board[x][y] = 1;
				for (int i = 0; i < 2; i++)
					board[x + i][y + 1] = 1;
				board[x + 1][y + 2] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	case(4):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 2] == 1)
			{
				board[x][y] = 1;
				for (int i = 0; i < 3; i++)
					board[x + i][y + 1] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 1] == 1)
			{
				board[x][y] = 1; board[x+1][y] = 1;
				board[x][y + 1] = 1;
				board[x][y + 2] = 1;
				reset();
			}
			break;
		}
		case(2):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 1] == 1 || board[x + 1][y + 2] == 1)
			{
				for (int i = 0; i < 3; i++)
					board[x + i][y] = 1;
				board[x + 2][y + 1] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 3] == 1)
			{
									board[x+1][y] = 1;
									board[x+1][y + 1] = 1;
				board[x][y + 2] = 1;board[x + 1][y + 2] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	case(5):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 2] == 1)
			{
				board[x+2][y] = 1;
				for (int i = 0; i < 3; i++)
					board[x + i][y + 1] = 1;
				reset();
			}
			break;
		}
		case(1):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 3] == 1)
			{
				board[x][y] = 1; 
				board[x][y + 1] = 1;
				board[x][y + 2] = 1; board[x + 1][y+2] = 1;
				reset();
			}
			break;
		}
		case(2):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 1] == 1 || board[x + 2][y + 1] == 1)
			{
				for (int i = 0; i < 3; i++)
					board[x + i][y] = 1;
				board[x][y + 1] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 3] == 1)
			{
				board[x][y] = 1; board[x + 1][y] = 1;
								 board[x+1][y + 1] = 1;
								 board[x + 1][y + 2] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	case(6):
	{
		switch (rotation)
		{
		case(0):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 2] == 1)
			{
				board[x + 1][y] = 1;
				board[x][y + 1] = 1;	board[x + 1][y + 1] = 1; board[x + 2][y + 1] = 1;
				reset();
			}
			
			break;
		}
		case(1):
		{
			if (board[x][y + 3] == 1 || board[x + 1][y + 2] == 1)
			{
				board[x][y] = 1;
				board[x][y + 1] = 1; board[x + 1][y + 1] = 1;
				board[x][y + 2] = 1;
				reset();
			}
			
			break;
		}
		case(2):
		{
			if (board[x][y + 1] == 1 || board[x + 1][y + 2] == 1 || board[x + 2][y + 1] == 1)
			{
				board[x][y] = 1; board[x + 1][y] = 1; board[x + 2][y] = 1;
				board[x + 1][y + 1] = 1;
				reset();
			}
			break;
		}
		case(3):
		{
			if (board[x][y + 2] == 1 || board[x + 1][y + 3] == 1)
			{
				board[x + 1][y] = 1;
				board[x][y + 1] = 1;	board[x + 1][y + 1] = 1;
				board[x + 1][y + 2] = 1;
				reset();
			}
			break;
		}
		}
		break;
	}
	break;
}
}
void lineerase(void)
{
	for (int i = 20; i > 0; i--)
	{
		if (board[1][i] == 1 && board[2][i] == 1 && board[3][i] == 1 && board[4][i] == 1 && board[5][i] == 1 && board[6][i] == 1 && board[7][i] == 1 && board[8][i] == 1 && board[9][i] == 1 && board[10][i] == 1)
		{
			gotoXY(2, i - 1);
			for (int j = 1; j < 11; j++)
			{
				board[j][i] = 0;
				printf("  ");
			}
			for (int k = i; k > 1; k--)
			{
				for (int j = 1; j < 11; j++)
				{
					board[j][k] = board[j][k - 1];
				}
			}
			clear();
			


		}
	}
}
void initGame()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		board[i][0] = 1;
	for (int i = 1; i < BOARD_HEIGHT - 1; i++) {
		board[0][i] = 1; board[11][i] = 1;
	}
	for (int i = 0; i < BOARD_WIDTH; i++)
		board[i][21] = 1;

	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		printf("◈");
	}
	printf("\n");
	for (int i = 0; i < BOARD_HEIGHT - 3; i++)
	{
		printf("◈");
		for (int j = 0; j < (BOARD_WIDTH - 2); j++)
			printf("  ");
		printf("◈");
		printf("\n");
	}
	for (int i = 0; i < BOARD_WIDTH; i++)
		printf("◈");

}
void gotoXY(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int getGameAction(void)
{
		int keyValue, act = 0;
		if (_kbhit() != 0) //키보드를 눌렀는지 확인함 
		{
			keyValue = _getch();
			if (keyValue == 224) //특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값은 224값을 발생하고 두번째 값은 특수키에 따라 다름
			{
				keyValue = _getch(); //특수 키를 확인하기 위해 2번의 getch()함수를 호출해야 함
			}
			switch (keyValue)
			{
			case ESC:
				act = GAME_QUIT;//5
				break;
			case LEFT:
				act = MOVE_LEFT;//1
				break;
			case RIGHT:
				act = MOVE_RIGHT;//2
				break;
			case DOWN:
				act = MOVE_DOWN;//3
				break;
			case UP:
				act = CHANGE;//6
				break;
			default:
				break;
			}
		}
		return act;
}
void count(void)
{
	Sleep(10);
	times++;
	times_s++;
}
void save(void)
{
	exX = X;
	exY = Y;
	extype = Type;
	exrotation = Rotation;
}
void reset(void)
{
	X = 4, Y = 1, exX = 4, exY = 1, Rotation = 0, Type = rand() % 7 , collisions = 1; flag = 1;
}
void clear(void)
{
	for (int i = 20; i > 1; i--)
	{
		for (int j = 1; j < 11; j++)
		{
			if (board[j][i] == 0)
			{
				gotoXY(2 * j, i-1);
				printf("  ");
			}
			if (board[j][i] == 1)
			{
				gotoXY(2 * j, i-1);
				printf("★");
			}
		}
	}
}
