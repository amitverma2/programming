/*            Snake ladder problem    */
#include <iostream>
#include <queue>

using namespace std;

/*
The idea is to consider the given snake and ladder board as a directed graph with number of vertices equal to the number of cells in the board. 
The problem reduces to finding the shortest path in a graph. Every vertex of the graph has an edge to next six vertices if next 6 vertices do not 
have a snake or ladder. If any of the next six vertices has a snake or ladder, then the edge from current vertex goes to the top of the ladder or 
tail of the snake. Since all edges are of equal weight, we can efficiently find shortest path using Breadth First Search of the graph.
*/

// An entry in queue used in BFS, we just dont want to store the nodes in the queue
// we are also interested in the distance of this node from the starting node, hence another member dist is being used
struct queueEntry
{
    int v;     // Vertex number
    int dist;  // Distance of this vertex from source
};

// move[] is an array of size N where N is no. of cells on board
// If there is no snake or ladder from cell i, then move[i] is -1
// Otherwise move[i] contains cell to which snake or ladder at i
// takes to.
int getMinDiceThrows(int moves[], int N)
{
	// The graph has N vertices. Mark all the vertices as
    // not visited
    bool *visited = new bool[N];
    for (int i = 0; i < N; i++)
        visited[i] = false;

	queue<queueEntry> Queue;

	queueEntry s = {0,0};
	Queue.push(s);
	visited[0] = true;

	while(!Queue.empty()) {
		s = Queue.front();
		//cout << "The popped out node is: " << s.v << "\n";
		int v;
		v = s.v;
		if(v == N-1) // we have reached the last node
			break;

		Queue.pop();

		for(int i=v+1; i<=v+6 && i< N; i++)
		{
			if(visited[i] == false)
			{
				queueEntry a;
				a.dist = s.dist + 1;
				if(moves[i] == -1)
					a.v = i;
				else
					a.v = moves[i];
				Queue.push(a);
				visited[i] = true;
			    //cout << "***********The pushed  node is: " << a.v << "\n";
			}
		}
	}
	return s.dist;
}



int main()
{
	int N = 30;
	int* moves;
	moves = new int[N];
	// Graph construction, where each edge has a edge to next one, being denoted by -1
	for(int i=0; i<N; i++)
		moves[i] = -1;

    // Ladders, note that values are greater than indices, since we are going up
    moves[2] = 21;
    moves[4] = 7;
    moves[10] = 25;
    moves[19] = 28;
 
    // Snakes, note that values are smaller than indices, since we are going down
    moves[26] = 0;
    moves[20] = 8;
    moves[16] = 3;
    moves[18] = 6;

    cout << "Min Dice throws required is " << getMinDiceThrows(moves, N);

	getchar();

    return 0;
}