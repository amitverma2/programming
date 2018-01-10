////////////////////////////////// BellManFord Algorithm //////////////////////////////////////////////////////////////////////////
//// Note that in Bellman Ford, since we deal with Edges mainly v-1 times, its better to store the graph in terms of edges, so that
//// algorithm can be applied easily
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#define MAX_INT 0x7FFFFFFF

using namespace std;

class Graph
{
	int V; // total no of vetices
	int E; // total no of edges
	int edge_count; // current counter, helps in edge addition

	struct Edge
	{
		int u; // starting point
		int v; // end point
		int weight; // weight of the edges
		struct Edge(int u1, int v1, int w1): u(u1), v(v1), weight(w1) {}
		struct Edge():u(0), v(0), weight(0) {}
	};

	Edge* edge;
public:
	Graph(int V1, int E1);
	void addEdge(int u, int v, int weight);
	void BellmanFord(int s);
	~Graph();

};

Graph::~Graph()
{
	V = E = edge_count = 0;
	delete[] edge;
}

Graph::Graph(int V1, int E1)
{
	V = V1;
	E = E1;
	edge = new Edge[E];
	edge_count = 0;
}

void Graph::addEdge(int u, int v, int weight)
{
	edge[edge_count++] = Edge(u, v, weight);
}

void Graph::BellmanFord(int s)
{
	int* dist;

	dist = new int[V];

	// Step 1: Initialize distances from src to all other vertices as INFINITE
	for(int i=0; i<V; i++)
	{
		dist[i] = MAX_INT;
	}

	dist[s] = 0;
	int u,v,w;

	// Step 2: Relax all edges |V| - 1 times. 
	// A simple shortest path from src to any other vertex can have at-most |V| - 1 edges
	for(int i=0; i<V-1; i++)
	{
		for(int j=0; j<E; j++)
		{
			u = edge[j].u;
			v = edge[j].v;
			w = edge[j].weight;

			if(dist[u] != MAX_INT && dist[u]+w < dist[v])
				dist[v] = dist[u]+w;
		}
	}

	// Step 3: check for negative-weight cycles.  The above step guarantees
    // shortest distances if graph doesn't contain negative weight cycle.
    // If we get a shorter path, then there is a cycle.

		for(int j=0; j<E; j++)
		{
			u = edge[j].u;
			v = edge[j].v;
			w = edge[j].weight;

			if(dist[u] != MAX_INT && dist[u]+ w < dist[v])
			{
				cout << "Graph contains negative weight cycle";
				return;
			}
		}

		//Lets print the vertices and their distances now
		cout << "Vertex   Distance from Source\n";
        for (int i = 0; i < V; ++i)
		{

			//cout << i << "\t\t"  << dist[i] << endl;
			cout << i<< "\t\t";
			cout.width(2);
			cout << std::right;
			cout << dist[i] << endl;
		}
}


int main()
{
	Graph g(5,8);
	g.addEdge(0,1,-1);
	g.addEdge(0,2,4);
	g.addEdge(1,2,3);
	g.addEdge(1,3,2);
	g.addEdge(1,4,2);
	g.addEdge(3,2,5);
	g.addEdge(3,1,1);
	g.addEdge(4,3,-3);
	g.BellmanFord(0);

	return 0;
}
