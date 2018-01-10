#include <iostream>

using namespace std;

/*
http://www.spoj.com/problems/ACTIV/

Ana likes many activities. She likes acrobatics, alchemy, archery, art, Arabic dances, and
many more. She joined a club that offers several classes. Each class has a time interval
in every week. Ana wants to sign up for many classes, but since they overlap in time, she
looks for a subset of non-overlapping classes to attend. A subset is non-overlapping if it
does not contain two classes that overlap in time. If a class starts at the time another
class ends, this is not considered overlapping.
Ana decided to list all the non-overlapping non-empty subsets of classes. Then she will
choose the subset she likes best. In order to predict the amount of paper needed to write
the list, she wants you to calculate how many of these subsets there are.

Input:
5
5
1 3
3 5
5 7
2 4
4 6
3
500000000 1000000000
1 500000000
1 500000000
1
999999999 1000000000
6 
1 2 
2 3 
3 4 
1 8 
4 5 
5 6 
7
1 2
1 2
1 2
1 2
1 2
1 2
2 3



Output:
#1 12
#2 5
#3 1
#4 32
#5 13
*/

#define MAX 1000000

int N;

struct activ {
	int start;
	int end;
};

activ ac[MAX];

int dp[MAX];

void swap(activ* x, activ* y)
{
	activ temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// heapify
void siftDown(activ a[], int start, int end)
{
	int root = start;
	int child;

	while (root * 2 + 1 < end) {
		child = 2 * root + 1;
		if ((child + 1 < end) && (a[child].end < a[child + 1].end)) {
			child += 1;
		}
		if ((a[root].end < a[child].end)) {
			swap(&a[child], &a[root]);
			root = child;
		}
		else
			return;
	}
}

void heapSort(activ a[], int n)
{
	int start, end;

	for (start = (n - 1 - 1) / 2; start >= 0; start--) {
		siftDown(a, start, n);
	}


	for (end = n - 1; end > 0; end--) {
		swap(&a[end], &a[0]);
		siftDown(a, 0, end);
	}
}

int binsearch(int x, activ a[], int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x >= a[mid].end && x < a[mid + 1].end)
			return mid;
		else if (x < a[mid].end)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

int findmax()
{
    if(N == 0)
	    return 0;
	// lets use tabulation method
	// We need to sort the activ array, I shall do it based on end time
	heapSort(ac, N);

	//Base case
	// not taken would be 0, and taken would be 1, hence total 1
	dp[0] = 1; 

	for (int i = 1; i < N; i++)
	{
		int not_taken;
		int taken;

		not_taken = dp[i - 1];

		// find the start time of this activity
		int start_time = ac[i].start;
		// check if there is nearest activity for which the end time is less than this start time 
		int index = binsearch(start_time, ac, N);
		
		// index -1, means there is no such activity with end time less than start time
		// note we need to account for the case where "ith" activity is the only option in the arrangement
		if (index != -1)
			taken = dp[index] + 1;
		else
			taken = 1;

		dp[i] = taken + not_taken;
	}
	return dp[N - 1];
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
			cin >> ac[i].start >> ac[i].end;
		}

		int answer = findmax();

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}