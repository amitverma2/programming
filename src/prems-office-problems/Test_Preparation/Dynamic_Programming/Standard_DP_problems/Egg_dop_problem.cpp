#include <iostream>

using namespace std;

/*
Problem Statement :
-----------------
http://www.geeksforgeeks.org/dynamic-programming-set-11-egg-dropping-puzzle/

The following is a description of the instance of this famous puzzle involving n=2 eggs and a building with k=36 floors.

Suppose that we wish to know which stories in a 36-story building are safe to drop eggs from, and which will cause the eggs to break on landing. We make a few assumptions:

…..An egg that survives a fall can be used again.
…..A broken egg must be discarded.
…..The effect of a fall is the same for all eggs.
…..If an egg breaks when dropped, then it would break if dropped from a higher floor.
…..If an egg survives a fall then it would survive a shorter fall.
…..It is not ruled out that the first-floor windows break eggs, nor is it ruled out that the 36th-floor do not cause an egg to break.

If only one egg is available and we wish to be sure of obtaining the right result, the experiment can be carried out in only one way. Drop the egg from the first-floor window; if it survives, drop it from the second floor window. Continue upward until it breaks. In the worst case, this method may require 36 droppings. Suppose 2 eggs are available. What is the least number of egg-droppings that is guaranteed to work in all cases?
The problem is not actually to find the critical floor, but merely to decide floors from which eggs should be dropped so that total number of trials are minimized.

In this post, we will discuss solution to a general problem with n eggs and k floors. The solution is to try dropping an egg from every floor (from 1 to k) and recursively calculate the minimum number of droppings needed in worst case. The floor which gives the minimum value in worst case is going to be part of the solution.

Input:
-----
2
2 10
2 36

Output:
------
#1 4
#2 8

*/

#define MAX 100

// No of eggs
int N;
// No of floors
int K;

int dp[MAX+1][MAX+1];

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

// i items, w weight
int eggdropUtil(int n, int k)
{
	// if k is 0, then 0 trial possible
	// if k is 1, then 1 trial possible
	if (k == 0 || k == 1)
		return k;

	// We need k trials for one egg and k floors
	if (n == 1)
		return k;

	int& res = dp[n][k];

	if (res != -1)
		return res;

	int val1, val2;
	int min_val = 0x7fffffff;
	// check for each floor starting from floor no 1 to k
	for (int x = 1; x <= k; x++)
	{
		// case 1: egg broke
		val1 = 1 + eggdropUtil(n - 1, x - 1);
		// case 2: egg did not break
		val2 = 1 + eggdropUtil(n, k-x);

		// find the worst case
		val1 = max(val1, val2);

		// find the best trial among worst case
		min_val = min(val1, min_val);
	}
	return res = min_val;
}

int eggdrop()
{
	return eggdropUtil(N, K);
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N >> K;

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= K; j++)
				dp[i][j] = -1;
		}

		int answer = eggdrop();
		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}