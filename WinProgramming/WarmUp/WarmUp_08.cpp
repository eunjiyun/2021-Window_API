#include<iostream>
using namespace std;
//모양 종류 :
//3 마름모
//높이는 너비 /2 
int main()
{
	int shape = 0;
	int width = 0;
	cout << "Input command: ";
	cin >> shape >> width;

	if (width % 2 != 0 || width > 40 || shape > 6 || shape < 1)
		cout << "error";
	else
	{
		cout << "Result is: " << endl;
		switch (shape)
		{
		case 1:

			for (int i = 0; i < width / 2 - 1; ++i)
			{
				for (int j = 0; j < width; ++j)
				{

					if (j == width - 1 - 2 * i)
					{
						if (width / 2 % 2 != 0 && i == width / 4)
							cout << " ";
						else
							cout << "*";
					}

					else if (j == 2 * i)
						cout << "*";
					else
						cout << " ";
				}
				cout << endl;
			}
			for (int j = 0; j < width; ++j)
				if (j == 0 || j == width - 1)
					cout << "*";
				else
					cout << " ";

			break;
		case 2:
			for (int i = 0; i < width / 2; ++i)
			{
				for (int h = 0; h < i; ++h)
					cout << " ";
				for (int j = i; j < width - i; ++j)
				{
					cout << "*";
				}
				cout << endl;
			}
			break;
		case 3:
			for (int i = 0; i < width / 2; ++i)
			{
				for (int j = width / 2 - 1; j > i; --j)
				{
					cout << " ";
				}

				for (int j = 0; j < 2 * i + 1; ++j)
				{
					cout << "*";
				}
				cout << endl;
			}

			for (int i = 1; i < width / 2; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					cout << " ";
				}

				for (int j = 2 * width / 2 - 1; j > 2 * i; --j)
				{
					cout << "*";
				}
				cout << endl;
			}
			break;
		case 4:
			for (int i = 0; i < width / 2 - 1; ++i)
			{

				if (i < width / 4)
				{
					for (int j = 0; j < width; ++j)
					{

						if (2 * i < j && j < width - 1 - 2 * i)
							cout << " ";
						else
							cout << "*";

					}
					cout << endl;
				}
				else if (i == width / 4)
				{
					for (int j = 0; j < width; ++j)
					{

						cout << "*";
					}
					cout << endl;
				}
				else
				{
					for (int j = 0; j < width; ++j)
					{

						if (width - 1 - 2 * i <= j && j <= 2 * i)
							cout << " ";
						else
							cout << "*";
					}
					cout << endl;

				}

			}
			for (int j = 0; j < width; ++j)
			{
				if (j == 0 || j == width - 1)
					cout << "*";
				else
					cout << " ";
			}


			break;
		case 5:

			for (int i = 0; i < width / 2 - 1; ++i)
			{

				if (i < width / 4)
				{
					for (int j = 0; j < width; ++j)
					{

						if (2 * i <= j && j <= width - 1 - 2 * i)
							cout << "*";
						else
							cout << " ";
					}
					cout << endl;
				}
				else if (i == width / 4)
				{
					for (int j = 0; j < width; ++j)
					{
						if (width / 2 % 2 != 0)
						{
							if (2 * i <= j && j <= width - 1 - 2 * i)
								cout << "*";
							else
								cout << " ";
						}
						else
						{
							if (width - 1 - 2 * i <= j && j <= 2 * i)
								cout << "*";
							else
								cout << " ";
						}
					}
					cout << endl;
				}
				else
				{
					for (int j = 0; j < width; ++j)
					{

						if (width - 1 - 2 * i <= j && j <= 2 * i)
							cout << "*";
						else
							cout << " ";
					}
					cout << endl;

				}

			}
			for (int j = 0; j < width; ++j)
				cout << "*";



			break;
		case 6:
			for (int i = 0; i < width / 2; ++i)
			{
				if (i == 0 || i == width / 2 - 1)
				{
					for (int j = 0; j < width; ++j)
					{
						cout << "*";
					}
				}
				else
				{
					for (int j = 0; j < width; ++j)
					{
						if (j == 0 || j == width - 1)
							cout << "*";
						else
							cout << " ";
					}
				}
				cout << endl;
			}
			break;
		default:
			cout << "error";
			break;
		}
	}
	return 0;
}