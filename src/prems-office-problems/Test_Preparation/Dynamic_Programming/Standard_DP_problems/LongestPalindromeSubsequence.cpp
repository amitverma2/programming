#include <iostream>

using namespace std;

/*
Find the longest Palindromic subsequence inside a string

//Every single character is a palindrome of length 1
L(i, i) = 1 for all indexes i in given sequence

//If there are only 2 characters and both are same
Else if (j == i + 1) L(i, j) = 2

//If there are more than two characters, and first and last
characters are same
Else L(i, j) =  L(i + 1, j - 1) + 2

//IF first and last characters are not same
If (X[i] != X[j])  L(i, j) =  max{L(i + 1, j),L(i, j - 1)}


INPUT:
7
GEEKS FOR GEEKS
MADAM
Deens
Samsung
Motorola
Apple
Microsoft
*/

#define MAX 1000

char str[MAX];
int dp[MAX][MAX];

int N;

#define max(a,b) (a>b?a:b)

int length(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

int findlongestpalsequnce()
{
	// All substrings of length 1 are palindromes
	for (int i = 0; i < N; ++i)
		dp[i][i] = 1;

	// k is the length of the substring
	for (int k = 2; k <= N; k++)
	{
		// Fix the starting index
		for (int i = 0; i < N; i++)
		{
			// find the ending index of this substring
			int j = i + k - 1;

			if (str[i] == str[j] && k == 2)
			{
				dp[i][j] = 2;
			}
			else if (str[i] == str[j])
			{
				dp[i][j] = 2 + dp[i + 1][j - 1];
			}
			else
			{
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
			}
		}
	}
	return dp[0][N - 1];
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> str;

		N = length(str);

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				dp[i][j] = 0;
		}

		int answer = findlongestpalsequnce();

		cout << "#" << count << " " << answer << endl;

	}
	return 0;
}