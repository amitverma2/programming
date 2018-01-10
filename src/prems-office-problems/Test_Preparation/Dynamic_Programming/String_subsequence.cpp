#include <iostream>

using namespace std;
/*

http://www.spoj.com/problems/DSUBSEQ/

Given a string, count the number of distinct subsequences of it ( including empty subsequence ). For the uninformed, A subsequence of a string is a new string which is formed from the original string by deleting some of the characters without disturbing the relative positions of the remaining characters.
For example, "AGH" is a subsequence of "ABCDEFGH" while "AHG" is not.

Input

First line of input contains an integer T which is equal to the number of test cases. You are required to process all test cases. Each of next T lines contains a string s.

Output

Output consists of T lines. Ith line in the output corresponds to the number of distinct subsequences of ith input string. Since, this number could be very large, you need to output ans%1000000007 where ans is the number of distinct subsequences.

Example

Input:
3
AAA
ABCDEFG
CODECRAFT


Output:
4
128
496


Solution:
Consider the string “ABCD”

Let dp[i] = { number of subsequences possible from string[1…i]}

Note : we are considering 1 based string array

what are all the possible subsequences

dp[0] = 1   { }

dp[1]= 2   { } ,A

dp[2] = 4  { } ,A ,B ,AB

dp[3] = 8  { } ,A ,B ,AB ,C ,AC,BC,ABC

dp[4] = 16 { } ,A ,B ,AB ,C ,AC,BC,ABC,D,AD,BD,ABD,CD,ACD,BCD ,ABCD

So do we get some kind of pattern ?

yes!

dp[i]= dp[i-1]*2

(sum of all subseq till string[1…i-1] + sum of subseq till string[1…i-1] concatenated with character string[i])

Now, if we have duplicate characters in the string
Initially, we assume we can append a[i] to all subsequences ending on previous characters, 
but this might violate the condition that the counted subsequences need to be distinct. 
Remember that last[a[i]] gives us the last position a[i] appeared on until now. 
The only subsequences we overcount are those that the previous a[i] was appended to, so we subtract those.
Here, dp is 1 indexed while str is 0 indexed

dp[i] = (dp[i - 1] * 2) - dp[(last_pos[str[i - 1] - 'A']) - 1];

*/

#define MAX_CHAR 26

int strlen(char* str)
{
	int len = 0;
	while (*str++)
		len++;

	return len;
}

int findmaxsubseq(char str[])
{
	int len = strlen(str);
	int value;

	int* dp;
	// need to take string from position 1 to n
	// note, str is 0 indexed though
	dp = new int[len + 1];

	//intialize for the case empty string
	dp[0] = 1;
	int last_pos[MAX_CHAR];

	// no repeating characters initially
	for (int i = 0; i < MAX_CHAR; i++)
		last_pos[i] = -1;

	for (int i = 1; i <= len; i++)
	{
		if (last_pos[str[i-1] - 'A'] == -1)
			dp[i] = dp[i - 1] * 2;
		else
			dp[i] = (dp[i - 1] * 2) - dp[(last_pos[str[i - 1] - 'A']) - 1];
		
		last_pos[str[i - 1] - 'A'] = i;
	}
	value = dp[len];
	delete[] dp;

	return value;
}

int main()
{
	char str[100];
	cout << "Enter the string: " << endl;
	cin >> str;
	cout << "The max no of unique substring(including empty one) is: " << findmaxsubseq(str);
	return 0;
}