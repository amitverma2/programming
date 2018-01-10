#include <iostream>

using namespace std;

/*
http://www.spoj.com/problems/MC/


Problem Statement :

Given two string S and T. you can delete a character  from  S  with  cost 15 and  a Character T with cost 30. Your goal is to make the string equal (same). 
It is not mandatory  to delete  character .
For example :  S = a5b and  T = 2ab . Now , if we delete X from S and Y from T, then total cost  =  15+30 = 45.  And  S and T will become ab.
Another example : S = ab , T = cd , Now  total cost = 15  + 15 + 30 + 30 = 90.
Another example : S = abcd , T = acdb , Now  total cost = 15 + 30 = 45.

Input:
Input consists of pairs of lines. The first line of a pair contains the first string S and the second line contains the second string T. 
Each string is on a separate line and consists of at most 1,000 characters .

Output:
For each subsequent pair of input lines, output a line containing one integer number which  the minimum cost to make the string equal (same).



Input:
4
axb
yab
ab
cd
ko
p
abcd
acdb

Output:
#1 45
#2 90
#3 60
#4 45

*/

#define MAX 1005

#define COST_STR1 15
#define COST_STR2 30

char str1[MAX];
char str2[MAX];

// 1 based dp array
// here we deal with length of string from 0 to 1 to n
int dp[MAX][MAX];

int strlen(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

#define max(a,b) (a>b?a:b)

int findmincost()
{
	int m = strlen(str1);
	int n = strlen(str2);

	for (int i = 0; i <= m; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (i == 0 || j == 0)
				dp[i][j] = 0;
			else if (str1[i - 1] == str2[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1];
			else
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}


	return ((m - dp[m][n]) * COST_STR1) + ((n - dp[m][n]) * COST_STR2);
}


int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> str1 >> str2;

		int answer = findmincost();

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}