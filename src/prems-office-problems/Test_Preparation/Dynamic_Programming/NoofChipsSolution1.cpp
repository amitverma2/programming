#include <iostream>

using namespace std;

#define ROW_MAX 10
#define COL_MAX 25

int a[ROW_MAX][COL_MAX] =
{

	/*
	{0,0,0,1,1},
	{0,1,1,1,1},
	{1,1,1,1,0},
	{1,1,1,1,0}
	*/
	/*
	{1,1,0,0,0},
	{1,1,1,1,0},
	{1,1,0,1,1},
	{1,1,1,1,1}
	*/
	/*

	{0,0,1,1,0},
	{0,1,1,1,1},
	{0,1,1,1,1},
	{0,0,0,0,0}
	*/

	/*
	{0,0,0,0},
	{1,1,1,1},
	{1,1,1,1},
	{0,1,1,0}
	*/



	{0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
	{0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
	{0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
	{0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1},
	{0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,1}





};

int func_maximum = 0;

int final_max = 0;


void  count(int x, int y, int cur_val, int max_sq)
{
	//cout << "x=" << x << ",y=" << y << endl;
	func_maximum++;

	if(final_max < cur_val)
		final_max = cur_val;

	if(cur_val+max_sq < final_max)
		return;

	int i,j;
	bool flag = false;

	for(i=x;i<ROW_MAX;i++)
	{
		j =y;
		while(j<COL_MAX)
		{
			if(a[i][j] && (i+1<ROW_MAX && a[i+1][j]) && (j+1<COL_MAX && a[i][j+1]) && (i+1<ROW_MAX && j+1<COL_MAX && a[i+1][j+1]))
			{
				flag = true;
				break;
			}
			j++;
		}
		if(flag)
			break;
		y=0;
	}

	if(i== ROW_MAX && j == COL_MAX)
		return;

	if(func_maximum%2 == 1)
	{
		a[i][j] = 0;
		count(i, j+1, cur_val, max_sq-1);
		a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 0;
		count(i, j+2, cur_val+1, max_sq-1);
		a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1;
	}
	else
	{
		a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 0;
		count(i, j+2, cur_val+1, max_sq-1);
		a[i][j] = a[i+1][j] = a[i][j+1] = a[i+1][j+1] = 1;
		a[i][j] = 0;
		count(i, j+1, cur_val, max_sq-1);
		a[i][j] = 1;
	}
}

void printmatrix()
{
	for(int i=0; i<ROW_MAX; i++)
	{
		for(int j=0;j<COL_MAX;j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	int max_sq = 0;
	for(int i=0;i<ROW_MAX;i++)
	{
		for(int j=0;j<COL_MAX;j++)
		{
			/*
			if(a[i][j])
			max_sq++;
			*/
			if(a[i][j] && (i+1<ROW_MAX && a[i+1][j]) && (j+1<COL_MAX && a[i][j+1]) && (i+1<ROW_MAX && j+1<COL_MAX && a[i+1][j+1]))
			{
				max_sq++;
			}
		}
	}

	cout << "Max square would be \n" << max_sq << endl;



	count(0,0,0,max_sq);
	cout << final_max << endl;
	printmatrix();
	cout << func_maximum << endl;
	return 0;
}