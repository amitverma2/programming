#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>

typedef std::pair<int, int> ii;
typedef std::vector<ii> vii;

bool debug = false;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

  // Try this input for Adjacency Matrix/List/EdgeList
  // Adj Matrix
  //   for each line: |V| entries, 0 or the weight
  // Adj List
  //   for each line: num neighbors, list of neighbors + weight pairs
  // Edge List
  //   for each line: a-b of edge(a,b) and weight
  /*
  6
    0  10   0   0 100   0
   10   0   7   0   8   0
    0   7   0   9   0   0
    0   0   9   0  20   5
  100   8   0  20   0   0
    0   0   0   5   0   0
  6
  2 2 10 5 100
  3 1 10 3 7 5 8
  2 2 7 4 9
  3 3 9 5 20 6 5
  3 1 100 2 8 4 20
  1 4 5
  7
  1 2 10
  1 5 100
  2 3 7
  2 5 8
  3 4 9
  4 5 20
  4 6 5
  */

    // Case 1
    std::cout << "------- AdjMatrix ------ \n";
    int AdjMatrix[100][100];
    int V;
    std::cin >> V;
    for(int i = 0 ; i < V; i++)
        for(int j = 0 ; j < V; j++) {
            int weight;
            std::cin >> weight;
            AdjMatrix[i][j] = weight;
        }
    // show the adjacency for vertex 0
    for(int j = 0 ; j < V; j++) {
        if(AdjMatrix[0][j]) std::cout << "0-" << j << " weight " << AdjMatrix[0][j] << std::endl;
    }

    // Case 2
    std::cout << "------- AdjList ------ \n";
    std::cin >> V;
    std::vector<vii> AdjList;
    AdjList.assign(V, vii());
    for(int i = 0; i < V; i++) {
        int N;
        std::cin >> N;
        for(int n = 0 ; n < N; n++) {
            int v, w;
            std::cin >> v >> w;
            AdjList[i].push_back(ii(v-1, w));
        }
    }
    // show the nieghbors for vertex 0
    for(vii::const_iterator i = AdjList[0].begin();
        i != AdjList[0].end(); i++)
        std::cout << "0-" << i->first << " weight " << i->second << std::endl;
    // Case 3
    std::cout << "------- EdgeList ------ \n";
    int E;
    std::cin >> E;
    std::vector<std::pair<int, ii> > EdgeList;
    for(int e = 0 ; e < E; e++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        EdgeList.push_back(std::make_pair(w, ii(a, b)));
    }
    std::sort(EdgeList.begin(), EdgeList.end());
    for(std::vector<std::pair<int, ii> >::const_iterator i = EdgeList.begin();
        i != EdgeList.end(); i++) {
        std::cout << "W " << i->first << " (" << i->second.first << ", " << i->second.second << ")\n";
    }
}
