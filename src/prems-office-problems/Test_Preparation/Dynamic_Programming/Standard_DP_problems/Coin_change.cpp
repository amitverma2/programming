#include <iostream>

using namespace std;

/*
Problem Statement :
-----------------
http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/

Given a value N, if we want to make change for N cents, and we have infinite supply of each of S = { S1, S2, .. , Sm} valued coins, 
how many ways can we make the change? The order of coins doesn’t matter.

For example, for N = 4 and S = {1,2,3}, 
there are four solutions: 
{1,1,1,1},{1,1,2},{2,2},{1,3}. 
So output should be 4. 

For N = 10 and S = {2, 5, 3, 6}, 
there are five solutions: 
{2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} and {5,5}. 
So the output should be 5.

Input:
-----
2
4 3
1 2 3
10 4
2 5 3 6


Output:
------
#1 4
#2 5


*/

#define MAX 100

// value n
int N;

// No of coins
int M;

// value of each coin
int S[MAX];

int dp[MAX+1][MAX+1];

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

// i items, w weight
int coinchangeUtil(int n, int m)
{
	// If n is 0 then there is 1 solution (do not include any coin)
	if (n == 0)
		return 1;

	// If n is less than 0 then no solution exists
	if (n < 0)
		return 0;

	// If there are no coins and n is greater than 0, then no solution exist
	if (m <= 0 && n >= 1)
		return 0;


	int& res = dp[n][m];

	if (res != -1)
		return res;

	int val1, val2;
    
	// case 1: lets take this mth coin as part of solution
	val1 = coinchangeUtil(n - S[m - 1], m);

	// case 2: mth coin is not part of solution
	val2 = coinchangeUtil(n, m - 1);

	return res = (val1+val2);
}

int coinchange()
{
	return coinchangeUtil(N, M);
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N >> M;

		for (int i = 0; i < M; i++)
			cin >> S[i];

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= M; j++)
				dp[i][j] = -1;
		}

		int answer = coinchange();
		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}