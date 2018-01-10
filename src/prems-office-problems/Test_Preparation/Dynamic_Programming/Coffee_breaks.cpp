#include <iostream>

using namespace std;
/*

https://www.codechef.com/problems/COFFEE
Sergey works as a programmer. Like all programmers, he is a coffee fan. He likes coffee so much that has K cups of coffee daily. However, having more than K cups doesn't suit him, because the excess caffeine won't allow him to sleep at night.
Sergey's working day is divided into N periods. For every period, he knows how many kilobytes of code he can produce.
During each of the periods, Sergey can either have or not to have one cup of coffee. If he is having a cup of coffee in some period, the amount of code he writes in this period drops to zero. But he also gets a productivity boost — if he decides to skip coffee during a period and the last cup of coffee he had was no more than D periods ago, the amount of code he writes during such a period is M times the usual.
As his productivity advisor (congrats on your new job!), help Sergey plan his coffee breaks optimally. Please find the maximum number of lines of code he can write, provided that he has exactly K coffee breaks during the day.
Input

The first line of the input contains an integer T denoting the number of test cases. The description of T test cases follows.
The first line of each test case contains four space separated integers N, K, D and M denoting the number of the working periods, the number of coffee-breaks and two more parameters as described in the statement.
The second line contains N space-separated integers A1, A2, ... , AN denoting the number of kilobytes of code that Sergey writes during each period.
Output

For each test case, output a single line containing the maximum number of kilobytes of code that Sergey can produce if he takes exactly K coffee breaks.
Constraints

1 ≤ T ≤ 200
In subtasks 1-3 it holds that 1 ≤ sum of all N over the test case ≤ 1000
Subtask 1 (15 points): K = 1, 1 ≤ D < N ≤ 18
Subtask 2 (25 points): 1 ≤ K, D < N ≤ 18
Subtask 3 (30 points): 1 ≤ K, D < N ≤ 200
Subtask 4 (30 points): 1 ≤ K, D < N ≤ 5000, 1 ≤ sum of all N over the test case ≤ 5000
1 ≤ M, Ai ≤ 1000
Example

Input:
1
5 2 2 10
1 2 3 4 5

Output:
110

*/

#define MAX 300
int N, K, D, M;

int dp[MAX][MAX+1][MAX +1+1];
int prod[MAX];

#define max(a,b) (a>b?a:b)

int countutil(int period, int brk, int gap)
{
	if (dp[period][brk][gap] != -1)
		return dp[period][brk][gap];

	// Last period.
	if (period == N - 1)
	{
		// No option, need to take break
		if (brk == K - 1)
			return dp[period][brk][gap] = 0;

		// Not enough break taken, so this is not valid use case
		if (brk < K - 1)
			return dp[period][brk][gap]= 0x80000000;

		// All coffee breaks taken
		if (brk == K)
		{
			//Lets try max productivity
			if (gap <= D)
			{
				return dp[period][brk][gap] = M*prod[period];
			}
			else
			{
				return dp[period][brk][gap] = prod[period];
			}
		}
		// should never reach here
		return dp[period][brk][gap] = 0x80000000;
	}

	//other cases, Either we take a coffee break or not
	int val1, val2;

	//Lets take a coffee break
	val1 = 0x80000000;
	// if we have not taken enough breaks
	if (brk < K)
		val1 = countutil(period + 1, brk + 1, 1);

    // Here, dont take break.
	//lets calculate the productivity based on previous coffee breaks
	if (gap <= D)
		val2 = M*prod[period] + countutil(period + 1, brk, (gap>D ? gap : gap + 1));
	else
		val2 = prod[period] + countutil(period + 1, brk, (gap>D ? gap : gap + 1));

	val1 = max(val1, val2);

	return dp[period][brk][gap] = val1;


}

int findmax()
{
	// 0th Period, no breaks so far, gap is more than max
	return countutil(0, 0, D + 1);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N >> K >> D >> M;

		for (int i = 0; i < N; i++)
			cin >> prod[i];

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < K+1; j++)
			{
				for (int k = 0; k <= D+1; k++)
					dp[i][j][k] = -1;
			}
		}

		int answer = findmax();

		//cout << "#" << count << " ";
		cout << answer << endl;
	}
	return 0;
}