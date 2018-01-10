#include <iostream>

using namespace std;

/*
Problem Statement :
-----------------
http://www.spoj.com/problems/SAMER08C/

Little Charlie is a nice boy addicted to candies. 
He is even a subscriber to All Candies Magazine and was selected to participate in the International Candy Picking Contest.

In this contest a random number of boxes containing candies are disposed in M rows with N columns each (so, there are a total of M ×N boxes). 
Each box has a number indicating how many candies it contains.

The contestant can pick a box (any one) and get all the candies it contains. 
But there is a catch (there is always a catch): when choosing a box, 
all the boxes from the rows immediately above and immediately below are emptied, 
as well as the box to the left and the box to the right of the chosen box. 
The contestant continues to pick a box until there are no candies left.


For small values of M and N, Charlie can easily find the maximum number of candies he can pick, 
but when the numbers are really large he gets completely lost. 
Can you help Charlie maximize the number of candies he can pick?

Input
The input contains several test cases. The first line of a test case contains two positive integers M and N (1 ≤ M ×N ≤ 105), 
separated by a single space, indicating the number of rows and columns respectively. Each of the following M lines contains N integers 
separated by single spaces, each representing the initial number of candies in the corresponding box. 
Each box will have initially at least 1 and at most 103 candies.

Output

For each test case in the input, your program must print a single line, containing a single value, 
I athe integer indicating the maximum number of candies that Charlie can pick.

Input:
-----
3
5 5
1 8 2 1 9
1 7 3 5 2
1 2 10 3 10
8 4 7 9 1
7 1 3 1 6
4 4
10 1 1 10
1 1 1 1
1 1 1 1
10 1 1 10
2 4
9 10 2 7
5 1 1 5

Output:
------
#1 54
#2 40
#3 17

*/

#define MAX 1000

// ROW length
int M;
// Col length
int N;

//array
int a[MAX][MAX];

// dp value for max row values
int dp[MAX];

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

int getMaxArray(int* arr, int n)
{
	int incl = arr[0];
	int excl = 0;
	int excl_new;
	int i;

	for (i = 1; i < n; i++)
	{
		/* current max excluding i */
		excl_new = (incl > excl) ? incl : excl;

		/* current max including i */
		incl = excl + arr[i];
		excl = excl_new;
	}

	/* return max of incl and excl */
	return ((incl > excl) ? incl : excl);
}


int findMax()
{
	for (int i = 0; i < M; i++)
		dp[i] = getMaxArray(a[i], N);

	int ans = getMaxArray(dp, M);

	return ans;

}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> M >> N;

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
				cin >> a[i][j];
		}

		int answer = findMax();

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}