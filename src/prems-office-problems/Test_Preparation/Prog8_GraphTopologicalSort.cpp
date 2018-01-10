#include <iostream>
#include <list>
#include <stack>

using namespace std;

/*
We can modify DFS to find Topological Sorting of a graph. In DFS, we start from a vertex, we first print it and then recursively 
call DFS for its adjacent vertices. In topological sorting, we use a temporary stack. We don’t print the vertex immediately, we first 
recursively call topological sorting for all its adjacent vertices, then push it to a stack. Finally, print contents of stack. 
Note that a vertex is pushed to stack only when all of its adjacent vertices (and their adjacent vertices and so on) are already in stack.
*/

class Graph {
	int V;
	list<int>* adjlist;
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);  // used by isCyclic()

public:
	Graph(int num);
	void addEdge(int src, int dest);
    void topologicalSort();  // no need of initial vertex, we shall start from 0th
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

void Graph::topologicalSortUtil(int v, bool visited[], stack<int>& Stack)
{
	visited[v] = true;

	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
	{
		if(visited[*i] == false)
		{
			topologicalSortUtil(*i, visited, Stack);
		}
	}
    // Push current vertex to stack which stores result
	// since all its children have been visited and recursively already store in the stack
	Stack.push(v);
}


void Graph::topologicalSort()
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
	while(!Stack.empty()) {
		cout << Stack.top() << " ";
		Stack.pop();

	}
	cout << "\n";
}

int main()
{
   // Create a graph given in the above diagram
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
 
    cout << "Following is a Topological Sort of the given graph \n";
    g.topologicalSort();
 
	getchar();
    return 0;
}