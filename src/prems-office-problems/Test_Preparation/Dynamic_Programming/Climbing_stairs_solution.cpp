#include <iostream>

using namespace std;
/*
A game about climbing stairs going up from the lowest starting point to the highest arriving point. As in , each stair has a score. When you step on a stair, you will get the score written on the stair.
For example, as in , reaching the arriving point by going up from the starting point to the first, second, fourth and sixth stairs, the total score is 10+20+25+20=75.

The rules of going up the stairs are as below:

1. You may go up one or two stairs at a time. That means once you step on a stair, then you can step up to the next or two higher stairs.
2. You may not step on every three consecutive stairs. However, the starting point is not included in the number of stairs.
3. You must step on the final arriving stair.

Therefore, when you step on the first stair, you can step on the second or third stair. However, after you step on the first stair, you may neither step on the fourth stair nor the first, second and third stair consecutively.
Create a program to find the maximum total score available in this game in the given scores written on the stairs.

Time limit: 1 second (java: 2 seconds)

[Input]
Several test cases can be included in the inputs. T, the number of cases is given in the first row of the inputs. After that, the test cases as many as T (T ≤ 20) are given in a row.
The number of stairs, N is given on the first row per each test case. (1 ≤ N ≤300)
The scores written on each stair, S are given in order from the bottom stair one by one from the second row to N number rows. (1 ≤ S ≤ 10,000)

*/

#define MAX 300

int N;

int stepscr[MAX];

int dp[MAX][3];

#define max(a,b) (a>b?a:b)


int countutil(int step, int increment)
{
	// invalid use case, hence return minimum value
	if (step > N - 1)
		return 0x80000000;

	int &res = dp[step][increment];

	if (res != -1)
		return res;

	// concrete answer
	if (step == N - 1)
		return res = stepscr[step];

	// only 2 increment possible here
	if (increment == 1)
		return res = stepscr[step] + countutil(step + 2, 2);

	// both 1 and 2 increment possible here
	if (increment == 2)
	{
		int val1, val2;
		val1 = stepscr[step] + countutil(step + 1, 1);
		val2 = stepscr[step] + countutil(step + 2, 2);
		return res = max(val1, val2);
	}
	// we should not reach at this place anytime
	return 0x80000000;
}


int findmax()
{
	int val1, val2, val3, val4;
	//starting from step 0
	// Two cases possible, take 1 increment or take 2 increments
	val1 = stepscr[0] + countutil(1, 1);
	val2 = stepscr[0] + countutil(2, 2);
	val3 = stepscr[1] + countutil(2, 1);
	val4 = stepscr[1] + countutil(3, 2);

	val1 = max(val1, val2);
	val3 = max(val3, val4);
	return max(val1, val3);
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
			cin >> stepscr[i];
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < 3; j++)
				dp[i][j] = -1;
		}

		int answer = findmax();
		cout << "#" << count << " " << answer << endl;

	}
	return 0;
}