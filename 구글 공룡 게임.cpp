// 구글 크롬에서 인터넷 연결이 안될 시 뜨는 미니게임을 설계!


#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

// 콘솔 창의 크기 및 제목을 지정하는 함수
void SetConsoleView()
{
	system("mode con:cons=100, lines=25");
	system("title Google Dinosaurs. By eikJae.");
}

// 커서의 위치를 x, y로 이동하는 함수
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

// 공룡을 그리는 함수
void DrawDino(int dinoY)
{
	GotoXY(0, dinoY);
	static bool legFlag = true;
	printf("        $$$$$$$ \n");
	printf("       $$ $$$$$$\n");
	printf("       $$$$$$$$$\n");
	printf("$      $$$      \n");
	printf("$$     $$$$$$$  \n");
	printf("$$$   $$$$$     \n");
	printf(" $$  $$$$$$$$$$ \n");
	printf(" $$$$$$$$$$$    \n");
	printf("  $$$$$$$$$$    \n");
	printf("    $$$$$$$$    \n");
	printf("     $$$$$$     \n");
	if (legFlag)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		legFlag = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		legFlag = true;
	}
}

// 장애물(나무)를 그리는 함수
void DrawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("$$$$");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 3);
	printf(" $$ ");
	GotoXY(treeX, TREE_BOTTOM_Y + 4);
	printf(" $$ ");
}

// 충돌 시 게임오버를 띄워주는 함수
void DrawGameOver(const int score)
{
	system("cls");
	int x = 18;
	int y = 8;
	GotoXY(x, y);
	printf("===========================");
	GotoXY(x, y + 1);
	printf("======G A M E O V E R======");
	GotoXY(x, y + 2);
	printf("===========================");
	GotoXY(x, y + 5);
	printf("SCORE : %d", score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}

// 충돌한 경우 true, 아니면 false
bool isCollision(const int treeX, const int dinoY)
{
	// 나무의 X가 공룡의 몸체 쪽에 있는 경우,
	// 공룡의 높이가 충분하지 않다면 충돌로 처리한다
	GotoXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY);
	if (treeX <= 8 && treeX >= 4 && dinoY > 8)
	{
		return true;
	}
	return false;
}

// 메인 함수
int main()
{
	SetConsoleView();

	while (true)
	{
		// 게임 시작시 초기화
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr;  // 점수 변수 초기화
		start = clock();  // 시작시간 초기화
		while (true)
		{
			// 충돌체크. 나무의 x값과 공룡의 y값으로 판단
			if (isCollision(treeX, dinoY))
				break;

			// z키가 눌렸고, 바닥이 아닐 때 점프
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			// 점프중이라면 Y를 감소, 점프가 끝났다면 Y를 증가
			if (isJumping)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			// Y가 계속해서 증가하는 것을 방지하기 위해 바닥을 지정
			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			// 나무가 왼쪽으로 (즉, x음수) 가도록 하고
			// 나무의 위치가 왼쪽 끝으로 가면, 다시 오른쪽 끝으로 소환
			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			// 점프의 맨 위를 찍으면 점프가 끝난 상황
			if (dinoY <= 3)
			{
				isJumping = false;
			}

			// 공룡과 나무를 그린다
			DrawDino(dinoY);
			DrawTree(treeX);

			// 현재시간 받아오기
			curr = clock();

			// 1초가 넘었을 때
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)
			{
				score++;  // 스코어 증가
				start = clock();  // 시작시간 초기화
			}

			Sleep(60);
			system("cls"); // clear

			// 점수 출력을 1초마다 해주는 것이 아니라 항상 출력
			// 1초가 지났을 때, ++ 해준다

			// 커서를 가운데 위쪽으로 옮김
			// 콘솔창이 cols = 100이니까 2*x 이므로, 22정도 넣어줌
			GotoXY(22, 0);

			//점수를 출력
			printf("score : %d ", score);
		}

		// 게임 오버
		DrawGameOver(score);
	}
	return 0;
}