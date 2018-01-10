#include <iostream>

using namespace std;

/*
http://www.spoj.com/problems/MC/


Problem Statement :
-----------------
Knapsack problem
Given weights and values of n items, put these items in a knapsack of capacity 'W' to get the maximum total value in the knapsack.
In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated with n items respectively. 
Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this 
subset is smaller than or equal to W. You cannot break an item, either pick the complete item, or don’t pick it (0-1 property).

Input:
1
3 50
60 10
100 20
120 30


Output:
220

*/

#define MAX 100

int value[MAX];
int wt[MAX];

int N;
int W;

int dp[MAX+1][MAX+1];

#define max(a,b) (a>b?a:b)

// i items, w weight
int knapSackUtil(int i, int w)
{
	if (i == 0 || w <= 0)
		return 0;

	int val1, val2;

	int& res = dp[i][w];

	if (res != -1)
		return res;

	if (wt[i - 1] > w)
	{
		val1 = knapSackUtil(i - 1, w);
	}
	else
	{
		//take this item
		val1 = value[i-1] + knapSackUtil(i - 1, w - wt[i-1]);
		val2 = knapSackUtil(i - 1, w);
		val1 = max(val1, val2);
	}

	return res = val1;
}

int knapSack()
{
	return knapSackUtil(N, W);
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N >> W;
		for (int i = 0; i < N; i++)
			cin >> value[i] >> wt[i];

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= W; j++)
				dp[i][j] = -1;
		}

		int answer = knapSack();
		cout << "#" << count << " " << answer;
	}
	return 0;
}