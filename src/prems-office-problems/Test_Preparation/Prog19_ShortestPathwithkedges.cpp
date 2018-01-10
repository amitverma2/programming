#include <iostream>

using namespace std;

#define V 4

#define INF 999999999


int findShortestPath(int g[V][V], int u, int v, int k)
{
	if(k == 0 && u == v) return 0;
	else if(k==1 && g[u][v] != INF && g[u][v] != 0)
		return g[u][v];
	else if (k <= 0)
		return INF;

	int cur = INF;

	for(int i=0; i<V; i++)
	{
		if(g[u][i] != INF && u!=i && v!=i)
			// concentrate on intermdediate nodes other than u and v
		{
			int cur_res = findShortestPath(g, i, v, k-1);
			if(cur_res != INF)
			{
				cur_res += g[u][i];
				if(cur_res < cur)
					cur = cur_res;
			}
		}
	}
	return cur;
}



// driver program to test above function
int main()
{
	/* Let us create the graph shown in above diagram*/
	int graph[V][V] = {
		{0, 10, 3, 2},
		{INF, 0, INF, 7},
		{INF, INF, 0, 6},
		{INF, INF, INF, 0}
	};
	int u = 0, v = 3, k = 2;
	cout << "Weight of the shortest path is " << findShortestPath(graph, u, v, k);
	return 0;
}