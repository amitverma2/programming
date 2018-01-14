/*
 * BFS using adjacency list/multimap/queue in C++
 * Covers directed and undirected graph
 *  - for undirected graph, comment out a line in main()
 *
 * To handle disconnected graphs, need to set DISCONNECTED_GRAPH_BFS
 * to 1
 *
 * Input
 * V M      number of verties: number of edges
 * x1 y1    edge 1
 * x2 y2
 * ...
 * xM yM    edge M
 * O        bfs Origin vertex
 *
 * NOTE: In this the vertex numbering starts from 0
 */
#include <iostream>
#include <map>
#include <queue>

#define DISCONNECTED_GRAPH_BFS 0 

bool verbose = false;

int V, M;
typedef std::multimap<int, int> MMI;
MMI adj;
typedef std::multimap<int, int>::const_iterator MMICI;
typedef std::vector<int> VI;
typedef std::queue<int> QI;

void bfs(MMI &adj, int O, VI &visited)
{
    QI queue;

#if DISCONNECTED_GRAPH_BFS
    /* this is needed if we are doing a bfs on disconnected
     * graph, where the caller will call the bfs function
     * on all the vertices of the graph. this will result
     * in calls with vertices that are already visited
     * in doing bfs with other vertices
     */
    if(visited[O])
        return;
#endif

    visited[O] = 1;
    queue.push(O);

    while(!queue.empty()) {
        int vertex = queue.front();
        std::cout << vertex << ' ';
        queue.pop();

        std::pair<MMICI, MMICI> range = adj.equal_range(vertex);
        for(MMICI i = range.first; i != range.second; i++) {
            if(!visited[(*i).second]) {
                visited[(*i).second] = 1;
                queue.push((*i).second);
            }
        }
    }

    return;
}

void doBfs(std::multimap<int, int> &adj, int O)
{
#if DISCONNECTED_GRAPH_BFS 
    if(verbose)
        std::cout << "Starting BFS assuming disconnected graph" << std::endl;

    VI visited(V);

    for(int i = 0 ; i < V; i++) {
        if(verbose)
            std::cout << std::endl << "Disconnected bfs for vertex " << i << std::endl;

        bfs(adj, i, visited);
    }
#else
    if(verbose)
        std::cout << "Starting BFS with vertex " << O << std::endl;

    VI visited(V);

    bfs(adj, O, visited);
#endif

    std::cout << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        verbose = true;

    std::cin >> V >> M;

    while(M--) {
        int x, y;
        std::cin >> x >> y;
        adj.insert(std::pair<int, int>(x, y));
    }
    if(verbose) {
        std::cout << "Graph with vertices 0 to " << V-1 << ","
            << " and following edges" << std::endl;
        for(MMICI i = adj.begin(); i != adj.end(); i++)
            std::cout << (*i).first << "->" << (*i).second << std::endl;
    }

    int O;
    std::cin >> O;

    doBfs(adj, O);

    return 0;
}
