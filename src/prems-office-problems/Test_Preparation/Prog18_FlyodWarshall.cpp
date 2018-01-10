////////////////////////////// Floyd Warshall Algorithm /////////////////////////////////
/*
The idea is to one by one pick all vertices and update all shortest paths which include the picked vertex as an intermediate vertex in 
the shortest path. When we pick vertex number k as an intermediate vertex, we already have considered vertices {0, 1, 2, .. k-1} as intermediate 
vertices. For every pair (i, j) of source and destination vertices respectively, there are two possible cases.
1) k is not an intermediate vertex in shortest path from i to j. We keep the value of dist[i][j] as it is.
2) k is an intermediate vertex in shortest path from i to j. We update the value of dist[i][j] as dist[i][k] + dist[k][j].

*/

#include <iostream>

using namespace std;

// Number of vertices in the graph
#define V 4

/* Define Infinite as a large enough value. This value will be used
for vertices not connected to each other */
#define INF 999999999

/* A utility function to print solution */
void printSolution(int dist[][V])
{
	cout << "Following matrix shows the shortest distances between every pair of vertices \n";
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			cout.width(7);
			if (dist[i][j] == INF)
				cout << "INF";
			else
				cout << dist[i][j];
		}
		cout << endl;
	}
}

void floydWarshell(int graph[][V])
{
	/* dist[][] will be the output matrix that will finally have the shortest 
	distances between every pair of vertices */
	int dist[V][V], i, j, k;

	/* Initialize the solution matrix same as input graph matrix. Or 
	we can say the initial values of shortest distances are based
	on shortest paths considering no intermediate vertex. */

	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			dist[i][j] = graph[i][j];

    /* Add all vertices one by one to the set of intermediate vertices.
      ---> Before start of a iteration, we have shortest distances between all
      pairs of vertices such that the shortest distances consider only the
      vertices in set {0, 1, 2, .. k-1} as intermediate vertices.
      ----> After the end of a iteration, vertex no. k is added to the set of
      intermediate vertices and the set becomes {0, 1, 2, .. k} */

	for(k=0; k<V; k++)
	{
		for(i=0; i<V; i++)
		{
			for(j=0; j<V; j++)
			{
				if( dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	// Print the shortest distance matrix
	printSolution(dist);

}


// driver program to test above function
int main()
{
	/* Let us create the following weighted graph
            10
       (0)------->(3)
        |         /|\
      5 |          |
        |          | 1
       \|/         |
       (1)------->(2)
            3 
    /*

	/*
	Note that the value of graph[i][j] is 0 if i is equal to j 
	And graph[i][j] is INF (infinite) if there is no edge from vertex i to j
	*/

	int graph[V][V] = { 
		{0,   5,  INF, 10},
		{INF, 0,   3, INF},
		{INF, INF, 0,   1},
		{INF, INF, INF, 0}
	};

	// Print the solution
	floydWarshell(graph);
	return 0;
}