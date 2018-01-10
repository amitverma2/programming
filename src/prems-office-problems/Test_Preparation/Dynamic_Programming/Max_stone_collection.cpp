#include <iostream>

using namespace std;


/*
One of the secret chambers in Hogwarts is full of philosopher’s stones. The floor of the chamber is covered by h × w square tiles, where there are h rows of tiles from front (first row) to back (last row) and w columns of tiles from left to right. Each tile has 1 to 100 stones on it. Harry has to grab as many philosopher’s stones as possible, subject to the following restrictions:

He starts by choosing any tile in the first row, and collects the philosopher’s stones on that tile. Then, he moves to a tile in the next row, collects the philosopher’s stones on the tile, and so on until he reaches the last row.
When he moves from one tile to a tile in the next row, he can only move to the tile just below it or diagonally to the left or right.
Given the values of h and w, and the number of philosopher’s stones on each tile, write a program to compute the maximum possible number of philosopher’s stones Harry can grab in one single trip from the first row to the last row.
Input

The first line consists of a single integer T, the number of test cases. In each of the test cases, the first line has two integers. The first integer h (1<=h<=100) is the number of rows of tiles on the floor. The second integer w (1<=w<=100) is the number of columns of tiles on the floor. Next, there are h lines of inputs. The ith line of these, specifies the number of philosopher’s stones in each tile of the ith row from the front. Each line has w integers, where each integer m (0<=m<=100) is the number of philosopher’s stones on that tile. The integers are separated by a space character.

Output

The output should consist of T lines, (1<=T<=100), one for each test case. Each line consists of a single integer, which is the maximum possible number of philosopher’s stones Harry can grab, in one single trip from the first row to the last row for the corresponding test case.

Example

Input:
1
6 5
3 1 7 4 2
2 1 3 1 1
1 2 2 1 8
2 2 1 5 3
2 1 4 4 4
5 2 7 5 1

Output:
32 	

//7+1+8+5+4+7=32

Solution:

A cell can be reached by 3 direction from above
so, for a cell aux[i][j] = max(aux[i-1][j-1], aux[i-1][j], aux[i-1][j+1])+num[i][j]
note that we can do inplace array calculation avoiding aux array, if we are not interested to maintain original values

Sample input:

1
6 5
3 1 7 4 2
2 1 3 1 1
1 2 2 1 8
2 2 1 5 3
2 1 4 4 4
5 2 7 5 1

Output:
32 	

//7+1+8+5+4+7=32
*/

#define ROW 6
#define COL 5

int num[ROW][COL] =
{
	{3, 1, 7, 4, 2},
	{2, 1, 3, 1, 1},
	{1, 2, 2, 1, 8},
	{2, 2, 1, 5, 3},
	{2, 1, 4, 4, 4},
	{5, 2, 7, 5, 1}
};

#define max(a,b) (a>b?a:b)
#define NINF 0x80000000

int calmaxStones()
{
	int aux[ROW][COL];
	for(int j=0; j<COL; j++)
		aux[0][j] = num[0][j];

	for(int i=1;i<ROW;i++)
	{
		for(int j=0;j<COL;j++)
		{
			switch (j)
			{
			case 0:
				aux[i][j] = max(aux[i-1][j], aux[i-1][j+1])+num[i][j];
				break;

			case COL-1:
				aux[i][j] = max(aux[i-1][j-1], aux[i-1][j])+num[i][j];
				break;

			default:
				aux[i][j] = max(aux[i-1][j-1], max(aux[i-1][j], aux[i-1][j+1]))+num[i][j];
				break;
			}
		}
	}

	int max_stones = NINF;
	for(int j=0;j<COL;j++)
	{
		cout << aux[ROW-1][j] << " ";
		if(max_stones<aux[ROW-1][j])
			max_stones = aux[ROW-1][j];
	}
	cout << endl;

	return max_stones;
}


int main() {

	int total = calmaxStones();
	cout << "Max stones that can be collected: " << total << endl;
	return 0;
}