#include <iostream>
#include <list>

using namespace std;

/*
An undirected graph is tree if it has following properties.
1) There is no cycle.
2)The graph is connected.
*/


class Graph {
	int V;
	list<int>* adjlist;
    bool isCyclicUtil(int v, bool visited[], int parent);  // used by isCyclic()

public:
	Graph(int num);
	void addEdge(int src, int dest);
    bool isTree();    // returns true if there is a cycle in this graph
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

// Returns true if the graph is a tree, else false.
bool Graph::isTree()
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[V];

	for(int i =0; i<V; i++) {
		visited[i] = false;
	}

    // The call to isCyclicUtil serves multiple purposes
    // It returns true if graph reachable from vertex 0 is cyclcic.
    // It also marks all vertices reachable from 0.
	if( isCyclicUtil(0, visited, -1) )
	{
		return false;
	}

	for (int v=0; v<V; v++)
	{
		if(!visited[v])
			return false;
	}

	return true;
}

int main()
{
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.isTree()? cout << "Graph is Tree\n":
                 cout << "Graph is not Tree\n";
 
    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.isTree()? cout << "Graph is Tree\n":
                 cout << "Graph is not Tree\n";

	getchar();
 
    return 0;

	getchar();
	return 0;
}
