/*
 * A puzzle game
 * https://www.codechef.com/problems/H1
 *
 * Johnny has some difficulty memorizing the small prime numbers. So, his
 * computer science teacher has asked him to play with the following puzzle
 * game frequently.
 *
 * The puzzle is a 3x3 board consisting of numbers from 1 to 9. The
 * objective of the puzzle is to swap the tiles until the following final
 * state is reached:
 *
 * 1 2 3 4 5 6 7 8 9 At each step, Johnny may swap two adjacent tiles if
 * their sum is a prime number. Two tiles are considered adjacent if they
 * have a common edge.
 *
 * Help Johnny to find the shortest number of steps needed to reach the
 * goal state.Input
 *
 * The first line contains t, the number of test cases (about 50). Then t
 * test cases follow. Each test case consists of a 3x3 table describing a
 * puzzle which Johnny would like to solve.
 *
 * The input data for successive test cases is separated by a blank line.
 *
 * Output
 * For each test case print a single line containing the shortest number of
 * steps needed to solve the corresponding puzzle. If there is no way to
 * reach the final state, print the number -1.
 *
 * Example
 * Input:
 * 2
 *
 * 7 3 2 
 * 4 1 5 
 * 6 8 9 
 *
 * 9 8 5 
 * 2 4 1 
 * 3 7 6  
 *
 * Output:
 * 6
 * -1
 *
 */
#include<iostream>
#include<list>
#include<map>
#include<queue>
#include<set>

bool verbose;
bool debug;

class ArrayBFSContainer {
    private:
        std::map<int, int> minStepsMap;
    
        inline void findValidChildren(int n, std::list<int> &children)
        {
            // 0 = 0,0
            // 1 = 0,1
            // 2 = 0,2
            // 3 = 1,0
            // 4 = 1,1
            // 5 = 1,2
            // 6 = 2,0
            // 7 = 2,1
            // 8 = 2,2
            int swapPos[9][4] =
            {
                { -1, 3, 1, -1 },
                { -1, 4, 2, 0 },
                { -1, 5, -1, 1 },
                { 0, 6, 4, -1 },
                { 1, 7, 5, 3 },
                { 2, 8, -1, 4 },
                { 3, -1, 7, -1 },
                { 4, -1, 8, 6 },
                { 5, -1, -1, 7 },
            };
            
            for(int i = 0 ; i < 9; i++) {
                for(int p = 0 ; p < 4; p++) {
                    // 0 = up, 1 = down, 2 = right, 3 = left
                    int j = swapPos[i][p];
                    if(j != -1 && isAValidSwap(i, j, n))
                        children.push_back(makeSwappedPosition(n, i, j));
                }
            }
            return;
        }
    
        inline int putDigitAtPos(int n, int pos, int digit)
        {
            int divisor[9] =
            {
                100000000,
                10000000,
                1000000,
                100000,
                10000,
                1000,
                100,
                10,
                1,
            };
            if(debug)
                std::cout << "Putting " << digit << " in " << n <<
                " at pos " << pos << std::endl;
            
            int upper = (n / (10 * divisor[pos])) * divisor[pos] * 10;
            if(debug)
                std::cout << "Upper " << upper << std::endl;
            int lower = n % divisor[pos];
            if(debug)
                std::cout << "Lower " << lower << std::endl;
            digit *= divisor[pos];
            if(debug)
                std::cout << "digit " << digit << std::endl;
            return upper + digit + lower;
        }
    
        inline bool isAValidSwap(int i, int j, int n)
        {
            bool isPrime[18] =
            {
                0, // 0 is not prime
                1, // 1 is prime
                1, // 2 is prime
                1, // 3 is prime
                0, // 4 is not prime
                1, // 5 is prime
                0, // 6 is not prime
                1, // 7 is prime
                0, // 8 is not prime
                0, // 9 is not prime
                0, // 10 is not prime
                1, // 11 is prime
                0, // 12 is not prime
                1, // 13 is prime
                0, // 14 is not prime
                0, // 15 is not prime
                0, // 16 is not prime
                1, // 17 is prime
            };

            int a = digitAtPos(n, i);
            int b = digitAtPos(n, j);
            if(isPrime[a+b])
                return true;
            else
                return false;
        }
        inline int makeSwappedPosition(int n, int i, int j)
        {
            int a = digitAtPos(n, i);
            int b = digitAtPos(n, j);

            n = putDigitAtPos(n, i, b);
            n = putDigitAtPos(n, j, a);
            if(debug)
                std::cout << "... got " << n << std::endl;
            return n;
        }

        inline int digitAtPos(int n, int p)
        {
            int divisor[9] =
            {
                100000000,
                10000000,
                1000000,
                100000,
                10000,
                1000,
                100,
                10,
                1,
            };
            return (n / divisor[p]) % 10;
        }
    public:
        ArrayBFSContainer(int n);
        int present(int n);
};


ArrayBFSContainer::ArrayBFSContainer(int n)
{
    std::set<int> visited;
    std::queue<std::pair<int, int> > bfsQueue;

    minStepsMap.insert(std::pair<int,int>(n, 0));
    bfsQueue.push(std::pair<int,int>(n, 0));
    visited.insert(n);

    while(!bfsQueue.empty()) {
        std::pair<int, int> i = bfsQueue.front();
        bfsQueue.pop();
        int steps = i.second;
        int position = i.first;
        std::list<int> children;
        findValidChildren(position, children);
        if(verbose)
            std::cout << "From position " << i.first << " at step "
                << i.second << " found " << children.size()
                << " valid children." << std::endl;
        for(std::list<int>::const_iterator c = children.begin();
            c != children.end(); c++) {
            if(visited.find(*c) == visited.end()) {
                if(verbose)
                    std::cout << "... adding child " << *c << " at step "
                        << steps + 1 << std::endl;
                visited.insert(*c);
                minStepsMap.insert(std::pair<int,int>(*c, steps+1));
                bfsQueue.push(std::pair<int,int>(*c, steps+1));
            } else {
                if(verbose)
                    std::cout << "... skipping already visited child " << *c
                        << std::endl;
            }
        }
        if(verbose && steps % 2 == 0)
            std::cout << "After " << steps << " steps. minStepsMap.size() is " << minStepsMap.size()
               << " visited size " << visited.size() << " bfsQueue size if " << bfsQueue.size()
               << std::endl;
    }
    if(verbose)
        std::cout << "BFS done. Total positions found = " <<
            minStepsMap.size() << std::endl;
}

int ArrayBFSContainer::present(int n)
{
    std::map<int, int>::const_iterator i = minStepsMap.find(n);
    if(i == minStepsMap.end())
        return -1;
    else
        return (*i).second;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        verbose = true;
    if(argc > 2)
        debug = true;

    int T;
    //std::cin >> T;
    T = 1;
    
    std::list<int> tests;
    tests.push_back(732415689);
#if 0
    for(int i = 0 ; i < T; i++) {
        // represet array in an integer max int
        // 1 2 3
        // 4 5 6
        // 7 8 9
        // will represent as
        // 123456789
        int t = 0;
        for(int j = 0 ; j < 9; j++) {
            int n;
            std::cin >> n;
            t *= 10;
            t += n % 10; // being cautious
        }
        if(verbose)
            std::cout << "Test " << i + 1 << " is " << t << std::endl;

        tests.push_back(t);
    }
#endif
    if(verbose)
        std::cout << "Total list size is " << tests.size() << std::endl;

    /* start with 123456789 i.e. this matrix
     * 1 2 3
     * 4 5 6
     * 7 8 9
     * and fill up all the reachable positions in the map minStepsMap by
     * doing a BFS
     */
    ArrayBFSContainer bfs(123456789);

    for(std::list<int>::const_iterator i = tests.begin();
        i != tests.end(); i++) {
        std::cout << bfs.present(*i) << std::endl;
    }
    return 0;
}
