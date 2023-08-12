#include<iostream>
#include<math.h>
using namespace std;

struct shapes
{
	int type;
	double rightWingX;
	double rightWingY;
	double leftDownX;
	double leftDownY;

	double circlearea;
	double rectanglearea;

	double centerx;
	double centery;

}shape;
int main()
{
	shapes myshape[10];
	int check = 0;
	for (int i = 0; ++i;)
	{

		char input = 0;
		cout << "input: ";
		cin >> input;
		if (input == 113)
			break;
		else if (input == 112)
		{
			for (int j = 1; j <= check; ++j)
			{
				if (j == 10)
					break;
				cout << "result: ";
				cout << "shape: ";
				if (myshape[j].type == 1)
					cout << "Rectangle     ";
				else
					cout << "Circle     ";
				cout << "points(" << myshape[j].rightWingX << ", " << myshape[j].rightWingY << ") (" << myshape[j].leftDownX << ", ";
				cout << myshape[j].leftDownY << ")";

				cout << ", " << "center position(" << myshape[j].centerx << ", " << myshape[j].centery << ") ,";
				if (myshape[j].type == 1)
					cout << "area " << myshape[j].rectanglearea << endl << endl;
				else
					cout << "area " << myshape[j].circlearea << endl << endl;
			}
		}
		else
		{
			cin >> myshape[i].type >> myshape[i].rightWingX >> myshape[i].rightWingY >> myshape[i].leftDownX >> myshape[i].leftDownY;
			++check;
			myshape[i].centerx = (myshape[i].rightWingX + myshape[i].leftDownX) / 2;
			myshape[i].centery = (myshape[i].rightWingY + myshape[i].leftDownY) / 2;

			double resval = (myshape[i].rightWingX - myshape[i].leftDownX) * (myshape[i].rightWingX - myshape[i].leftDownX) + (myshape[i].rightWingY - myshape[i].leftDownY) * (myshape[i].rightWingY - myshape[i].leftDownY);
			myshape[i].circlearea = pow(sqrt(resval) / 2, 2);
			myshape[i].rectanglearea = (myshape[i].rightWingX - myshape[i].leftDownX) * (myshape[i].rightWingY - myshape[i].leftDownY);

			cout << "result: Shape: ";
			if (myshape[i].type == 1)
			{
				cout << "Rectangle, center position (x,y) = (" << myshape[i].centerx << ", " << myshape[i].centery << "), area ";
				cout << myshape[i].rectanglearea << endl << endl;
			}
			else
			{
				cout << "Circle, center position (x,y) = (" << myshape[i].centerx << ", " << myshape[i].centery << "), area ";
				cout << myshape[i].circlearea << endl << endl;
			}
		}
	}
	return 0;
}
