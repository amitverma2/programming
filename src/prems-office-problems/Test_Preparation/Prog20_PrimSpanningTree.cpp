#include <iostream>
using namespace std;

#define V 5
#define INF 0x7FFFFFFF


// A utility function to print the constructed MST stored in parent[]
void printMST(int graph[V][V], int* parent)
{
	cout << "Edge      Weight\n";
	for (int i = 1; i <= V-1; i++)
		cout << parent[i] << " - " << i <<   "      " << graph[parent[i]][i]  << endl; 
}


int findminKey(bool* mstSet, int* key)
{
	int index = -1;
	int min_val = INF;

	for(int i=0; i<V;i++)
	{
		if(key[i] <= min_val && mstSet[i] == false)
		{
			index = i;
			min_val = key[i];
		}
	}
	return index;
}


void primMST(int g[V][V])
{
	int parent[V];
	bool mstSet[V];
	int key[V];

	for(int i=0; i<V; i++)
	{
		mstSet[i] = false;
		key[i] = INF;
	}

	//mstSet[0] = true; //note dont make this true now
	//it needs to be made true later, after being picked up by findmincall
	key[0] = 0;
	parent[0] = -1;

	int u;

	for(int count=1; count<=V-1; count++)
	{
		u = findminKey(mstSet, key);
		mstSet[u] = true;


		for(int v=0; v<V; v++)
		{
			if( g[u][v] != 0 && mstSet[v] == false && g[u][v] < key[v])
			{
				parent[v] = u;
				key[v] = g[u][v];
			}
		}
	}

	printMST(g, parent);
}


// driver program to test above function
int main()
{
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          */
   int graph[V][V] = {{0, 2, 0, 6, 0},
                      {2, 0, 3, 8, 5},
                      {0, 3, 0, 0, 7},
                      {6, 8, 0, 0, 9},
                      {0, 5, 7, 9, 0},
                     };
 
   // Print the solution
   primMST(graph);

   return 0;
}