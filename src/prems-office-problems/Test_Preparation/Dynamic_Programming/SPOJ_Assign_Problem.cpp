#include <iostream>
using namespace std;

/*

http://www.spoj.com/problems/ASSIGN/

Problem

Your task will be to calculate number of different assignments of n different topics to n students
such that everybody gets exactly one topic he likes.

Input
First line of input contains number of test cases c (1<=c<=80). 
Each test case begins with number of students n (1<=n<=20). 
Each of the next n lines contains n integers describing preferences of one student. 
1 at the ith position means that this student likes ith topic, 0 means that he definitely doesn't want to take it.

Output
For each test case output number of different assignments (it will fit in a signed 64-bit integer).
Example

Input:
3
3
1 1 1
1 1 1
1 1 1
11
1 0 0 1 0 0 0 0 0 1 1 
1 1 1 1 1 0 1 0 1 0 0 
1 0 0 1 0 0 1 1 0 1 0 
1 0 1 1 1 0 1 1 0 1 1 
0 1 1 1 0 1 0 0 1 1 1 
1 1 1 0 0 1 0 0 0 0 0 
0 0 0 0 1 0 1 0 0 0 1 
1 0 1 1 0 0 0 0 0 0 1 
0 0 1 0 1 1 0 0 0 1 1 
1 1 1 0 0 0 1 0 1 0 1 
1 0 0 0 1 1 1 1 0 0 0 
11
0 1 1 1 0 1 0 0 0 1 0 
0 0 1 1 1 1 1 1 1 1 1 
1 1 0 1 0 0 0 0 0 1 0 
0 1 0 1 0 1 0 1 0 1 1 
1 0 0 1 0 0 0 0 1 0 1 
0 0 1 0 1 1 0 0 0 0 1 
1 0 1 0 1 1 1 0 1 1 0 
1 0 1 1 0 1 1 0 0 1 0 
0 0 1 1 0 1 1 1 1 1 1 
0 1 0 0 0 0 0 0 0 1 1 
0 1 1 0 0 0 0 0 1 0 1 

Output:
6
7588
7426

*/

#define MAX 20
int N;
int js[MAX][MAX];

int all_mask;
int dp[1<<MAX][MAX];

int findmax(int mask, int job)
{
	// One arrangement reached
	// each student is doing some job
	if(mask == all_mask)
		return 1;

	// not all selected and we have bigger job no
	if(job >= N)
		return 0;

	if (dp[mask][job] != -1)
		return dp[mask][job];

	int total = 0;
	for(int j=0; j<N;j++)
	{
		if(js[job][j] && !(mask & (1 <<j)))
		{
			total += findmax(mask | 1 <<j, job+1);
		}
	}

	return dp[mask][job] = total;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;

	for(int count=1;count<=T;count++)
	{
		cin >> N;
		int job;
		// scanning for each student
		for(int i=0;i<N;i++)
		{
			// scanning for jobs now
			for(int j=0;j<N;j++)
			{
				// job j can be done by student i
				cin >> js[j][i];
			}
		}
		for(int i=0; i< (1<<N); i++)
		{
			for(int j=0; j<N; j++)
			{
				dp[i][j] = -1;
			}
		}
		all_mask = (1<<N) -1;
		// mask chosen is for students
		// job no is the second index of dp array
		// no student selected, and current job index as 0
		int answer = findmax(0, 0);

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}