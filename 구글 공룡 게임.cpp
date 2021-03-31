// ���� ũ�ҿ��� ���ͳ� ������ �ȵ� �� �ߴ� �̴ϰ����� ����!


#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

// �ܼ� â�� ũ�� �� ������ �����ϴ� �Լ�
void SetConsoleView()
{
	system("mode con:cons=100, lines=25");
	system("title Google Dinosaurs. By eikJae.");
}

// Ŀ���� ��ġ�� x, y�� �̵��ϴ� �Լ�
void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// Ű������ �Է��� �ް�, �Էµ� Ű�� ���� ��ȯ�ϴ� �Լ�
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

// ������ �׸��� �Լ�
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

// ��ֹ�(����)�� �׸��� �Լ�
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

// �浹 �� ���ӿ����� ����ִ� �Լ�
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

// �浹�� ��� true, �ƴϸ� false
bool isCollision(const int treeX, const int dinoY)
{
	// ������ X�� ������ ��ü �ʿ� �ִ� ���,
	// ������ ���̰� ������� �ʴٸ� �浹�� ó���Ѵ�
	GotoXY(0, 0);
	printf("treeX : %d, dinoY : %d", treeX, dinoY);
	if (treeX <= 8 && treeX >= 4 && dinoY > 8)
	{
		return true;
	}
	return false;
}

// ���� �Լ�
int main()
{
	SetConsoleView();

	while (true)
	{
		// ���� ���۽� �ʱ�ȭ
		bool isJumping = false;
		bool isBottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int treeX = TREE_BOTTOM_X;

		int score = 0;
		clock_t start, curr;  // ���� ���� �ʱ�ȭ
		start = clock();  // ���۽ð� �ʱ�ȭ
		while (true)
		{
			// �浹üũ. ������ x���� ������ y������ �Ǵ�
			if (isCollision(treeX, dinoY))
				break;

			// zŰ�� ���Ȱ�, �ٴ��� �ƴ� �� ����
			if (GetKeyDown() == 'z' && isBottom)
			{
				isJumping = true;
				isBottom = false;
			}

			// �������̶�� Y�� ����, ������ �����ٸ� Y�� ����
			if (isJumping)
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}

			// Y�� ����ؼ� �����ϴ� ���� �����ϱ� ���� �ٴ��� ����
			if (dinoY >= DINO_BOTTOM_Y)
			{
				dinoY = DINO_BOTTOM_Y;
				isBottom = true;
			}

			// ������ �������� (��, x����) ������ �ϰ�
			// ������ ��ġ�� ���� ������ ����, �ٽ� ������ ������ ��ȯ
			treeX -= 2;
			if (treeX <= 0)
			{
				treeX = TREE_BOTTOM_X;
			}

			// ������ �� ���� ������ ������ ���� ��Ȳ
			if (dinoY <= 3)
			{
				isJumping = false;
			}

			// ����� ������ �׸���
			DrawDino(dinoY);
			DrawTree(treeX);

			// ����ð� �޾ƿ���
			curr = clock();

			// 1�ʰ� �Ѿ��� ��
			if (((curr - start) / CLOCKS_PER_SEC) >= 1)
			{
				score++;  // ���ھ� ����
				start = clock();  // ���۽ð� �ʱ�ȭ
			}

			Sleep(60);
			system("cls"); // clear

			// ���� ����� 1�ʸ��� ���ִ� ���� �ƴ϶� �׻� ���
			// 1�ʰ� ������ ��, ++ ���ش�

			// Ŀ���� ��� �������� �ű�
			// �ܼ�â�� cols = 100�̴ϱ� 2*x �̹Ƿ�, 22���� �־���
			GotoXY(22, 0);

			//������ ���
			printf("score : %d ", score);
		}

		// ���� ����
		DrawGameOver(score);
	}
	return 0;
}