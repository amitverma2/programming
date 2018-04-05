/*
 * Emily the entrepreneur has a cool business idea: packaging and selling
 * snowflakes. She has devised a machine that captures snowflakes as they fall,
 * and serializes them into a stream of snowflakes that flow, one by one, into
 * a package. Once the package is full, it is closed and shipped to be sold.
 * The marketing motto for the company is “bags of uniqueness.” To live up to
 * the motto, every snowflake in a package must be different from the others.
 * Unfortunately, this is easier said than done, because in reality, many of
 * the snowflakes flowing through the machine are identical. Emily would like
 * to know the size of the largest possible package of unique snowflakes that
 * can be created. The machine can start filling the package at any time, but
 * once it starts, all snowflakes flowing from the machine must go into the
 * package until the package is completed and sealed. The package can be
 * completed and sealed before all of the snowflakes have flowed out of the
 * machine.
 * Input
 * The first line of input contains one integer specifying the number of test
 * cases to follow. Each test case begins with a line containing an integer n,
 * the number of snowflakes processed by the machine.  The following n lines
 * each contain an integer (in the range 0 to 10^9 , inclusive) uniquely
 * identifying a snowflake. Two snowflakes are identified by the same integer
 * if and only if they are identical.  The input will contain no more than one
 * million total snowflakes.
 * Output
 * For each test case output a line containing single integer, the maximum
 * number of unique snowflakes that can be in a package.
 * Sample Input
 * 1
 * 5
 * 1
 * 2
 * 3
 * 2
 * 1
 * Sample Output
 * 3
 */
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

bool debug = false;

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    std::ios_base::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while(T--) {
        int N;
        std::cin >> N;

        std::vector<int> snowflakes;
        snowflakes.reserve(1 * 1000 * 1000 + 100);
        int num = N;
        snowflakes.push_back(-1);
        while(num--) {
            int s;
            snowflakes.push_back((std::cin >> s, s));
        }
        if(debug) {
            std::cout << "Total snowflakes : " << snowflakes.size() << std::endl;
            for(int i = 1 ; i <= std::min(10, N); i++)
                std::cout << snowflakes[i] << std::endl;
        }
        int max = 0;
        for(int i = 1 ; i <= N; ) {
            int curMax = 1;
            std::map<int, int> present;
            present[snowflakes[i]] = i;
            if(curMax > max) max = curMax;
            if(max >= (N-i)) break; // we can't have better max
            if(debug) std::cout << "max" << max << " starting at " << i << std::endl;
            bool broken = false;
            int brokenAt = 0;
            for(int j = i+1; j <= N; j++) {
                if(present[snowflakes[j]] != 0) {
                    // if(debug) std::cout << "Found " << snowflakes[j] << " in the present map" << std::endl;
                    broken = true;
                    brokenAt = present[snowflakes[j]];
                    break;
                } else {
                    // if(debug) std::cout << "Not Found " << snowflakes[j] << " in the present map" << std::endl;
                    present[snowflakes[j]] = j;
                    curMax++;
                }
            }
            if(curMax > max) max = curMax;
            if(!broken)
                i++;
            else 
                i = brokenAt + 1;
        }
        std::cout << max << std::endl;
    }
    return 0;
}
