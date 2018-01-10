#include <iostream>
#include <list>

using namespace std;

// Detect cycle in a directed graph
// the node should not already be considered while moving in the recursion

class Graph {
	int V;
	list<int>* adjlist;
    bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()

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
	adjlist[src].push_back(dest);
}


bool Graph::isCyclicUtil(int v, bool visited[], bool* recStack)
{
	if(visited[v] == false)
	{
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
		{
			if(visited[*i] == false)
			{
				if( isCyclicUtil(*i, visited, recStack) == true)
					return true;
			}
			else if (recStack[*i] == true)
				return true;
		}
	}
    recStack[v] = false;  //clear this, since this node is not the one which is part of cycle
	return false;
}


bool Graph::isCyclic()
{
    // Mark all the vertices as not visited and not part of recursion stack
    bool *visited = new bool[V];
	// For recStack note that the nodes that are part of cycle would be having 1s and others would be having 0s
    bool *recStack = new bool[V];

	for(int i =0; i<V; i++) {
		visited[i] = false;
		recStack[i] = false;
	}

	// Run the loop for each node starting from 0th node ---this is very imp, think from 
	// from the point of view of non connected graph.
	for (int v=0; v<V; v++) {
	    if( isCyclicUtil(v, visited,recStack) )
		{
			cout << "cycle information\n";
			for(int i=0; i<V; ++i)
				cout << "recStack[" << i << "]: " << recStack[i] << " \n";
			return true;
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
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
 
    if(g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";

	getchar();
	return 0;
}