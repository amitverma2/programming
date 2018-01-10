#include <iostream>

using namespace std;

/*
Find the solution to TSP problem using bitmask DP

Note that in this question, we have been asked to minimum
so, we need to find top down

The graph solved is from following link:
http://www.people.vcu.edu/~gasmerom/MAT131/brutefrc.html
*/


#define MAX 5
int N;
int all_mask;

// dp array for min distance
int dp[1 << MAX][MAX];

// children nodes to be filled here
int path[1 << MAX][MAX];

#define MAX_INT 0x7fffffff

// Distance between each node, here all nodes should be connnected
int g[][MAX] = {
	{ 0, 500, 200, 185, 205 },   // node A
	{ 500, 0, 305, 360, 340 },   // node B
	{ 200, 305, 0, 320, 165 },   // node C
	{ 185, 360, 320, 0, 302 },   // node D
	{ 205, 340, 165, 302, 0 }    // node E
};

// Array that would store thd final value of node path
int final_arr[MAX + 1];


int countUtil(int mask, int cur_node)
{
	if (dp[mask][cur_node] != -1)
		return dp[mask][cur_node];

	// all nodes have been visited, return to starting node
	if (mask == all_mask)
	{
		// returning back to starting point
		path[mask][cur_node] = 0;
		// This is minimum cost, since there is no other alternative here
		return dp[mask][cur_node] = g[cur_node][0];
	}

	// We need to have a starting intial value, lets have int max value here !!
	int min_val = 0x7fffffff;
	int val;
	int child = -1;

	for (int i = 0; i < N; i++)
	{
		// this child is not yet visited
		if (((mask & (1 << i)) == 0))
		{
			// Lets visit this node...
			val = countUtil(mask | 1 << i, i) + g[cur_node][i];
			if (min_val > val)
			{
				// child 'i' gives the best min value yet
				min_val = val;
				child = i;
			}
		}
	}

	path[mask][cur_node] = child;
	return dp[mask][cur_node] = min_val;

}

int findTSP()
{
	// intialize with MAX_INT
	int final_val = MAX_INT;
	int val;

	// Starting point has been defined
	final_arr[0] = 0;
	int first_child = -1;
	for (int i = 1; i < N; i++)
	//for(int i=N-1;i>=0;i--)  //  both ways it works giving awesomely different paths
	{
		val = countUtil(1 | (1 << i), i) + g[0][i];
		if (final_val > val)
		{
			final_val = val;
			first_child = i;
		}
	}

	// Starting with only 1st node visited
	int mask = 1;
	// we know which is next child.
	int parent = first_child;
	// as of now, final_arr only has 1 element, starting point
	int counter = 1;

	while (mask != all_mask)
	{
		final_arr[counter++] = parent;
		mask = mask | 1 << parent;
		parent = path[mask][parent];
	}

	final_arr[counter++] = parent;

	return final_val;
}

int main()
{
	N = MAX;

	// Initialize only for the required 'N'
	for (int i = 0; i < (1 << N); i++)
	{
		for (int j = 0; j < N; j++)
			dp[i][j] = -1;
	}

	all_mask = (1 << N) - 1;
	int answer = findTSP();

	cout << "Optimal path solution is: " << answer << endl;
	cout << "Path is : ";
	// We know the initial starting point
	cout << 'A';
	for (int i = 1; i <= N; i++)
		cout << "->" << (char)('A' + final_arr[i]);

	return 0;
}