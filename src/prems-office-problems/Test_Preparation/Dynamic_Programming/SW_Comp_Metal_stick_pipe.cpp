#include <iostream>

using namespace std;

/*
You will connect circular metal sticks as longest as possible. One side of the circular metal stick has an external thread, and the other side has an internal thread. The external and internal threads are different in thickness.In the figure below, thickness of the external thread is 3 while that of the internal thread is 4.



(Hereafter, thickness of the treads will be represented as ‘thickness' of external thread x thickness of internal thread’. Stick connection will be indicatedas ‘+’.)


To connect such circular metal sticks, thickness of the external thread and that of the internal thread must match. For example, when there are twocircular metal sticks A(3x4) and B(4x5), connection must be made as 3x4+4x5,and they will not get connected if the sequence is 4x5+3x4.


Now,you will connect circular metal sticks with different external and internal thread sizes as many as possible. Write a program that finds the sequence by which amaximum number of sticks are connected.

[Input]

In the first line,the number of test cases is given. The test cases are given in each line. Each test case consists of 2 lines; the first line has a number of circular metalstick, n, and the next line has 2*n numbers. Numbers are separated by a blank space. Two numbers from the front mean the thickness of the external thread,and that of the internal thread of a circular metal stick respectively.

[Output]

Print out answers foreach of the test cases. Start each line with ‘#x’, leave a blank space, and print in order the thicknesses of the external and internal threads of circular metal stick so that they could be connected as longest as possible from the sequence given in each test case.

[Input/output example]

Input
10                              <- No. of test cases
3                             <- Test case #1,  No. of circular metal stick
3 4 2 3 4 5                     <- Matrix of thicknesses of external and internal

threads
4                               <- Test case #2
1 2 5 1 2 4 4 3
…


[Output]

#1 2 3 3 4 4 5
#2 5 1 1 2 2 4 4 3

*/



// MAX is maximum no of pipes possible
#define MAX 20

int N;

// 0 based index here
int dm[MAX][2];

// BitMask from 0 to 19 would be used here, so 1 more.
int dp[1 << MAX][MAX];

int all_mask;
int final_arr[MAX];

int countUtil(int mask, int pipe_no, int cnt, int* arr)
{
	if (dp[mask][pipe_no] != -1)
		return dp[mask][pipe_no];

	if (mask == all_mask)
	{
		dp[mask][pipe_no] = cnt;
		return cnt;
	}

	// Till now the cnt value
	int final_val = cnt;
	int val;

	for (int i = 0; i<N; i++)
	{
		if (((mask & (1 << i)) == 0) && dm[pipe_no][1] == dm[i][0])
		{
			val = countUtil(mask | 1 << i, i, cnt + 1, arr);
			if (final_val < val)
			{
				final_val = val;
				arr[cnt] = i;
			}
		}
	}

	return dp[mask][pipe_no] = final_val;

}

int findmax()
{
	// minimum lenth possible would be 1
	int final_val = 1;
	int val;

	int* int_arr;
	int_arr = new int[N];

	//Exploring each solution starting with individual pipe nos
	for (int i = 0; i<N; i++)
	{
		int_arr[0] = i;
		val = countUtil(1 << i, i, 1, int_arr);
		if (final_val < val)
		{
			final_val = val;
			for (int i = 0; i < final_val; i++)
				final_arr[i] = int_arr[i];
		}
	}

	delete[] int_arr;
	return final_val;
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;

	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N;

		for (int i = 0; i<N; i++)
		{
			cin >> dm[i][0] >> dm[i][1];
		}

		// Initialize only for the required 'N'
		for (int i = 0; i<(1 << N); i++)
		{
			for (int j = 0; j<N; j++)
				dp[i][j] = -1;
		}

		all_mask = (1 << N) - 1;
		int answer = findmax();

		cout << "#" << count;

		for (int i = 0; i < answer; i++)
			cout << " " << dm[final_arr[i]][0] << " " << dm[final_arr[i]][1];
		cout << endl;
	}
	return 0;
}