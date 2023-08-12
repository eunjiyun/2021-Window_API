#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;

int anagram(char*, char*);
int main()
{
	char fir[60] = { 0, };
	char sec[60] = { 0, };

	cout << "Input the first sentence: ";
	scanf_s(" %[^\n]", fir, sizeof(fir));
	cout << "Input the second sentence: ";
	scanf_s(" %[^\n]", sec, sizeof(sec));

	cout << "result: '";
	for (int i = 0; i < 60; ++i)
	{
		if (fir[i] == NULL)
			break;
		else
			cout << fir[i];
	}
	cout << "' and '";
	for (int i = 0; i < 60; ++i)
	{
		if (sec[i] == NULL)
			break;
		else
			cout << sec[i];
	}
	cout << "' are ";
	if (anagram(fir, sec))
		cout << "anagram!";
	else
		cout << "not anagram!";
}
int anagram(char* fir, char* sec)
{
	int count = 0;
	for (int i = 0; i < 60; ++i)
	{
		if (fir[i] == NULL)
			break;
		else if (fir[i] == 32)
			continue;
		else
		{
			count = 0;
			for (int j = 0; j < 60; ++j)
			{
				if (fir[i] == sec[j])
					break;
				else
				{
					++count;
					continue;
				}
			}
			if (count == 60)
				break;
		}
	}
	if (count == 60)
		return 0;
	else
		return 1;
}