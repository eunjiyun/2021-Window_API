#include<iostream>
using namespace std;
int error();
void calcul();


void priority();
int oper(int, char, int);
void calcu();
int val[5] = { 0, };
char ope[4] = { 0, };
int resval[4] = { 0, };

int result = 0;


int main()
{
	cout << "Input numbers: ";
	cin >> val[0] >> ope[0] >> val[1] >> ope[1] >> val[2] >> ope[2] >> val[3] >> ope[3] >> val[4];

	if (error() == 1)
		return 0;
	else
		calcul();

}
int error()
{
	if (val[0] > 99 || val[1] > 99 || val[2] > 99 || val[3] > 99 || val[4] > 99)
	{
		cout << "error";
		return 1;
	}
	else if (ope[0] == 47 && val[1] == 0 || ope[1] == 47 && val[2] == 0 || ope[2] == 47 && val[3] == 0 || ope[3] == 47 && val[4] == 0)
	{
		cout << "error";
		return 1;
	}
	else if (ope[0] != 43 && ope[0] != 45 && ope[0] != 42 && ope[0] != 47)
	{
		cout << "error";
		return 1;
	}
	else if (ope[1] != 43 && ope[1] != 45 && ope[1] != 42 && ope[1] != 47)
	{
		cout << "error";
		return 1;
	}
	else if (ope[2] != 43 && ope[2] != 45 && ope[2] != 42 && ope[2] != 47)
	{
		cout << "error";
		return 1;
	}
	else if (ope[3] != 43 && ope[3] != 45 && ope[3] != 42 && ope[3] != 47)
	{
		cout << "error";
		return 1;
	}
	else
		return 0;
}
//   +43
//   -45


//   *42
//   /47
void calcul()
{

	if (ope[0] == 0)
	{
		cout << " ";
	}
	else
	{
		switch (ope[0])
		{
		case 43:
			resval[0] = val[0] + val[1];
			break;
		case 45:
			resval[0] = val[0] - val[1];
			break;
		case 42:
			resval[0] = val[0] * val[1];
			break;
		case 47:
			resval[0] = val[0] / val[1];
			break;
		}
		switch (ope[1])
		{
		case 43:
			resval[1] = resval[0] + val[2];
			break;
		case 45:
			resval[1] = resval[0] - val[2];
			break;
		case 42:
			resval[1] = resval[0] * val[2];
			break;
		case 47:
			resval[1] = resval[0] / val[2];
			break;
		}
		switch (ope[2])
		{
		case 43:
			resval[2] = resval[1] + val[3];
			break;
		case 45:
			resval[2] = resval[1] - val[3];
			break;
		case 42:
			resval[2] = resval[1] * val[3];
			break;
		case 47:
			resval[2] = resval[1] / val[3];
			break;
		}
		switch (ope[3])
		{
		case 43:
			resval[3] = resval[2] + val[4];
			break;
		case 45:
			resval[3] = resval[2] - val[4];
			break;
		case 42:
			resval[3] = resval[2] * val[4];
			break;
		case 47:
			resval[3] = resval[2] / val[4];
			break;
		}
	}


	cout << "Result: " << val[0] << ope[0] << val[1] << ope[1] << val[2] << ope[2] << val[3] << ope[3] << val[4] << "= " << resval[3] << endl;
}
//   +43
//   -45


//   *42
//   /47
void priority()
{

	/*for (int i = 0; i < 4; ++i)
	{
		if (ope[i] == 42 || ope[i] == 47)
		{
			if (val[i] == NULL && val[i + 1] == NULL)
				resval[i + 1] = oper(resval[i], ope[i + 1], val[i + 2]);
			else
				resval[i] = oper(val[i], ope[i], val[i + 1]);
		}
		else
			continue;



	}*/
	int j = 0;
	int h = 0;
	for (int i = 0; i < 4; ++i)
	{
		if (ope[i] == 42 || ope[i] == 47)
		{
			for (j = 0; j < 9; ++j)
				if (val[j] != 0)
					break;
			for (h = j + 1; h < 9; ++h)
				if (val[h] != 0)
					oper(val[j], ope[i], val[h]);

		}
		else
			continue;



	}

}

int oper(int former, char operate, int latter)
{

	switch (operate)
	{
	case 43:
		result = former + latter;
		former = NULL;
		latter = NULL;
		operate = NULL;
		break;
	case 45:
		result = former - latter;
		former = NULL;
		latter = NULL;
		operate = NULL;
		break;
	case 42:
		result = former * latter;
		former = NULL;
		latter = NULL;
		operate = NULL;
		break;
	case 47:
		result = former / latter;
		former = NULL;
		latter = NULL;
		operate = NULL;
		break;
	}
	return result;
}
void calcu()
{
	void priority();
	for (int i = 0; i < 4; ++i)
	{

		if (val[i] == NULL && val[i + 1] == NULL)
		{
			if (val[i + 3 == NULL] && val[i + 2] == NULL)
				resval[i + 1] = oper(resval[i], ope[i + 1], resval[i + 2]);
			else if (val[i + 2] != NULL)
				resval[i + 1] = oper(resval[i], ope[i + 1], val[i + 2]);
		}

		else
			resval[i] = oper(val[i], ope[i], val[i + 1]);

		cout << "Result: " << val[0] << ope[0] << val[1] << ope[1] << val[2] << ope[2] << val[3] << ope[3] << val[4] << "= " << result << endl;


	}
}

