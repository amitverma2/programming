// Ford Fulkersion flow problem
// MAX cut - Min flow problems
// This algo should find max flow and should also find min cut edges
#include <iostream>
#include <list>

using namespace std;

#define V 6
#define min(a,b) (a<b)?(a):(b)

#define INF 0x7FFFFFFF

void dfs(int graph[V][V], int u, bool* visited)
{
	visited[u] = true;

	for(int v=0; v<V; v++)
	{
		if(graph[u][v] > 0 && visited[v] == false)
		{
			dfs(graph, v, visited);
		}
	}
}


bool bfs(int graph[V][V], int s, int t, int parent[])
{
	list<int> q;
	bool visited[V];
	for(int i=0; i<V;i++)
		visited[i] = false;

	parent[s] = -1;
	q.push_back(s);
	visited[s] = true;

	while(!q.empty())
	{
		int u = q.front();
		q.pop_front();

		for(int v=0; v<V;v++)
		{
			// Note, the edge validity case
			// it needs to be greater than 0 to have a flow capacity in it
			if( !visited[v] && graph[u][v] > 0)
			{
				q.push_back(v);
				visited[v] = true;
				parent[v] = u;
			}
		}
	}
	return (visited[t] == true);
}

int fordFulkerson(int graph[V][V], int s, int t)
{
	int u,v;

	int rGraph[V][V];

	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			rGraph[i][j] = graph[i][j];
		}
	}

	int parent[V];

	int max_flow = 0;

	while( bfs(rGraph, s,t, parent) )
	{
		int path_flow = INF;

		for(v=t; v!=s; v=parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, rGraph[u][v]);

		}
		for(v=t; v!=s; v=parent[v])
		{
			u = parent[v];
			rGraph[u][v] -= path_flow;
			rGraph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}

	// Flow is maximum now, find vertices reachable from s
	bool visited[V];
	for(int i=0; i<V; i++)
		visited[i] = false;

	dfs(rGraph, s, visited);

	for(int i=0; i<V; i++)
	{
		for(int j=0; j<V; j++)
		{
			if(graph[i][j] && visited[i] && !visited[j])
				cout << i << " - " << j << endl;
		}
	}

	return max_flow;
}


int main()
{
	// Let us create a graph shown in the above example
	//  Refer http://www.geeksforgeeks.org/ford-fulkerson-algorithm-for-maximum-flow-problem/
	//  and http://www.geeksforgeeks.org/minimum-cut-in-a-directed-graph/ for the graph figure and max flow - min cut scenario
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
 
    cout << "The maximum possible flow is " << fordFulkerson(graph, 0, 5);
 
	getchar();
    return 0;
}