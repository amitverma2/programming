#include <iostream>

using namespace std;

/*
Longest Increasing Subsequence

*/

#define MAX 100

int N;

int arr[MAX];

// 0 based dp array
int dp[MAX];


#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

int findLIS()
{
	// Initializing base case of each entry
	for (int i = 0; i < N; i++)
		dp[i] = 1;

	for (int i = 1; i < N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((arr[i] > arr[j]) && (dp[i] < dp[j] + 1))
				dp[i] = dp[j] + 1;
		}
	}

	int max = 0x80000000;
	for (int i = 0; i < N; i++)
	{
		if (max < dp[i])
			max = dp[i];
	}

	return max;
}


int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N;
		for (int i = 0; i < N; i++)
		{
			cin >> arr[i];
		}
		int answer = findLIS();
		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}