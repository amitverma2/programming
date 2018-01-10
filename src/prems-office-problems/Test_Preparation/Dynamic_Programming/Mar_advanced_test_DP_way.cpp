#include <iostream>
using namespace std;
/////////////////////// Making the solution DP way ////////////////////
/*
Assumption
N varies from 1 t0 20
while toal combined org army from all nodes are not more than 100
*/

#define MAX_INT 0x7fffffff
#define MAX 20

int N;

int org[MAX];
int ncost[MAX];

int dp[MAX][100][100][100];

#define min(a,b) (a<b?a:b)

int countUtil(int node, int temp1, int temp2, int temp3)
{
	// if the state was already calculated
	if (dp[node][temp1][temp2][temp3] != -1)
	{
		return dp[node][temp1][temp2][temp3];
	}

	// Last node, first step to calculate concrete state
	if (node == N - 1)
	{
		// in this case, Hire is not required
		// if Battle is possible, thats the best thing to do

		//lets battle, if possible
		if (temp1+ temp2 + temp3 >= org[node])
		{
			return dp[node][temp1][temp2][temp3] = 0;
		}
		else
		{
			//ok, pass is the only option
			return dp[node][temp1][temp2][temp3] = ncost[node];
		}
	}
	else
	{
		// Pass, Hire and Battle is possible
		int val1;  // Pass value
		int val2;  // Hire vlaue
		int val3;  // Battle value

		// Lets store the army state, would be used while saving the state value at the end stage
		int t1 = temp1;
		int t2 = temp2;
		int t3 = temp3;

		//Lets pass
		val1 = ncost[node] + countUtil(node + 1, temp1, temp2, temp3);

		//or lets hire
		val2 = (2 * ncost[node]) + countUtil(node + 1, temp1, temp2, temp3+org[node]);

		// if val3 doesn't get calculated, this would help us to choose val1 or val2
		val3 = MAX_INT;
		//or lets battle as well
		// if we have more orgs, then only we can fight
		// note that for node '0', we would never have orgs to fight
		if (temp1+temp2+temp3 >= org[node])
		{
			if(temp1 >= org[node])
				temp1 -= org[node];
			else if(temp2 >= org[node]-temp1)
			{
				temp2 -= org[node]-temp1;
				temp1 = 0;
			}
			else
			{
				temp3 -=org[node]-temp1-temp2;
				temp1 = temp2 = 0;
			}

			// They fought 1 battle, hence reduce the life
			temp1 = temp2;
			temp2 = temp3;
			temp3 = 0;

			val3 = countUtil(node + 1, temp1, temp2, temp3);
		}
		return dp[node][t1][t2][t3] = min(val1, min(val2,val3));
	}
}

int findmincost()
{
	int answer;

	// node: 0, all org army 0
	answer = countUtil(0, 0, 0, 0);
	return answer;
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
			cin >> org[i] >> ncost[i];
		}

		memset(dp, -1, sizeof(dp));

		int answer = findmincost();

		cout << "#" << count << " " << answer << endl;
	}

	return 0;
}

/*
Tested with sample input:
1
6
12 500
15 100
20 5
30 20
5  150
10 250
*/

/*
Output:
#1 630
*/