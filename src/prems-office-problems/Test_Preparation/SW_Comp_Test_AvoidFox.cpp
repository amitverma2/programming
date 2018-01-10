#include<iostream>

using namespace std;

#define N 20

int findRabKilled(int g[N][N], int x, int y)
{
	int count;
	count = 0;

	int i, j;
	i = x; j = y;

	for(j = y-1; j>=0; --j)
		count+= g[i][j];
	i = x; j = y;


	for(j = y+1; j<N; j++)
		count+= g[i][j];
	i = x; j = y;

	for(i=x-1; i>=0; --i)
		count+= g[i][j];
	i = x; j = y;

	for(i=x+1; i<N; i++)
		count+= g[i][j];
	i = x; j = y;

	for(i=x-1, j=y-1; i>=0 && j>=0; --i, --j)
		count+= g[i][j];
	i = x; j = y;

	for(i=x+1, j=y+1; i<N && j<N; ++i, ++j)
		count+= g[i][j];
	i = x; j = y;

	for(i=x-1, j=y+1; i>=0 && j<N; --i, ++j)
		count+= g[i][j];
	i = x; j = y;

	for(i=x+1, j=y-1; i<N && j>=0; ++i, --j)
		count+= g[i][j];
	i = x; j = y;

	return count;
}


int main()
{
	int test_case;
	/* 
	The freopen function below opens input.txt in read only mode and 
	sets your standard input to work with the opened file. 
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);

	int g[N][N];

	int x,y;
	int rabn;
	int answer;
	int u,v;
	int i,j;

	/*
	Read each test case from standard input.
	*/
	for(test_case = 1; test_case <= 10; test_case++)
	{
		cin >> rabn;

		for(i=0; i<N; i++)
		{
			for(j=0; j<N; j++)
			{
				g[i][j] = 0;
			}
		}

		cin >> x >> y;
		x--; y--;

		g[x][y] = -1;

		for(i=0; i<rabn; i++)
		{
			cin >> u >> v;
			u--; v--;
			g[u][v] = 1;
		}


		answer = findRabKilled(g, x, y);

		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << answer << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}
