#include<opencv2\opencv.hpp>
#include<iostream>
#include<ctime>

using namespace std;
using namespace cv;

Mat gimmeinitialrawdata(int r, int c, int p)
{
	Mat A(r, c, CV_8U);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			A.at<uchar>(i, j) = 0;
		}
	}
	int numofpixelstobefilled = (r * c)*p / 100;
	cout << numofpixelstobefilled << endl;
	int randomi, randomj;
	
	int count = 0;
	while(count<numofpixelstobefilled)
	{
		randomi = r * (double(rand()) / RAND_MAX);
		randomj = c * (double(rand()) / RAND_MAX);
		if (A.at<uchar>(randomi, randomj) == 0)
		{
			A.at<uchar>(randomi, randomj) = 255;
			count = count++; //YES A SUCCESS
		}	
		else
		{
			//cout << "BEKAR ATTEMPT THA RE BABA" << endl;
		}
	}
	
	return A;
}
int main()
{
	srand(time(NULL));
	int rows, columns, perct;
	/*cout << "Enter the number of rows: " << endl;
	cin >> rows;
	cout << "Enter the number of columns: " << endl;
	cin >> columns;
	cout << "Enter the number of perect fill: " << endl;
	cin >> perct;*/
	rows = 100;
	columns = 100;
	perct = 10;
	Mat I = gimmeinitialrawdata(rows, columns, perct);
	namedWindow("Game of Life", CV_WINDOW_NORMAL);
	imshow("Game of Life", I);
	waitKey(0);
	
}