#include<iostream>
using namespace std;

int thismonth(int, int);
int WhatDay(int, int, int);
void ShowThisMon(int, int);
void fri13();

int main()
{

	int year = 0;
	int month = 0;
	int day = 0;
	char trash;

	cout << 2021 << "/" << 03 << "/" << 01 << ": Monday";
	ShowThisMon(2021, 3);

	for (;;)
	{
		cin >> year;
		if (year > 2030 || year < 2020)
		{
			if (year != 70 && year != 102)
			{
				fri13();
				goto Skip01;
			}
			else
				cout << "Error" << endl;
			return 0;
		}
		cin >> trash;

		cin >> month;
		cin >> trash;

		cin >> day;


		switch (WhatDay(year, month, day))
		{
		case 0:
			cout << year << "/" << month << "/" << day << ": Monday";
			break;
		case 1:
			cout << year << "/" << month << "/" << day << ": Tuesday";
			break;
		case 2:
			cout << year << "/" << month << "/" << day << ": Wednesday";
			break;
		case 3:
			cout << year << "/" << month << "/" << day << ": Thursday";
			break;
		case 4:
			cout << year << "/" << month << "/" << day << ": Friday";
			break;
		case 5:
			cout << year << "/" << month << "/" << day << ": Saturday";
			break;
		case 6:
			cout << year << "/" << month << "/" << day << ": Sunday";
			break;
		}
		ShowThisMon(year, month);
	}
Skip01:
	return 0;
}

int  thismonth(int year, int month)
{
	int thismonthday = 0;
	switch (month)
	{
	case 1:
		thismonthday = 31;
		break;
	case 2:
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
			thismonthday = 29;
		else
			thismonthday = 28;
		break;
	case 3:
		thismonthday = 31;
		break;
	case 4:
		thismonthday = 30;
		break;
	case 5:
		thismonthday = 31;
		break;
	case 6:
		thismonthday = 30;
		break;
	case 7:
		thismonthday = 31;
		break;
	case 8:
		thismonthday = 31;
		break;
	case 9:
		thismonthday = 30;
		break;
	case 10:
		thismonthday = 31;
		break;
	case 11:
		thismonthday = 30;
		break;
	case 12:
		thismonthday = 31;
		break;
	}
	return thismonthday;
}
int WhatDay(int year, int month, int day)
{
	int date = 0;
	int thismonthday = 0;
	int howmanyday = 0;
	int mymonth = month;
	int myyear = year;



	if (myyear < 2021 || myyear == 2021 && month == 1 || myyear == 2021 && month == 2)
	{

		thismonthday = thismonth(year, month);
		if (myyear == 2021)
			mymonth += 12;
		for (int i = mymonth + 1; i < 15; ++i)
		{
			switch (i)
			{
			case 2:
				howmanyday += 29;
				break;
			case 3:
				howmanyday += 31;
				break;
			case 4:
				howmanyday += 30;
				break;
			case 5:
				howmanyday += 31;
				break;
			case 6:
				howmanyday += 30;
				break;
			case 7:
				howmanyday += 31;
				break;
			case 8:
				howmanyday += 31;
				break;
			case 9:
				howmanyday += 30;
				break;
			case 10:
				howmanyday += 31;
				break;
			case 11:
				howmanyday += 30;
				break;
			case 12:
				howmanyday += 31;
				break;
			case 13:
				howmanyday += 31;
				break;
			case 14:
				howmanyday += 28;
				break;
			}
		}
		date = howmanyday + thismonthday - day + 1;

	}


	else
	{
		int i = 0;
		if (myyear == 2021 && mymonth == 3)
			goto Skip00;
		for (;;)
		{

			for (i = mymonth - 1; i > 0; --i)
			{
				if (myyear == 2021 && i == 3)
					break;

				switch (i)
				{
				case 1:
					howmanyday += 31;
					break;
				case 2:
					if (myyear % 4 == 0 && myyear % 100 != 0 || myyear % 400 == 0)
						howmanyday += 29;
					else
						howmanyday += 28;
					break;
				case 3:
					howmanyday += 31;
					break;
				case 4:
					howmanyday += 30;
					break;
				case 5:
					howmanyday += 31;
					break;
				case 6:
					howmanyday += 30;
					break;
				case 7:
					howmanyday += 31;
					break;
				case 8:
					howmanyday += 31;
					break;
				case 9:
					howmanyday += 30;
					break;
				case 10:
					howmanyday += 31;
					break;
				case 11:
					howmanyday += 30;
					break;
				case 12:
					howmanyday += 31;
					break;
				}

			}
			if (myyear == 2021 && i == 3)
				break;
			--myyear;
			mymonth = 13;
		}
	Skip00:
		if (myyear == 2021 && mymonth == 3)
			date = day - 1;
		else
			date = 30 + howmanyday + day;

	}

	if (year < 2021 || year == 2021 && month == 1 || year == 2021 && month == 2)
		return (7 - date % 7) % 7;
	else
		return date % 7;
}
void ShowThisMon(int year, int month)
{


	int thismonthday = thismonth(year, month);
	int whatday = WhatDay(year, month, 1);
	cout << endl << "               " << year << "-" << month << endl;
	cout << "   Sunday      Monday      Tuesday    Wednesday   Thursday     Friday     Saturday" << endl;

	if (whatday != 6)
	{
		for (int h = 0; h < whatday + 1; ++h)
		{
			cout << "            ";
		}
	}

	for (int i = 1; i < thismonthday + 1; ++i)
	{

		printf("%7d     ", i);


		if ((i + whatday + 1) % 7 == 0)
			cout << endl;


	}
	cout << endl;
}
void fri13()
{
	int check = 0;
	for (int i = 2020; i < 2031; ++i)
	{
		for (int h = 1; h < 13; ++h)
		{
			if (WhatDay(i, h, 13) == 4)
			{
				cout << i << "-" << h << "-" << 13 << "   ";
				++check;
			}

		}
		if (check % 6 == 0)
			cout << endl;
	}
}

