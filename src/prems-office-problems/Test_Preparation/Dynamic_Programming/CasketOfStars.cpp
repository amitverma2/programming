#include <iostream>

using namespace std;

/*
Problem Statement :
-----------------
http://www.spoj.com/problems/SAMER08C/

The Casket of Star (sic) is a device in the Touhou universe. 
Its purpose is to generate energy rapidly. Initially it contains n stars in a row. The stars are labeled 0 through n-1 from the left to the right. 
You are given a int[] weight, where weight[i] is the weight of star i.

The following operation can be repeatedly used to generate energy:

Choose a star x other than the very first star and the very last star.
The x-th star disappears.
This generates weight[x-1] * weight[x+1] units of energy.
We decrease n and relabel the stars 0 through n-1 from the left to the right.

Your task is to use the device to generate as many units of energy as possible. 
Return the largest possible total amount of generated energy.

Constraints
-	weight will contain between 3 and 50 elements, inclusive.
-	Each element in weight will be between 1 and 1,000, inclusive.

INPUT:
-----
5
4
1 2 3 4
5
100 2 1 3 100
7
2 2 7 6 90 5 9
8
477 744 474 777 447 747 777 474
15
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

OUTPUT:
------
#1 12
#2 10400
#3 1818
#4 2937051
#5 13


*/

#define MAX 50

// No of items
int N;

// weight of each item
int w[MAX];

int dp[MAX][MAX];

#define max(a,b) ((a)>(b)?(a):(b))

int findMaxProdUtil(int i, int j)
{
	int& res = dp[i][j];

	if (res != -1)
		return res;

	// if we reach where there are not enough elements in array
	if ((j - i) < 2)
		return res = 0;
	// idea case where we have only 3 elements left
	else if ((j - i) == 2)
		res =  w[i] * w[j];
	else
	{
		// assuming, k between i and j was the last element to be withdrawn
		for (int k = i + 1; k < j; k++)
		{
			int left = findMaxProdUtil(i, k);
			int right = findMaxProdUtil(k, j);
			int cur_res = (left + right) + (w[i] * w[j]);
			// note that res is initially -1, which is already least value here
			res = max(res, cur_res);
		}
	}

	return res;
}


int findMaxProd()
{
	return findMaxProdUtil(0, N - 1);
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
				cin >> w[i];
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				dp[i][j] = -1;
		}

		int answer = findMaxProd();

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}