#include <iostream>

using namespace std;

/*
https://community.topcoder.com/stat?c=problem_statement&pm=13166&rd=15854

Your friend Lucas gave you a sequence S of positive integers.
For a while, you two played a simple game with S: Lucas would pick a number, and you had to select some elements of S such that the sum of all numbers you selected is the number chosen by Lucas. For example, if S={2,1,2,7} and Lucas chose the number 11, you would answer that 2+2+7 = 11.
Lucas now wants to trick you by choosing a number X such that there will be no valid answer. For example, if S={2,1,2,7}, it is not possible to select elements of S that sum up to 6.
You are given the int[] S. Find the smallest positive integer X that cannot be obtained as the sum of some (possibly all) elements of S.

Definition
Class:	NumbersChallenge
Method:	MinNumber
Parameters:	int[]
Returns:	int
Method signature:	int MinNumber(int[] S)
(be sure your method is public)

Constraints
-	S will contain between 1 and 20 elements, inclusive.
-	Each element of S will be between 1 and 100,000, inclusive.

Examples
0)

{5, 1, 2}
Returns: 4
These are all the positive integers that can be obtained: 1, 2, 3, 5, 6, 7, and 8. (We can obtain 3 as 1+2, 6 as 1+5, 7 as 2+5, and 8 as 1+2+5.) The smallest positive integer not present in the above list is 4.
1)

{2, 1, 4}
Returns: 8
We can obtain each of the sums from 1 to 7, inclusive. The smallest impossible sum is 8.
2)

{2, 1, 2, 7}
Returns: 6
The example given in the problem statement.
3)

{94512, 2, 87654, 81316, 6, 5, 6, 37151, 6, 139, 1, 36, 307, 1, 377, 101, 8, 37, 58, 1}
Returns: 1092
4)

{883, 66392, 3531, 28257, 1, 14131, 57, 1, 25, 88474, 4, 1, 110, 6, 1769, 220, 442, 7064, 7, 13}
Returns: 56523

*/

#define MAX 20
int arr[MAX];
int N;

void swap(int *a, int *b)
{
	(*a) ^= (*b) ^= (*a) ^= (*b);
}

void siftDown(int a[], int start, int end)
{
	int root = start;
	int child;

	while (root * 2 + 1 < end) {
		child = 2 * root + 1;
		if ((child + 1 < end) && (a[child] < a[child + 1])) {
			child += 1;
		}
		if ((a[root] < a[child])) {
			swap(&a[child], &a[root]);
			root = child;
		}
		else
			return;
	}
}

/*
For a zero-based array, the root node is stored at index 0;
if i is the index of the current node, then
iParent     = floor((i-1) / 2)
iLeftChild  = 2*i + 1
iRightChild = 2*i + 2
*/


void heapsort(int a[], int n)
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
			cin >> arr[i];
		}
		heapsort(arr, N);
		int min = 1;

		for (int i = 0; i < N; i++)
		{
			if (min < arr[i])
				break;
			else
				min += arr[i];
		}

		cout << "#" << count << " " << min << endl;
	}
	return 0;
}