#include <iostream>
#include <list>

using namespace std;

class Graph {
	int V;
	list<int>* adjlist;
	void DFSUtil(int v, bool visited[]);

public:
	Graph(int num);
	void addEdge(int src, int dest);
	void DFS(int v);
	//void DFS();
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


void Graph::DFSUtil(int v, bool visited[])
{
	if(visited[v])
		return;

	cout << v << " ";

	visited[v] = true;
	list<int>::iterator i;

	for(i = adjlist[v].begin(); i != adjlist[v].end(); ++i)
	{
		if(!visited[*i])
			DFSUtil(*i, visited);
	}
}

//void Graph:: DFS () //   if, we want to make sure all the nodes are visited
void Graph::DFS(int v)
{
	bool* visited;
	visited = new bool[V];

	for(int i =0; i<V; i++)
		visited[i] = false;
    //for (int v=0; v<V; v++)   //in that case, run DFS for all the nodes starting from node 0
	if(visited[v] == false)
	    DFSUtil(v, visited);
	cout << "\n";
}





int main()
{
	// Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

	g.DFS(0);
	g.DFS(1);
	g.DFS(2);
	g.DFS(3);

	//g.DFS();

	getchar();
	return 0;
}