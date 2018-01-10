#include <iostream>

using namespace std;

/*
https://www.codechef.com/APRIL15/problems/CARLOS

INPUT:
3
3 3 3
1 2
2 3
3 1
3 2 1
3 1 2
2 3
2 1
1
4 2 4
1 3
4 2
4 2 2 1
Output:
2
-1
2

*/

#define MAX_NODES 50
#define MAX_LEN 20000
#define MAX_INT 0x7fffffff

// No of nodes
int M;
// Word length
int N;

int g[MAX_NODES+1][MAX_NODES+1];
int color[MAX_NODES+1];
int word[MAX_LEN + 1];
int cur_color;
int dp[MAX_LEN + 1][MAX_NODES+1];


void DFSUtil(int u)
{
	color[u] = cur_color;

	for (int v = 1; v <= M; v++)
	{
		if (g[u][v] == 1 && color[v] == -1)
			DFSUtil(v);
	}
}

void colorNodes()
{
	// make all the colors -1
	for (int i = 1; i <= M; i++)
		color[i] = -1;

	// Initial color is 0
	cur_color = 0;
	color[0] = cur_color++;

	for (int i = 1; i <= M; i++)
	{
		if (color[i] == -1)
		{
			DFSUtil(i);
			cur_color++;
		}
	}
}

int findMinchange()
{
	// lets create the index 1
	for (int j = 1; j <= M; j++)
	{
		if (word[1] == j)
			dp[1][j] = 0;
		else if (color[word[1]] == color[j])
			dp[1][j] = 1;
	}

	// word index
	for (int i = 2; i <= N; i++)
	{
		// all possible letter transformation
		for (int j = 1; j <= M; j++)
		{
			int min = MAX_INT;
			int temp;
			if (color[word[i]] == color[j])
			{
				// i-1th position investigation
				for (int k = 1; k <= j; k++)
				{
					if (dp[i - 1][k] != MAX_INT)
					{
						if (word[i] == j)
							temp = dp[i - 1][k];
						else
							temp = dp[i - 1][k] + 1;

						if (min > temp)
							min = temp;
					}
				}
			}
			if (min != MAX_INT)
				dp[i][j] = min;
		}
	}

	int min1 = MAX_INT;
	for (int j = 1; j <= M; j++)
	{
		if (min1 > dp[N][j])
			min1 = dp[N][j];
	}

	return ((min1 != MAX_INT)?min1:-1);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	// No of Edges
	int E;
	for (int count = 1; count <= T; count++)
	{
		cin >> M;
		int u, v;

		cin >> E;

		cin >> N;

		// Initially all nodes have no relationship
		for (int i = 0; i <= M; i++)
		{
			for (int j = 0; j <= M; j++)
				g[i][j] = 0;
		}


		for (int cnt = 1; cnt <= E; cnt++)
		{
			cin >> u >> v;
			g[u][v] = 1;
			g[v][u] = 1;
		}

		colorNodes();

		for (int i = 1; i <= N; i++)
			cin >> word[i];

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= M; j++)
				dp[i][j] = MAX_INT;
		}

		int answer = findMinchange();

		//cout << "#" << count << " " << answer << endl;
		cout << answer << endl;
	}
	return 0;
}



++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <iostream>

using namespace std;

/*
https://www.codechef.com/APRIL15/problems/CARLOS

INPUT:
3
3 3 3
1 2
2 3
3 1
3 2 1
3 1 2
2 3
2 1
4 2 4
1 3
4 2
4 2 2 1
Output:
2
-1
2

*/

#define MAX_NODES 200
#define MAX_LEN 200000
#define MAX_INT 0x7fffffff

// No of nodes
int M;
// Word length
int N;

int g[MAX_NODES+1][MAX_NODES+1];
int color[MAX_NODES+1];
int word[MAX_LEN + 1];
int cur_color;
int dp[MAX_LEN + 1][MAX_NODES+1];

#define min(a,b) (a<b?a:b)


void DFSUtil(int u)
{
	color[u] = cur_color;

	for (int v = 1; v <= M; v++)
	{
		if (g[u][v] == 1 && color[v] == -1)
			DFSUtil(v);
	}
}

void colorNodes()
{
	// make all the colors -1
	for (int i = 1; i <= M; i++)
		color[i] = -1;

	// Initial color is 0
	cur_color = 0;
	color[0] = cur_color++;

	for (int i = 1; i <= M; i++)
	{
		if (color[i] == -1)
		{
			DFSUtil(i);
			cur_color++;
		}
	}
}

int findMinchange()
{
	// lets create the index 1
	for (int j = 1; j <= M; j++)
	{
		if (word[1] == j)
			dp[1][j] = 0;
		else if (color[word[1]] == color[j])
			dp[1][j] = 1;
	}

	// word index
	for (int i = 2; i <= N; i++)
	{
		int min_prev = MAX_INT;
		// all possible letter transformation
		for (int j = 1; j <= M; j++)
		{
			min_prev = min(dp[i - 1][j], min_prev);
			if (color[word[i]] == color[j])
			{
				if (min_prev != MAX_INT)
				{
					if (word[i] == j)
						dp[i][j] = min_prev;
					else
						dp[i][j] = min_prev + 1;
				}
			}
		}
	}

	int min1 = MAX_INT;
	for (int j = 1; j <= M; j++)
	{
		if (min1 > dp[N][j])
			min1 = dp[N][j];
	}

	return ((min1 != MAX_INT)?min1:-1);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	// No of Edges
	int E;
	for (int count = 1; count <= T; count++)
	{
		cin >> M;
		int u, v;

		cin >> E;

		cin >> N;

		// Initially all nodes have no relationship
		for (int i = 0; i <= M; i++)
		{
			for (int j = 0; j <= M; j++)
				g[i][j] = 0;
		}


		for (int cnt = 1; cnt <= E; cnt++)
		{
			cin >> u >> v;
			g[u][v] = 1;
			g[v][u] = 1;
		}

		colorNodes();

		for (int i = 1; i <= N; i++)
			cin >> word[i];

		for (int i = 0; i <= N; i++)
		{
			for (int j = 0; j <= M; j++)
				dp[i][j] = MAX_INT;
		}

		int answer = findMinchange();

		//cout << "#" << count << " " << answer << endl;
		cout << answer << endl;
	}
	return 0;
}