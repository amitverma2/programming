/*
 * Jack and Jill have decided to sell
some of their Compact Discs, while
they still have some value. They
have decided to sell one of each of
the CD titles that they both own.
How many CDs can Jack and Jill
sell?
Neither Jack nor Jill owns more
than one copy of each CD.
Input
The input consists of a sequence of
test cases. The first line of each
test case contains two non-negative
integers N and M, each at most
one million, specifying the number
of CDs owned by Jack and by Jill, respectively. This line is followed by N lines listing the catalog
numbers of the CDs owned by Jack in increasing order, and M more lines listing the catalog numbers
of the CDs owned by Jill in increasing order. Each catalog number is a positive integer no greater than
one billion. The input is terminated by a line containing two zeros. This last line is not a test case and
should not be processed.
Output
For each test case, output a line containing one integer, the number of CDs that Jack and Jill both
own.
Sample Input
3 3
1
2
3
1
2
4
0 0
Sample Output
2
*/

#include<iostream>
#include<set>

bool debug = false;

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    std::ios_base::sync_with_stdio(false);

    int N, M;
    while(std::cin >> N >> M, (N || M)) {
        std::set<int> catalogJack;
        for(int n = 0; n < N; n++) {
            int cd;
            std::cin >> cd;
            //catalogJack.insert(catalogJack.end(), cd); // we know the input is sorted in ascending order, took 0.4 seconds on UVA to run
            catalogJack.insert(cd); // took 0.790 seconds on uva to run
        }
        int common = 0;
        std::set<int>::const_iterator ci = catalogJack.begin();
        for(int m = 0; m < M; m++) {

            int cd;
            std::cin >> cd;

            while(ci != catalogJack.end()) {
                if(*ci < cd) {
                    ci++;
                    continue;
                } else if(*ci == cd) {
                    if(debug) std::cout << "Common cd " << cd << std::endl;
                    common++;
                    ci++;
                    break;
                } else
                    break;
            }
        }
        std::cout << common << std::endl;
    }
    return 0;
}
