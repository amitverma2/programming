#include <iostream>

using namespace std;

/*
Find Longest Palindromic Substring in a String

We maintain a boolean dp[n][n] that is filled in bottom up manner. 
The value of dp[i][j] is true, if the substring is palindrome, otherwise false.
To calculate dp[i][j], we first check the value of dp[i+1][j-1], 
if the value is true and str[i] is same as str[j], then we make dp[i][j] true. 
Otherwise, the value of dp[i][j] is made false.

INPUT:
7
GEEKS FOR GEEKS
MADAM
Deens Academy
Samsung
Motorola
Apple
Microsoft
*/

#define MAX 1000

char str[MAX];
bool dp[MAX][MAX];

int N;
int maxlength;
int start;

int length(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

void findlongestpal()
{
	// All substrings of length 1 are palindromes
	maxlength = 1;
	start = 0;

	for (int i = 0; i < N; ++i)
		dp[i][i] = true;

	// k is the length of the substring
	for (int k = 2; k <= N; k++)
	{
		// Fix the starting index
		for (int i = 0; i < (n-k+1); i++)
		{
			// find the ending index of this substring
			int j = i + k - 1;

			if (k == 2)
			{
				if (str[i] == str[j])
				{
					dp[i][j] = true;
					if (maxlength < k)
					{
						start = i;
						maxlength = k;
					}
				}
			}
			else if (str[i] == str[j] && dp[i + 1][j - 1])
			{
				dp[i][j] = true;
				if (maxlength < k)
				{
					start = i;
					maxlength = k;
				}
			}	
		}
	}
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
				dp[i][j] = false;
		}

		findlongestpal();

		cout << "#" << count << " Longest palindrome substring is: ";
		for (int i =0; i < maxlength; i++)
			cout << str[start+i];

		cout << ", Length is: " << maxlength << endl;

	}
	return 0;
}