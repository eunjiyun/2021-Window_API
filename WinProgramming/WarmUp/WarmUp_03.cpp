#include<iostream>
#include < windows.h >
#include <random>
using namespace std;

random_device rd;//시드값
mt19937 gen(rd());// random_device 를 통해 난수 생성 엔진을 초기화 한다.
uniform_int_distribution<int> dis(0, 9);// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.

void showBoard(struct goBoard*);
struct goBoard
{
	char board[10][10] = { NULL };
	char player1 = 35;//샵
	char player2 = 37;//퍼센트

	int p1x;
	int p1y;
	int p2x;
	int p2y;

};
int main()
{
	struct goBoard game;
	char order = 0;
	int tmp = 0;
	game.p1x = dis(gen);
	game.p1y = dis(gen);
	game.p2x = dis(gen);
	game.p2y = dis(gen);

	game.board[game.p1y][game.p1x] = game.player1;
	game.board[game.p2y][game.p2x] = game.player2;
	showBoard(&game);

	for (int i = 1; ++i;)
	{
		cout << "Input command: ";
		cin >> order;
		if (order == 113)//q
		{
			cout << endl << "프로그램 종료" << endl;;
			break;
		}
		else if (i % 2 == 0)//p1 샵
		{
			game.board[game.p1y][game.p1x] = NULL;
			if (order == 87 || order == 119)//w
			{
				if (game.p1y - 2 < 0)
				{
					game.board[9][game.p1x] = game.player1;
					game.p1y = 9;
				}
				else
				{
					if ((game.p1x == game.p2x) && (game.p1y - 1 == game.p2y + 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1x == game.p2x - 1) && (game.p1y - 1 == game.p2y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1x == game.p2x + 1) && (game.p1y - 1 == game.p2y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					game.board[game.p1y - 1][game.p1x] = game.player1;
					game.p1y = game.p1y - 1;
				}
			}
			else if (order == 65 || order == 97)//a
			{
				if (game.p1x - 2 < 0)
				{
					game.board[game.p1y][9] = game.player1;
					game.p1x = 9;
				}
				else
				{
					if ((game.p1y == game.p2y) && (game.p1x - 1 == game.p2x + 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1y == game.p2y + 1) && (game.p1x - 1 == game.p2x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1y == game.p2y - 1) && (game.p1x - 1 == game.p2x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					game.board[game.p1y][game.p1x - 1] = game.player1;
					game.p1x = game.p1x - 1;
				}
			}
			else if (order == 83 || order == 115)//s
			{
				if (game.p1y + 2 > 9)
				{
					game.board[0][game.p1x] = game.player1;
					game.p1y = 0;
				}
				else
				{
					if ((game.p1x == game.p2x) && (game.p1y + 1 == game.p2y - 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1x == game.p2x + 1) && (game.p1y + 1 == game.p2y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1x == game.p2x - 1) && (game.p1y + 1 == game.p2y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					game.board[game.p1y + 1][game.p1x] = game.player1;
					game.p1y = game.p1y + 1;
				}
			}
			else if (order == 68 || order == 100)//d
			{
				if (game.p1x + 2 > 9)
				{
					game.board[game.p1y][0] = game.player1;
					game.p1x = 0;
				}
				else
				{
					if ((game.p1y == game.p2y) && (game.p1x + 1 == game.p2x - 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1y == game.p2y + 1) && (game.p1x + 1 == game.p2x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					else if ((game.p1y == game.p2y - 1) && (game.p1x + 1 == game.p2x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p2y][game.p2x] = game.player2;
					}
					game.board[game.p1y][game.p1x + 1] = game.player1;
					game.p1x = game.p1x + 1;
				}
			}
		}
		else//p2 퍼센트
		{
			game.board[game.p2y][game.p2x] = NULL;
			if (order == 73 || order == 105)//i
			{
				if (game.p2y - 2 < 0)
				{
					game.board[9][game.p2x] = game.player2;
					game.p2y = 9;
				}
				else
				{
					if ((game.p1x == game.p2x) && (game.p2y - 1 == game.p1y + 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1x - 1 == game.p2x) && (game.p2y - 1 == game.p1y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1x + 1 == game.p2x) && (game.p2y - 1 == game.p1y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					game.board[game.p2y - 1][game.p2x] = game.player2;
					game.p2y = game.p2y - 1;
				}
			}
			else if (order == 74 || order == 106)//j
			{
				if (game.p2x - 2 < 0)
				{
					game.board[game.p2y][9] = game.player2;
					game.p2x = 9;
				}
				else
				{
					if ((game.p1y == game.p2y) && (game.p2x - 1 == game.p1x + 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1y - 1 == game.p2y) && (game.p2x - 1 == game.p1x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1y + 1 == game.p2y) && (game.p2x - 1 == game.p1x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					game.board[game.p2y][game.p2x - 1] = game.player2;
					game.p2x = game.p2x - 1;
				}
			}
			else if (order == 75 || order == 107)//k
			{
				if (game.p2y + 2 > 9)
				{
					game.board[0][game.p2x] = game.player2;
					game.p2y = 0;
				}
				else
				{
					if ((game.p1x == game.p2x) && (game.p2y + 1 == game.p1y - 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1x - 1 == game.p2x) && (game.p2y - 1 == game.p1y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1x + 1 == game.p2x) && (game.p2y - 1 == game.p1y))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					game.board[game.p2y + 1][game.p2x] = game.player2;
					game.p2y = game.p2y + 1;
				}
			}
			else if (order == 76 || order == 108)//l
			{
				if (game.p2x + 2 > 9)
				{
					game.board[game.p2y][0] = game.player2;
					game.p2x = 0;
				}
				else
				{
					if ((game.p1y == game.p2y) && (game.p2x + 1 == game.p1x - 1))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1y - 1 == game.p2y) && (game.p2x + 1 == game.p1x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					else if ((game.p1y + 1 == game.p2y) && (game.p2x + 1 == game.p1x))
					{
						Beep(340, 500);
						tmp = game.player1;
						game.player1 = game.player2;
						game.player2 = tmp;
						game.board[game.p1y][game.p1x] = game.player1;
					}
					game.board[game.p2y][game.p2x + 1] = game.player2;
					game.p2x = game.p2x + 1;
				}
			}
		}
		showBoard(&game);
	}
	return 0;
}
void showBoard(struct goBoard* myboard)
{
	cout << "---------------------" << endl;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (myboard->board[i][j] == NULL)
				cout << "| ";
			else
				cout << "|" << myboard->board[i][j];
		}
		cout << "|" << endl << "---------------------" << endl;
	}
}
