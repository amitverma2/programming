#include<iostream>

using namespace std;

#define GRID 100
#define MAX_INT 0x7FFFFFFFFFFFFFFF

int count = 0;
long long max_count = MAX_INT;

void DFSUtil(int g[GRID][GRID], int x, int y, bool** visited)
{
	visited[x][y] = true;

	if(y+1 < GRID && visited[x][y+1] == false && g[x][y+1] == 1)
	{
		count++;
		return DFSUtil(g, x, y+1, visited );
	}

	if(y-1 >=0 && visited[x][y-1] == false && g[x][y-1] == 1 )
	{
		count++;
		return DFSUtil(g, x, y-1, visited );
	}

	if(x+1 < GRID && visited[x+1][y] == false && g[x+1][y] == 1 )
		return DFSUtil(g, x+1, y, visited );

	return;
}


int compute(int g[GRID][GRID])
{
	int answer = -1;

	max_count = MAX_INT;

	bool** visited;
	visited = new bool* [GRID];
	for(int i=0; i<GRID; i++)
		visited[i] = new bool [GRID];


	for(int u=0; u<GRID;u++)
	{

		for(int i=0; i<GRID; i++)
		{
			for(int j=0; j<GRID; j++)
			{
				visited[i][j] = false;
			}
		}

		count = 0;

		if( g[0][u] == 1 && g[1][u] == 1)	
		{
			DFSUtil(g, 1, u, visited);
			if(count <= max_count)
			{
				max_count = count;
				answer = u;
			}
		}
	}

	for(int i=0; i<GRID; i++)
		delete[] visited[i] ;
	delete[] visited;

	return answer;
}

int main(int argc, char** argv)
{
	int test_case;

	freopen("input.txt", "r", stdin);

	int map[GRID][GRID];

	int number;

	int answer;

	for(test_case = 1; test_case <= 10; ++test_case)
	{
		cin >> number;
		for(int i=0; i<GRID; i++)
		{
			for(int j=0; j<GRID;j++)
			{
				cin >> map[i][j];
			}
		}

		answer = compute(map);

		cout << "#" << test_case << " " << answer << endl;
	}

	return 0;
}