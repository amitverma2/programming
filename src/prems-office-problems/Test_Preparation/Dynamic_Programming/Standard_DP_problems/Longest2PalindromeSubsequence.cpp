#include <iostream>

using namespace std;

/*

https://www.hackerrank.com/challenges/strplay

haka and his brother have created a boring game which is played like this:

They take a word composed of lowercase English letters and try to get the maximum possible score by building exactly 2 palindromic subsequences. The score obtained is the product of the length of these 2 subsequences.

Let's say AA and BB are two subsequences from the initial string. If AiAi & AjAj are the smallest and the largest positions (from the initial word) respectively in AA ; and BiBi & BjBj are the smallest and the largest positions (from the initial word) respectively in BB, then the following statements hold true: 
Ai≤AjAi≤Aj, 
Bi≤BjBi≤Bj, & 
Aj<BiAj<Bi. 
i.e., the positions of the subsequences should not cross over each other.

Hence the score obtained is the product of lengths of subsequences AA & BB. Such subsequences can be numerous for a larger initial word, and hence it becomes harder to find out the maximum possible score. Can you help Shaka and his brother find this out?

Input Format 
Input contains a word SS composed of lowercase English letters in a single line.

Output Format 
Output the maximum score the boys can get from SS.

Constraints 
1<|S|≤30001<|S|≤3000 
each character will be a lower case english alphabet.

INPUT:
eeegeeksforskeeggeeks

Output:
50
*/

#define MAX 1000

char str[MAX];
int dp[MAX][MAX];

#define INT_MIN 0x80000000

int N;

#define max(a,b) (a>b?a:b)

int length(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

int find2longestpalsequence()
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
	// The complete dp array is filled for all the dimensions. Now, its easy to find the 2 longest.
	// This can be found in O(n)
	int max_prod = INT_MIN;
	for(int i=1;i<N-1;i++)
	{
		if(max_prod < dp[0][i]*dp[i+1][N-1])
			max_prod = dp[0][i]*dp[i+1][N-1];
	}
	return max_prod;
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

		int answer = find2longestpalsequence();

		cout << "#" << count << " " << answer << endl;

	}
	return 0;
}