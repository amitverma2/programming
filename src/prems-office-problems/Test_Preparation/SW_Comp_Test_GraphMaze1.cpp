#include<iostream>

using namespace std;

#define N 16


bool DFSUtil(int g[N][N], int x, int y, bool** visited)
{
	if(g[x][y] == 3)
		return true;

	visited[x][y] = true;

	if(x-1 >=0 && visited[x-1][y] == false && (g[x-1][y] == 0 || g[x-1][y] == 3) && DFSUtil(g, x-1, y, visited ) )
		return true;

	if(x+1 < N && visited[x+1][y] == false && (g[x+1][y] == 0 || g[x+1][y] == 3) && DFSUtil(g, x+1, y, visited ) )
		return true;

	if(y-1 >=0 && visited[x][y-1] == false && (g[x][y-1] == 0 || g[x][y-1] == 3) && DFSUtil(g, x, y-1, visited ) )
		return true;

	if(y+1 < N && visited[x][y+1] == false && (g[x][y+1] == 0 || g[x][y+1] == 3) && DFSUtil(g, x, y+1, visited ) )
		return true;

	return false;
}


bool compute(int g[N][N])
{
	bool find = false;

	bool** visited;
	visited = new bool* [N];
	for(int i=0; i<N; i++)
		visited[i] = new bool [N];

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			visited[i][j] = false;
		}
	}

	int x,y;
	bool flag = false;
	for(x=0; x<N; x++)
	{
		for(y=0; y<N; y++)
		{
			if(g[x][y] == 2)
			{
				flag = true;
				break;
			}
		}
		if(flag)
			break;
	}
	find = DFSUtil(g, x, y, visited);

	for(int i=0; i<N; i++)
		delete[] visited[i];

	delete[] visited;

	return find;
}

int main(int argc, char** argv)
{
	int test_case;

	freopen("input.txt", "r", stdin);

	char str[N+1];
	int g[N][N];

	int number;

	for(test_case = 1; test_case <= 10; ++test_case)
	{
		cin >> number;
		for(int i=0; i<N; i++)
		{
			cin >> str;
			for(int j=0; j<N;j++)
			{
				g[i][j] = str[j]-'0';
			}
		}

		bool find;

		find = compute(g);

		cout << "#" << test_case << " " << (find?1:0) << endl;
	}

	return 0;
}