#include <iostream>
#include <list>

using namespace std;

class Graph {
	int V;
	list<int>* adj;

public:
	Graph(int num);
	void addEdge(int src, int dest);
	void DFS(int v);
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
	
void Graph::DFS(int s)
{
	bool* visited;
	visited = new bool[V];

	for(int i=0; i<V; i++)
		visited[i] = false;

	list<int> stack;
	list<int>::iterator i;

	//If you want to count all the nodes, do this
	// this way u dont want s to be passed as parameter
	//for(s=0; s<V; s++)
	//{
		//if(visited[s] == false) {
			stack.push_back(s);
			visited[s] = true;
			while(stack.empty() == false)
			{
				s = stack.back();
				// This is where we are making the node count in DFS
				cout << s << " ";
				stack.pop_back();

				for(i=adj[s].begin(); i != adj[s].end(); ++i)
				{
					if(visited[*i] == false) {
						stack.push_back(*i);
						visited[*i] = true;
					}
				}
			}
		//}
	//}
	cout << "\n";
}




int main()
{
// Create a graph given in the above diagram
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    //g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);

	g.DFS(0);
	g.DFS(1);
	g.DFS(2);
	g.DFS(3);

	getchar();
	return 0;
}