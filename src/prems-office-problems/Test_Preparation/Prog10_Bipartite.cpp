#include <iostream>
#include <list>
#include <queue>

using namespace std;

/*
Following is a simple algorithm to find out whether a given graph is Birpartite or not using Breadth First Search (BFS).
1.	Assign RED color to the source vertex (putting into set U).
2.	Color all the neighbors with BLUE color (putting into set V).
3.	Color all neighbor’s neighbor with RED color (putting into set U).
4.	This way, assign color to all vertices such that it satisfies all the constraints of m way coloring problem where m = 2.
5.  While assigning colors, if we find a neighbor which is colored with same color as current vertex, then the graph cannot 
    be colored with 2 vertices (or graph is not Bipartite)
*/

class Graph {
	int V;
	list<int>* adjlist;

public:
	Graph(int num);
	void addEdge(int src, int dest);
    bool isBipartite(int v);  // finds whether it is bipartite starting from source vertex 'v'
};

Graph::Graph(int num)
{
	V = num;
	adjlist = new list<int>[num];
}

void Graph::addEdge(int src, int dest)
{
	// undirected graph
	adjlist[src].push_back(dest);
	adjlist[dest].push_back(src);
}

bool Graph::isBipartite(int v)
{
	int* color;
	color = new int[V];

	for(int i=0; i<V; i++)
		color[i] = -1; // -1 no color, 1 RED, 0 BLUE

	queue<int> Queue;

	// Start from 0th vertex
	Queue.push(v);
	color[v] = 1;

	while(!Queue.empty()) {
		v = Queue.front();
		Queue.pop();

		list<int>::iterator i;

		for(i=adjlist[v].begin(); i!=adjlist[v].end(); ++i)
		{
			if(color[*i] == -1)
			{
				color[*i] = 1-color[v];
				Queue.push(*i);
			}
			else if(color[v] == color[*i])
				return false;
		}
	}
	return true;
}


int main()
{
    Graph g(6);
	g.addEdge(0,1);
	g.addEdge(1,2);
	g.addEdge(2,3);
	g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(5,0);
	//g.addEdge(2,4);

	cout << "The given graph is Bipartite: " << ((g.isBipartite(0))?"Yes":"No") ;
 
	getchar();
    return 0;
}