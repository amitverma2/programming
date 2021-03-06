#include <cstdio>

using namespace std;

/*
https://www.codechef.com/problems/CARDINAL


All submissions for this problem are available.

You have a set of unique numbers. You are trying to find a subset of this set such that no two numbers in the subset have a common digit. There will of course be several such subsets. You are interested in the subset with the maximum sum. The sum of a subset is defined as the sum of the numbers in the subset.

In fact, you are most interested in the cardinality - that is, the number of elements - of the subset with the maximum sum. Of course there may be several such subsets with the same maximum sum. Find the cardinality of the subset with the most elements among such sets.

Refer to the explanation section for more clarity.
Input

There will be several test cases. Each test case is described in two lines. The first line contains the number N, the number of numbers in the set given to you. The second line contains N space separated positive integers, A1, A2 ..., AN. The input is terminated by EOF.
Output

For each test case, output a single line. The line should contain a single integer which denotes the cardinality of the set that satisfies all the requirements in the problem statement.
Constraints

1 ≤ N ≤ 100
1 ≤ Ai ≤ 1000000000
No two Ai's will be same.
There will be at most 100 test cases.

Sample Input

3
7 17 10
2
12 29
3
1 2 12

Sample Output

2
1
1

*/

#define MAX 100

#define MAX_DIGIT 10

int N;
long long arr[MAX];

struct value
{
	long long sum;
	int cardi;
};

int all_mask = (1 << MAX_DIGIT) - 1;

value dp[1 << MAX_DIGIT][MAX];

int getmask(long long n)
{
	int mask = 0;

	do
	{
		int remainder = n % 10;
		mask = mask | (1 << remainder);
		n = n / 10;
	} while (n);

	return mask;
}

value findMaxCardinalUtil(int bitmask, int index)
{
	value& res = dp[bitmask][index];
	// all digit chosen, hence no need to go further
	if (bitmask == all_mask || index > N - 1)
	{
		value temp;
		temp.cardi = 0;
		temp.sum = 0;
		return temp;
	}

	if (res.sum != -1 && res.cardi != -1)
		return res;

	int cur_mask = getmask(arr[index]);

	if (index == N - 1)
	{
		if ((bitmask & cur_mask) == 0)
		{
			res.sum = arr[index];
			res.cardi = 1;
		}
		else
		{
			res.sum = 0;
			res.cardi = 0;
		}
		return res;
	}

	//if we dont take this value
	value val1 = findMaxCardinalUtil(bitmask, index + 1);

	//if we can take this value
	if ((bitmask & cur_mask) == 0)
	{
		value val2 = findMaxCardinalUtil(bitmask | cur_mask, index + 1);

		val2.sum += arr[index];
		val2.cardi += 1;

		if (val1.sum > val2.sum)
			return res = val1;
		else if (val2.sum > val1.sum)
			return res = val2;
		else if (val1.cardi > val2.cardi)
			return res = val1;
		else
			return res = val2;
	}
	else
		return res = val1;
}

int findMaxCardinal()
{
	// bitmask 0 and index 0
	value ans = findMaxCardinalUtil(0, 0);
	return ans.cardi;
}


int main()
{
	freopen("input.txt", "r", stdin);

	while (scanf("%d", &N) != EOF)
	{
		for (int i = 0; i<N; i++)
			scanf("%lld", &arr[i]);

		for (int i = 0; i< (1 << MAX_DIGIT); i++)
		{
			for (int j = 0; j<N; j++)
			{
				dp[i][j].cardi = -1;
				dp[i][j].sum = -1;
			}
		}

		int answer = findMaxCardinal();
		printf("%d\n", answer);
	}
	return 0;
}