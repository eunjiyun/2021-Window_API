#include<iostream>
#include<cstring>
#include<stdlib.h>

using namespace std;

void show(char*);
void copitalLet(char*);
void blankCharac(char*);
int wordCount(char*);
void reverse(char*);
void spaceHandle(char*);

int main()
{
	char senten[60] = { 0, };
	char order = 0;
	cout << "Input sentence: ";
	scanf_s(" %[^\n]", senten, sizeof(senten));
	while (order != 113 && order != 81)//	q / Q :113   81//	���α׷��� ����
	{
		cout << "��ɾ�: ";

		cin >> order;
		if (order == 101 || order == 69)//e / E: 101  69//�ܾ e �Ǵ� E �ڰ� �ִ� ��쿡�� �� �ܾ ��� �빮�ڷ� �ٲٰ� ���32  90>=�빮��
		{
			copitalLet(senten);
			show(senten);
		}
		else if (order == 102 || order == 70)//f / F :102 70//	��� ���鿡(60 ���� �迭����) ������ ����(@, %, # �Ǵ� �� �ְ� ���
		{
			blankCharac(senten);
			show(senten);
		}
		else if (order == 108 || order == 76)//		l / L: 108  76//�ܾ��� ������ ���
			cout << "Result: " << wordCount(senten) << " words" << endl;
		else if (order == 99 || order == 67)//c / C :99   67//	�빮�ڴ� �ҹ��ڷ�, �ҹ��ڴ� �빮�ڷ� �ٲٱ�
		{
			reverse(senten);
			show(senten);
		}
		else if (order == 113 || order == 81)
			cout << "���α׷� ����" << endl;
		else
			cout << "error" << endl;
	}
	return 0;
}
void show(char* sentence)
{
	for (int i = 0; i < 60; ++i)
		cout << sentence[i];
	cout << endl;
}
void copitalLet(char* sentence)
{
	spaceHandle(sentence);
	int h = 0;
	for (int i = 0; i < 60; ++i)
	{
		if (sentence[i] == 101 || sentence[i] == 69)
		{
			for (h = i; h >= 0; --h)
			{
				if (sentence[h] == 32 || h == 0)
				{
					if (h == 0)
					{
						--h;
						break;
					}
					else
						break;
				}
			}
			for (int j = h + 1; j < 60; ++j)
			{
				if (sentence[j] == 32)
					break;
				else if (sentence[j] > 90)
					sentence[j] -= 32;
				else
					continue;
			}
		}
	}
}
void blankCharac(char* sentence)
{
	spaceHandle(sentence);
	for (int i = 0; i < 60; ++i)
	{
		if (sentence[i] > 64 && sentence[i] < 91)
			continue;
		else if (sentence[i] > 96 && sentence[i] < 123)
			continue;
		else if (sentence[i] == 46)
			continue;
		else
			sentence[i] = 37;
	}
}//�빮��, �ҹ���, ����, ��ħǥ, ��, �����Ⱚ
//(sentence[i] > 64 && sentence[i] < 91)
//(sentence[i] > 96 && sentence[i] < 123)
//32
//46
//NULL
int wordCount(char* sentence)
{
	spaceHandle(sentence);
	int count = 0;
	for (int i = 0; i < 60; ++i)//.�� 46
	{
		if (sentence[i] == 46)
			break;
		else if (sentence[i] == 32 || sentence[i] == 37)
			++count;
		else
			continue;
	}
	return count + 1;
}
void reverse(char* sentence)
{
	spaceHandle(sentence);
	for (int i = 0; i < 60; ++i)
	{
		if (sentence[i] > 96 && sentence[i] < 123)
			sentence[i] -= 32;
		else if (sentence[i] > 64 && sentence[i] < 91)
			sentence[i] += 32;
		else
			continue;
	}
}
void spaceHandle(char* sentence)
{
	int location = 0;
	int location2 = 0;
	for (int i = 0; i < 60; ++i)
	{
		if (sentence[i] == 32 && sentence[i + 1] == 32)
		{
			location = i + 1;
			for (int j = location; j < 60; ++j)
			{
				if (sentence[j] > 64 && sentence[j] < 91 || sentence[j] > 96 && sentence[j] < 123)
				{
					location2 = j;
					break;
				}
			}
			for (int h = location2; h < 60; ++h)
				sentence[h - location2 + location] = sentence[h];
		}
		else
			continue;
	}
}

