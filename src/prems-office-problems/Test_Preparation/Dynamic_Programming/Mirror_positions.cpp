#include <iostream>

using namespace std;


/*
Sherlock is stuck. There is a N X N grid in which some cells are empty (denoted by ‘.’), while some cells have rocks in them (denoted by ‘#’). Sherlock is on the South of the grid. He has to watch what is happening on the East of the grid. He can place a mirror at 45 degrees on an empty cell in the grid, so that he'll see what is happening on East side by reflection from the mirror.


But, if there's a rock in his line of sight, he won't be able to see what's happening on East side. For example, following image shows all possible cells in which he can place the mirror. 


You have to tell Sherlock in how many possible cells he can place the mirror and see what's happening on East side.
Input

First line, T, the number of testcases. Each testcase will consist of N in one line. Next N lines each contain N characters.
Output

For each testcase, print the number of possible options where mirror can be placed to see on the East side.
Constraints

1 ≤ T ≤ 10
1 ≤ N ≤ 1000
 
Example

Input:
2
3
#..
#..
#..
3
#.#
#.#
#.#

Output:
6
0

*/

#define N 4

char arr[N][N] = 
{
	{'#', '.', '#', '.'},
	{'#', '.', '.', '.'},
	{'#', '.', '.', '.'},
	{'.', '.', '.', '.'},
};

int findmaxsight()
{
	int count = 0;
	bool row[N];
	bool col[N];

	for(int i=0;i<N;i++)
		row[i] = col[i] = true;

	for(int i=N-1;i>=0;i--)
	{
		for(int j=N-1;j>=0;j--)
		{
			if(arr[i][j] == '#')
			{
				row[i] = false;
				col[j] = false;
			}
			else if(arr[i][j] == '.')
			{
				if(row[i] && col[j])
					count++;
			}
		}
	}
	return count;
}


int main()
{
	int answer;
	answer = findmaxsight();
	cout << "Max Sight positions: " << answer << endl;
	return 0;
}