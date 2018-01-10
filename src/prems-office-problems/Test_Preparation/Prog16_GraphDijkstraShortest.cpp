//////////////////////////////  Dijkstra’s Algorithm   ////////////////////////////////

#include<iostream>

using namespace std;

#define MAX_INT 0x7FFFFFFF

// Number of vertices in the graph
#define V 9

void printSolution (int* dist, int n)
{
	cout << "Vertex   Distance from Source\n";
	for(int i=0; i<n; i++)
		cout << i << "\t\t" << dist[i] << endl;
}

int minDistance(int dist[], bool sptSet[])
{
	int min = MAX_INT;
	int index = -1;

	for(int i=0; i<V; i++)
	{
	     //note that <= min is imp here, else we may end up returning -1 for index in some cases
		if(sptSet[i] == false && dist[i] <= min )
		{
			min = dist[i];
			index = i;
		}
	}
	return index;
}

void dijkstra(int graph[V][V], int u)
{
	int dist[V];  // distance of each vertex from vertex u
	bool sptSet[V];   // tells whether the vertice has been taken in the previous one

	for(int i=0; i<V; i++)
	{
		// all are at max distance and all are to be considered
		dist[i] = MAX_INT;
		sptSet[i] = false;
	}

	dist[u] = 0; //it has to be 0 distance and hence it would be picked up first also

	// run the loop for each of the vertices, 
	// NOTE THAT THE LOOP IS RUNNING FOR V-1 TIMES
	// See count is only used for counter  it is not used anywhere else inside the loop
	for(int count=0; count<V-1; count++)
	{
		u = minDistance(dist, sptSet);
		sptSet[u] = true;

		// need to find neighbours of u and update their dist, if applicable
		for(int v=0; v<V; v++)
		{
			if(sptSet[v] == false && graph[u][v] != 0 && dist[u] != MAX_INT && ( dist[u]+graph[u][v] < dist[v]) )
			{
				dist[v] = dist[u]+graph[u][v] ;
			}
		}
	}
	printSolution(dist, V);
}


int main()
{
	int	graph[V][V] = {
		{0, 4, 0, 0, 0, 0, 0, 8, 0},
		{4, 0, 8, 0, 0, 0, 0, 11, 0},
		{0, 8, 0, 7, 0, 4, 0, 0, 2},
		{0, 0, 7, 0, 9, 14, 0, 0, 0},
		{0, 0, 0, 9, 0, 10, 0, 0, 0},
		{0, 0, 4, 0, 10, 0, 2, 0, 0},
		{0, 0, 0, 14, 0, 2, 0, 1, 6},
		{8, 11, 0, 0, 0, 0, 1, 0, 7},
		{0, 0, 2, 0, 0, 0, 6, 7, 0}
	};

	dijkstra(graph, 0);   // Find shortest path for all vertices from node

	return 0;
}