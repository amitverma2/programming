#include <iostream>

using namespace std;
/*
https://community.topcoder.com/stat?c=problem_statement&pm=3491

My partner and I have bags of gold, lined up in a row. The bags are different sizes. 
My partner has offered to split up the gold using the following system: we take turns, each time choosing one bag from either end of the line. 
She has even generously offered to let me go first -- hmmmmmmmm....
I need software to tell me the total amount of gold that I will get compared to how much my partner will get if I choose first. 
Of course we will assume that my partner and I are brilliant and always choose in the optimum way.

Create a class BagsOfGold that contains a method netGain that is given a int[] bags, 
the values of all the bags of gold in the order in which they are lined up. 
It should return how much more gold I will get than my partner if we both behave optimally. 
(I fear that the answer might be a negative number since my partner proposed the plan.)


Definition

Class:	BagsOfGold
Method:	netGain
Parameters:	int[]
Returns:	int
Method signature:	int netGain(int[] bags)
(be sure your method is public)


Constraints
-	bags will contain between 1 and 50 elements inclusive.
-	Each element of bags will be between 1 and 100,000 inclusive.

INPUT:
4
2
7 2
3
2 7 3
5
1000 1000 1000 1000 1000
9
823 912 345 100000 867 222 991 3 40000

*/

#define MAX 50

enum player
{
	me,
	partner
};

int N;
int dp[MAX][MAX][2];
int bags[MAX];

#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

int countutil(int i, int j, player p)
{
	if (i > j)
		return 0;

	int &res = dp[i][j][p];

	if (res != -1)
		return res;

	if (i == j)
	{
		if (p == me)
		{
			return res = bags[i];
		}
		else
		{
			return res = (-bags[i]);
		}
	}

	int val1, val2;
	//We can take gold coins from either side
	if (p == me)
	{
		// take from left and calculate
		val1 = bags[i] + countutil(i + 1, j, partner);
		// take from right and calculate
		val2 = bags[j] + countutil(i, j-1, partner);
		return res = max(val1, val2);
	}
	else
	{
		// take from left and calculate
		val1 = -bags[i] + countutil(i + 1, j, me);
		// take from right and calculate
		val2 = -bags[j] + countutil(i, j - 1, me);
		return res = min(val1, val2);
	}
}

int findscore()
{
	int val1, val2;
	// take from left and calculate
	val1 = bags[0] +  countutil(1, N - 1, partner);
	// take from right and calculate
	val2 = bags[N-1] + countutil(0, N - 2, partner);

	return max(val1, val2);
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
			cin >> bags[i];
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < 2; k++)
					dp[i][j][k] = -1;
			}
		}

		int answer = findscore();
		cout << "#" << count << " " << answer << endl;

	}
	return 0;
}