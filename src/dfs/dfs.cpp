/*
 * Depth first search of a directed graph
 *  - also covers undirected graph, need to comment a line in main()
 *
 * This does not handle disconnected graphs well. For disconnected graphs
 * a minor modification is needed, in that we should do a dfs for all the
 * vertices.
 *
 * Input
 * V M      number of verties: number of edges
 * x1 y1    edge 1
 * x2 y2
 * ...
 * xM yM    edge M
 * O        dfs Origin vertex
 *
 * Few URLs for refernece
 * https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-1-dfs-of-unweighted-and-undirected/
 *
 * http://www.cs.princeton.edu/~rs/talks/samples.pdf
 *
 * https://www.geeksforgeeks.org/depth-first-traversal-for-a-graph/
 *
 */
#include <iostream>
#include <map>
#include <vector>

bool debug_on;

void dfs(std::multimap<int, int> &adj,
         std::vector<int> &visited,
         int V,
         int O)
{
    if(debug_on)
        std::cout << "From " << O << std::endl;
    else
        std::cout << O << ' ';
    visited[O] = 1;

    typedef std::multimap<int, int>::const_iterator MMCI;
    std::pair<MMCI, MMCI> vertices = adj.equal_range(O);
    for(MMCI i = vertices.first; i != vertices.second; i++) {
        if(!visited[(*i).second]) {
            visited[(*i).second] = 1;
            if(debug_on)
                std::cout << "... visiting " << (*i).second << std::endl;
            dfs(adj, visited, V, (*i).second);
        }
    }
    if(debug_on)
        std::cout << "...... returning\n";
    return;
}

void doDfs(std::multimap<int, int> &adj, int V, int O)
{
    std::vector<int> visited(V+1); // +1 because vectors are indexed with 0, which i don't use

    /* for disconnected graph the following needs to be done
     * for(i: 1..V)
     *  dfs(adj, visited, V, i);
     */
    dfs(adj, visited, V, O);
    return;
}

/*
 * Input
 * V M      number of verties: number of edges
 * x1 y1    edge 1
 * x2 y2
 * ...
 * xM yM    edge M
 * O        dfs Origin vertex
 */
int main(int argc, char *argv[])
{
    if(argc > 1)
        debug_on = true;

    std::multimap<int, int> adj;

    int V; // number of vertices
    // assuming Vertices is 1 - V in numbers.
    // 0 is an invalid vertex
    int M; // number of edges

    std::cin >> V >> M;

    while(M--) {
        int x, y;
        std::cin >> x >> y;
        adj.insert(std::pair<int, int>(x, y));
        // uncomment below for undirected graphs
        // adj.insert(std::pair<int, int>(y, x));
    }
    if(debug_on) {
        std::cout << "Here is the adj list\n";
        for(std::multimap<int, int>::const_iterator i = adj.begin();
            i != adj.end();
            i++)
            std::cout << (*i).first << " connected to " << (*i).second << std::endl;
    }

    int O;
    std::cin >> O;

    if(debug_on)
        std::cout << "Start dfs with " << O << std::endl;
    doDfs(adj, V, O);

    std::cout << std::endl;
    return 0;
}
