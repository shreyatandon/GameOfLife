#include<opencv2\opencv.hpp>
#include<iostream>
#include<ctime>

using namespace std;
using namespace cv;

int returnkrdepadosi(Mat A, int i, int j)
{
	int numberofaliveneighbors = 0;


	if (j + 1 <= A.cols - 1)
	{
		if (A.at<uchar>(i, j + 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (i + 1 <= A.rows - 1 && j + 1 <= A.cols - 1)
	{
		if (A.at<uchar>(i + 1, j + 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (i + 1 <= A.rows - 1)
	{
		if (A.at<uchar>(i + 1, j) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (i + 1 <= A.rows - 1 && j - 1 >= 0)
	{
		if (A.at<uchar>(i + 1, j - 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (j - 1 >= 0)
	{
		if (A.at<uchar>(i, j - 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (i - 1 >= 0 && j - 1 >= 0)
	{
		if (A.at<uchar>(i - 1, j - 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}


	if (i - 1 >= 0)
	{
		if (A.at<uchar>(i - 1, j) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	if (i - 1 >= 0 && j + 1 <= A.cols - 1)
	{
		if (A.at<uchar>(i - 1, j + 1) == 255)
		{
			numberofaliveneighbors++;
		}
	}

	return numberofaliveneighbors;

}

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
	while (count < numofpixelstobefilled)
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



Mat GOL(Mat INPUT)
{
	int rows = INPUT.rows;
	int cols = INPUT.cols;
	Mat OUTPUT(rows, cols,CV_8U);

	for (int i = 0; i < rows; i++)
	{

		for (int j = 0; j < cols; j++)
		{
			//The cell under consideration (i,j) is alive
			if (INPUT.at<uchar>(i, j) == 255)
			{
				int non = returnkrdepadosi(INPUT, i, j);
				//UNDERPOPULATED when non = 0 or 1
				if (non<2)
				{
					OUTPUT.at<uchar>(i, j) = 0;
				}

				//OVERPOPULATED when non = 4,5,6,7
				else if (non > 3)
				{
					OUTPUT.at<uchar>(i, j) = 0;
				}

				//OTHERWISE when non=2 or 3, then it will remain alive

				else
				{
					OUTPUT.at<uchar>(i, j) = 255;
				}
			}
			else //The cell under consideration (i,j) is dead
			{
				int non = returnkrdepadosi(INPUT, i, j);
				//The cell can become alive if there are exactly three alive neighbors
				if (non==3)
				{
					OUTPUT.at<uchar>(i, j) = 255;
				}
				else
				{
					OUTPUT.at<uchar>(i, j) = 0;
				}

			}

		}

	}


	return OUTPUT;

}

int main()
{
	srand(time(NULL));
	int rows, columns, perct, noi;
	/*cout << "Enter the number of rows: " << endl;
	cin >> rows;
	cout << "Enter the number of columns: " << endl;
	cin >> columns;
	cout << "Enter the number of perect fill: " << endl;
	cin >> perct;*/
	rows = 300;
	columns = 300;
	perct = 10;
	noi = 10000;

	Mat I = gimmeinitialrawdata(rows, columns, perct);
	namedWindow("Game of Life", CV_WINDOW_NORMAL);
	for (int i = 0; i < noi; i++)
	{
		imshow("Game of Life", I);
		I = GOL(I);
		waitKey(1);
	}
	waitKey(0);

}