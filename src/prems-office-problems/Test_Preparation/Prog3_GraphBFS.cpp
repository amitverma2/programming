#include <iostream>
#include <list>

using namespace std;

// This class represents a directed graph using adjacency list representation
class Graph {
	int V;
	list<int>* adj;

public:
	Graph(int num);
	void addEdge(int src, int dest);
	void BFS(int s);

};

Graph::Graph(int num)
{
	V = num;
	adj = new list<int>[num];
}

void Graph::addEdge(int src, int dest)
{
	adj[src].push_back(dest);
}

void Graph::BFS(int s)
{
	bool* visited = new bool[V];
	for(int i=0;i<V;i++)
		visited[i] = false;

	list<int> queue;
	list<int>::iterator i;

	visited[s] = true;
	queue.push_back(s);

	while(!queue.empty() ) {
		s = queue.front();
		// This is where we are making the node count in BFS
		cout << s << " ";
		queue.pop_front();

		for(i=adj[s].begin(); i != adj[s].end(); ++i)
		{
			if(visited[*i] == false)
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}
	cout << "\n";
}


int main()

{
	Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

	g.BFS(0);
	g.BFS(1);
	g.BFS(2);
	g.BFS(3);

	getchar();
	return 0;
}