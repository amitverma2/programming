#include <iostream>
#include <list>

using namespace std;

// Detect cycle in a undirected graph
/* We do a DFS traversal of the given graph. For every visited vertex ‘v’, if there is an adjacent ‘u’ such that u is already visited
and u is not parent of v, then there is a cycle in graph. If we don’t find such an adjacent for any vertex, we say that there is no cycle. 
The assumption of this approach is that there are no parallel edges between any two vertices.
*/

class Graph {
	int V;
	list<int>* adjlist;
    bool isCyclicUtil(int v, bool visited[], int parent);  // used by isCyclic()

public:
	Graph(int num);
	void addEdge(int src, int dest);
    bool isCyclic();    // returns true if there is a cycle in this graph
};

Graph::Graph(int num)
{
	V = num;
	adjlist = new list<int>[num];
}

void Graph::addEdge(int src, int dest)
{
	// Since, this is undirected graph
	adjlist[src].push_back(dest);
	adjlist[dest].push_back(src);
}


bool Graph::isCyclicUtil(int v, bool visited[], int parent)
{
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
	{
		if(visited[*i] == false)
		{
			if( isCyclicUtil(*i, visited, v) == true)
				return true;
		}
		else if (*i != parent)
			return true;
	}
	return false;
}

bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[V];

	for(int i =0; i<V; i++) {
		visited[i] = false;
	}

	// Run the loop for each node starting from 0th node.
	for (int v=0; v<V; v++)
	{
		if(!visited[v])
		{
			if( isCyclicUtil(v, visited, -1) )
			{
				return true;
			}
		}
	}
	return false;
}

int main()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(3, 2);
	g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
//    g.addEdge(5, 3);
 
    if(g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";

	getchar();
	return 0;
}
