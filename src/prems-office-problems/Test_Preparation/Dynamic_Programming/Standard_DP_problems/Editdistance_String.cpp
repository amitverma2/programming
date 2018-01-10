#include <iostream>

using namespace std;

/*
Edit Distance String Dp solution

Input:
1
sunday
saturday


output:
#1 3

*/

#define MAX 100

#define COST_STR1 15
#define COST_STR2 30


char a[MAX + 1];
char b[MAX + 1];


//deals with lenght of string, hence 1 based dp array, string lenght 0 and from len 1 to n
int dp[MAX + 1][MAX + 1];

int strlen(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

#define min(a,b) ((a<b)?(a):(b))

int findmincost()
{
	int m = strlen(a);
	int n = strlen(b);

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			// If first string is empty, only option is to
			// insert all characters of second string
			if (i == 0)
				dp[i][j] = j;  // Min. operations = j
			// If second string is empty, only option is to
			// remove all characters of second string
			else if (j == 0)
				dp[i][j] = i; // Min. operations = i
			else if (a[i - 1] == b[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
			{
				dp[i][j] = 1 + min(
					dp[i][j - 1],  // Insert
					min(dp[i - 1][j],  // Remove
					dp[i - 1][j - 1])); // Replace
			}
		}
	}
	return dp[m][n];
}


int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> a >> b;

		int answer = findmincost();

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}