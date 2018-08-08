// Interview cake
// Mesh Message
// Given information about active users on the network, find
// the shortest route for a message from one user (the sender)
// to another (the recipient). Return a vector of users that
// make up this route.
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<vector>
#include<list>

bool debug = false;

typedef std::unordered_map<std::string, std::vector<std::string> > UMSVS;
typedef std::vector<std::string> VS;

void readInput(UMSVS &network)
{
    // format of input
    // N -> total number of edges
    // <Name1> M1
    // Friend1 Friend2 ... FriendM1
    // <Name2> M2
    // Friend1 Friend2 ... FriendM2
    // ...
    // <Name2> Mn
    // Friend1 Friend2 ... FriendMn
    int N;
    std::cin >> N;
    while(N-- > 0) {
        std::string aFriend;;
        int friends_num;
        std::cin >> aFriend;
        std::cin >> friends_num;
        if(debug) std::cout << "Adding " << friends_num
            << " friends of \"" << aFriend << "\"\n";
        std::vector<std::string> hisFriends;
        while(friends_num-- > 0) {
            std::string hisFriend;
            std::cin >> hisFriend;
            hisFriends.push_back(hisFriend);
            if(debug) std::cout << " " << hisFriend;
        }
        if(debug) std::cout << std::endl;
        network[aFriend] = hisFriends;
    }
}

bool findShortestPath(UMSVS &network,
                      std::string &from,
                      std::string &receiver,
                      VS &path)
{
    // Do a BFS and return the path if found
    std::unordered_set<std::string> visited;
    std::list<std::string> bfs;
    // To find the path for the message I am using
    // a list that would be one to one mapped to
    // the bfs node list
    // a node in bfs list  --------> a Path in all path
    // must make sure that bfs list and allPaths list
    // are always in lockstep (push, pops)
    std::list<std::vector<std::string> > allPaths;
    std::vector<std::string> curPath;

    bfs.push_front(from);
    // lockstep path
    curPath.push_back(from);
    allPaths.push_front(curPath);

    while(!bfs.empty()) {
        std::string aFriend;
        aFriend = bfs.front();
        bfs.pop_front();
        // lockstep path
        curPath = allPaths.front();
        allPaths.pop_front();
        if(debug) std::cout << "BFS : At friend \"" << aFriend << "\"\n";
        visited.insert(aFriend);
        for(VS::const_iterator i = network[aFriend].begin();
            i != network[aFriend].end(); i++) {
            if(*i == receiver) {
                // not clue about path and length
                if(debug) std::cout << "Found receiver! \"" << *i << "\" Return true...\n";
                path = curPath;
                // add this element to the path
                path.push_back(*i);
                return true;
            }
            if(visited.find(*i) != visited.end()) {
                if(debug) std::cout << "Child traversal Revisiting \"" << *i << "\" skip further...\n";
                continue;
            }
            if(debug) std::cout << "Child traversal adding \"" << *i << "\" ...\n";
            bfs.push_back(*i);
            // add this node to the current path
            std::vector<std::string> newPath = curPath;
            newPath.push_back(*i);
            // lockstep path
            allPaths.push_back(newPath);
        }
    }
    return false;
}

void handleQueries(UMSVS &network)
{
    // M -> number of queries
    // senderFriend1 receiverFriend1
    // ...
    // senderFriendM receiverFriendM
    int M;
    std::cin >> M;
    while(M-- > 0) {
        std::string sender, receiver;
        std::cin >> sender >> receiver;
        VS path;
        if(debug) std::cout << "Finding shortest path from \"" << sender << "\" to \"" << receiver << "\"\n";
        if(findShortestPath(network, sender, receiver, path)) {
            std::cout << "Found path from \"" << sender << "\" to \"" << receiver << "\"\n";
            for(VS::const_iterator i = path.begin();
                i != path.end();
                i++) {
                std::cout << " " << *i ;
            }
            std::cout << std::endl;
        } else {
            std::cout << "No path from \"" << sender << "\" to \"" << receiver << "\"\n";
        }
    }
    return;
}

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    std::unordered_map<std::string, std::vector<std::string> > network;
    readInput(network);
    handleQueries(network);

    return 0;
}

