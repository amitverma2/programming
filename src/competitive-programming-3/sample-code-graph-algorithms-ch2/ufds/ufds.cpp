// Union find disjoint sets
// described in the competitive programming 3 book
// section 2.4.2
// Need to have efficient
//  merge operation - unionSet(i,j) - put i & j in same set
//  find if same set - isSameSet(i,j) - true if same set, false otherwise
#include<iostream>
#include<vector>

typedef std::vector<int> vi;

bool debug = false;

class UnionFindDisjointSet {
    private:
    vi p;       // parent of elements
    vi rank;    // rank of element
    public:
        UnionFindDisjointSet(int N) {
            p.assign(N, 0); // resize the vector to N elements, and make all elements 0
            rank.assign(N, 0);

            for(int i = 0 ; i < N ; i++)
                p[i] = i;   // all elements are in disjoint sets to start with;
        }
        int findSet(int i) {    // find the head of the set to which 'i' belongs to
            if(i == p[i]) return i;
            
            // also do path compression/collapsing
            return p[i] = findSet(p[i]);
            // fixme??? why we don't need to update rank along with parent
        }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        void unionSet(int i, int j) {
            if(isSameSet(i, j)) return;
            if(rank[findSet(i)] > rank[findSet(j)]) {
                p[findSet(j)] = findSet(i);
            } else if(rank[findSet(i)] < rank[findSet(j)]) {
                p[findSet(i)] = findSet(j);
            } else {
                p[findSet(i)] = findSet(j);
                rank[findSet(j)]++;
            }
        }
        int sizeOfSet(int _i) {
            int sz = 0;
            for(int i = 0 ; i < p.size() ; i++)
                if(findSet(_i) == findSet(i)) sz++;

            return sz;
        }
        int numDisjointSets(void) {
            int num = 0;
            for(int i = 0 ; i < p.size() ; i++)
                if(i == p[i]) num++;
            return num;
        }
};

int main(int argc, char *argv[])
{
    int N = 10;

    UnionFindDisjointSet ufds(N);

    std::cout << "0, & 3 are " << (ufds.isSameSet(0, 3)?"same":"disjoint") << " sets." << std::endl;
    std::cout << "Joining 0 & 3." << std::endl;
    ufds.unionSet(0, 3);
    ufds.unionSet(1, 7);
    ufds.unionSet(7, 8);
    std::cout << "Now 0, & 3 are " << (ufds.isSameSet(0, 3)?"same":"disjoint") << " sets." << std::endl;
    std::cout << "Number of disjoint sets " << ufds.numDisjointSets() << std::endl;
    std::cout << "Size of set containing 3 is " << ufds.sizeOfSet(3) << std::endl;
    std::cout << "Size of set containing 0 is " << ufds.sizeOfSet(0) << std::endl;
    std::cout << "Size of set containing 8 is " << ufds.sizeOfSet(8) << std::endl;
    return 0;
}
