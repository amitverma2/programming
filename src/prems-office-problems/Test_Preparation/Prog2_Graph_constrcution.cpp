#include<stdio.h>
#include<stdlib.h>

//Each node
struct AdjListNode {
	int data;
	struct AdjListNode* next;
};

//Single link list
struct AdjList {
	struct AdjListNode *head;
};

// The Actual graph representation, which is quite easy on the space side
struct Graph {
	int V;
	struct AdjList* arraylist;
};

// a utility function to create new nodes in the adjacency list
struct AdjListNode* newAdjListNode(int dest)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->data = dest;
	newNode->next = NULL;
	return newNode;
}

// a utility function to create graph of 'v' vertices
struct Graph* CreateGraph(int n)
{
	struct Graph* newGraph = (struct Graph*)malloc(sizeof(struct Graph));
	newGraph->V = n;

	newGraph->arraylist =  (struct AdjList*) malloc( n* sizeof(struct AdjList));

	for(int i=0; i<n; i++) {
		newGraph->arraylist[i].head = NULL;
	}
	return newGraph;
}


// adds an edge to undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
	// Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
	struct AdjListNode* newNode = newAdjListNode(dest);
	newNode->next = graph->arraylist[src].head;
	graph->arraylist[src].head = newNode;


	 // Since graph is undirected, add an edge from dest to src also
	newNode = newAdjListNode(src);
	newNode->next = graph->arraylist[dest].head;
    graph->arraylist[dest].head = newNode;
}

void printGraph(struct Graph* graph)
{
	int i;
	for(i=0; i<graph->V; i++)
	{
		printf("\n Adjacency  list for the vertex %d:\n head", i);
		struct AdjListNode* pCrawl = graph->arraylist[i].head;
		while(pCrawl) {
			printf(" -> %d", pCrawl->data);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}


int main()
{
	int num_vertices = 5;
	struct Graph* graph = CreateGraph(num_vertices);

	addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

	// print the adjacency list representation of the above graph
    printGraph(graph);

    getchar();
    return 0;
}