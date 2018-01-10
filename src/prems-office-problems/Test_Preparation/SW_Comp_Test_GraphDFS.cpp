#include<iostream>

using namespace std;

#define V 100

bool DFSUtil(int** g, int u, bool* visited)
{
	if( u == 99)
		return true;

	visited[u] = true;

	for(int v=0; v<V; v++)
	{
		if(g[u][v] == 1)
		{
			if (!visited[v])
			{
				if(DFSUtil(g, v, visited))
					return true;
			}
		}
	}
	return false;
}



bool DFS(int** g, int s)
{
	bool* visited;

	visited = new bool[V];

	for(int i =0; i<V; i++)
		visited[i] = false;

	return DFSUtil(g, s, visited);

}


int main(int argc, char** argv)
{
	int T;
	/* 
	The freopen function below opens input.txt in read only mode and 
	sets your standard input to work with the opened file. 
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);

	int E;
	int u, v;
	int **g;
	bool find;
	int test_case;

	while(cin >> test_case)
	{

		//cin >> test_case;
		cin >> E;

		g = new int*[V];
		for(int i=0;i<V;i++)
			g[i] = new int[V];

		for(int i=0; i<V; i++)
		{
			for(int j=0; j<V; j++)
			{
				g[i][j] = 0;
			}
		}

		for(int i=0; i<E; i++)
		{
			cin >> u; cin >> v;
			g[u][v] = 1;
		}

		find = DFS(g, 0);


		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << find << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}