#include<iostream>
#include <random>
using namespace std;

void show();
void ascend();
void descend();
void showeven();
void showodd();
void showmax();
void showmini();
void randsort();
char matrix[4][5] = { 0, };

random_device rd;//�õ尪
mt19937 gen(rd());// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
uniform_int_distribution<int> dis(65, 90);// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
uniform_int_distribution<int> ver(0, 3);
uniform_int_distribution<int> hor(0, 4);

int main()
{

	char order = 0;
	cout << "��İ�: " << endl;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 5; ++j)
			matrix[i][j] = dis(gen);

	show();
	while (order != 113)//	q :���α׷� ����
	{
		cout << "��ɾ� �Է�: ";
		cin >> order;
		if (order == 97)//a: 1�� 1 ���� �������� ���� ���� ������������ ����
		{
			ascend();
			show();
		}
		else if (order == 100)//d : 1�� 5 ���� �������� ���� ���� ������������ ����
		{
			descend();
			show();
		}
		else if (order == 116)//t :¦���� ����ϱ� ������ ���� �ƽ�Ű������ ��
		{
			showeven();
		}
		else if (order == 115)//s: Ȧ���� ����ϱ� ������ ���� �ƽ�Ű������ ��
		{
			showodd();
		}
		else if (order == 109)//	m :�ִ밪 ���
		{
			showmax();
		}
		else if (order == 110)//n	: �ּҰ� ���
		{
			showmini();
		}
		else if (order == 114)//r :�����ϰ� ������
		{
			randsort();
			show();
		}
		else if (order == 112)//p	: �ٽ� �Է¹ޱ� ����
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 5; ++j)
					matrix[i][j] = dis(gen);
			cout << "��İ�: " << endl;
			show();
		}
	}
	return 0;
}
void show()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			printf("%4c ", matrix[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}
void ascend()
{
	int temp = 0;

	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int h = 0; h < 5; ++h)
			{
				if (h < 4)
				{
					if (matrix[i][h] > matrix[i][h + 1])
					{
						temp = matrix[i][h];
						matrix[i][h] = matrix[i][h + 1];
						matrix[i][h + 1] = temp;

					}
				}
				else if (i < 3 && h == 4)
				{
					if (matrix[i][4] > matrix[i + 1][0])
					{
						temp = matrix[i][4];
						matrix[i][4] = matrix[i + 1][0];
						matrix[i + 1][0] = temp;
					}
				}
				else
					continue;
			}
		}
	}
}
void descend()
{
	{
		int temp = 0;

		for (int j = 0; j < 20; ++j)
		{
			for (int h = 4; h >= 0; --h)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (i < 3)
					{
						if (matrix[i][h] < matrix[i + 1][h])
						{
							temp = matrix[i + 1][h];
							matrix[i + 1][h] = matrix[i][h];
							matrix[i][h] = temp;
						}
					}
					else if (i == 3 && h > 0)
					{
						if (matrix[3][h] < matrix[0][h - 1])
						{
							temp = matrix[3][h];
							matrix[3][h] = matrix[0][h - 1];
							matrix[0][h - 1] = temp;

						}
					}
					else
						continue;
				}
			}
		}
	}
}

void showeven()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int h = 0; h < 5; ++h)
		{
			if (matrix[i][h] % 2 == 0)
				printf("%4c ", matrix[i][h]);
			else
				printf("%4c ", 92);
		}
		cout << endl;
	}
}
void showodd()
{
	for (int i = 0; i < 4; ++i)
	{
		for (int h = 0; h < 5; ++h)
		{
			if (matrix[i][h] % 2 != 0)
				printf("%4c ", matrix[i][h]);
			else
				printf("%4c ", 92);
		}
		cout << endl;
	}
}
void showmax()
{
	int max = matrix[0][0];
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int h = 0; h < 5; ++h)
			{
				if (matrix[i][h] == 92)
					continue;
				else if (matrix[i][h] >= max)
					max = matrix[i][h];
				else
					matrix[i][h] = 42;
			}
		}
	}
	show();
}
void showmini()
{
	int min = matrix[0][0];
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int h = 0; h < 5; ++h)
			{
				if (matrix[i][h] == 42)
					continue;
				else if (matrix[i][h] != 0 && matrix[i][h] <= min)
					min = matrix[i][h];
				else
					matrix[i][h] = 92;
			}
		}
	}
	show();
}

void randsort()
{
	int tmp = 0;
	int fir = 0;
	int sec = 0;
	for (int j = 0; j < 20; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int h = 0; h < 5; ++h)
			{
				tmp = matrix[i][h];
				fir = ver(gen);
				sec = hor(gen);
				matrix[i][h] = matrix[fir][sec];
				matrix[fir][sec] = tmp;
			}
		}
	}
}