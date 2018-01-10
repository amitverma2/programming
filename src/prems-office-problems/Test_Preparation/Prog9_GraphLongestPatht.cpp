#include <iostream>
#include <list>
#include <stack>

#include <limits.h>
#define NINF INT_MIN

using namespace std;

/*
Longest Path in a Directed Acyclic Graph
the longest path problem has a linear time solution for directed acyclic graphs.
we use Tological Sorting.

We initialize distances to all vertices as minus infinite and distance to source as 0,
then we find a topological sorting of the graph. Topological Sorting of a graph represents 
a linear ordering of the graph (See below, figure (b) is a linear representation of figure (a) ). 
Once we have topological order (or linear representation), we one by one process all vertices in 
topological order. For every vertex being processed, we update distances of its adjacent using 
distance of current vertex.
*/

class AdjListNode {
	int v;       // vertex no of this node
    int weight;  // weight of this node
public:
	AdjListNode(int _v, int _w): v(_v), weight(_w){}
	int getV() { return v;}
	int getWeight() { return weight;}
};

class Graph {
	int V;
	list<AdjListNode>* adjlist;
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);  // used by isCyclic()

public:
	Graph(int num);
	void addEdge(int src, int dest, int weight);
    void longestPath(int s);  // Finds the longest path from given vertex s
};

Graph::Graph(int num)
{
	V = num;
	adjlist = new list<AdjListNode>[num];
}

void Graph::addEdge(int src, int dest, int weight)
{
	AdjListNode node(dest, weight);
	adjlist[src].push_back(node); // add dist to src list, so that edge is src->dest
}

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	// Mark the current node as visited
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<AdjListNode>::iterator i;
	for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
	{
		AdjListNode node = *i;
		if(visited[node.getV()] == false)
		{
			topologicalSortUtil(node.getV(), visited, Stack);
		}
	}
    // Push current vertex to stack which stores result
	// since all its children have been visited and recursively already store in the stack
	Stack.push(v);
}


void Graph::longestPath(int s)  // longest path from vertex s
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];

	for(int i =0; i<V; i++) {
		visited[i] = false;
	}

	stack<int> Stack ;  // created a new stack that would hold the node, when all its children are already visited recursively

	// Run the loop for each node starting from 0th node.
	for (int v=0; v<V; v++) {
	    if(!visited[v])
		{
			topologicalSortUtil(v, visited, Stack);
		}
	}
	int *dist;
	dist = new int[V];

	for(int i =0; i<V; i++) {
		dist[i] = NINF;
	}
	dist[s] = 0;

	while(!Stack.empty()) {
		int u;
		u = Stack.top();
		Stack.pop();
		list<AdjListNode>::iterator i;
		if(dist[u] != NINF)
		{
			for(i=adjlist[u].begin(); i!=adjlist[u].end(); ++i)
			{
				if(dist[i->getV()] < dist[u] + i->getWeight() )
					dist[i->getV()] = dist[u] + i->getWeight() ;
			}
		}
	}

	for(int i =0; i<V; i++) {
		(dist[i] == NINF)? cout << "INF ": cout << dist[i] << " ";
	}
}

int main()
{
// Create a graph given in the above diagram.  Here vertex numbers are
    // 0, 1, 2, 3, 4, 5 with following mappings:
    // 0=r, 1=s, 2=t, 3=x, 4=y, 5=z
    Graph g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 4, 4);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 1);
    g.addEdge(3, 4, -1);
    g.addEdge(4, 5, -2);
 
    int s = 1;
    cout << "Following are longest distances from source vertex " << s <<" \n";
    g.longestPath(s);
 
	getchar();
    return 0;
}