/*
 * Problem
 * There exists a straight line along which cities are built.
 *
 * Each city is given a number starting from 1. So if there are 10 cities, city
 * 1 has a number 1, city 2 has a number 2,... city 10 has a number 10.
 *
 * Different buses (named GBus) operate within different cities, covering all
 * the cities along the way. The cities covered by a GBus are represented as
 * 'first_city_number last_city_number' So, if a GBus covers cities 1 to 10
 * inclusive, the cities covered by it are represented as '1 10'
 *
 * We are given the cities covered by all the GBuses. We need to find out how
 * many GBuses go through a particular city.
 *
 * Input The first line contains the number of test cases (T), after which T
 * cases follow each separated from the next with a blank line.  For each test
 * case, The first line contains the number of GBuses.(N) Second line contains
 * the cities covered by them in the form a1 b1 a2 b2 a3 b3...an bn where GBus1
 * covers cities numbered from a1 to b1, GBus2 covers cities numbered from a2
 * to b2, GBus3 covers cities numbered from a3 to b3, upto N GBuses.  Next line
 * contains the number of cities for which GBus count needs to be determined
 * (P).  The below P lines contain different city numbers.  Output For each
 * test case, output one line containing "Case #Ti:" followed by P numbers
 * corresponding to the number of cities each of those P GBuses goes through. 
 *
 * Limits
 * 1 <= T <= 10 
 * ai and bi will always be integers.
 *
 * Small dataset
 * 1 <= N <= 50 
 * 1 <= ai <= 500, 1 <= bi <= 500 
 * 1 <= P <= 50
 *
 * Large dataset
 * 1 <= N <= 500 
 * 1 <= ai <= 5000, 1 <= bi <= 5000 
 * 1 <= P <= 500
 *
 *
 * Input 
 *      
 *      2
 *      4
 *      15 25 30 35 45 50 10 20
 *      2
 *      15
 *      25
 *
 *      10
 *      10 15 5 12 40 55 1 10 25 35 45 50 20 28 27 35 15 40 4 5
 *      3
 *      5
 *      10
 *      27
 *
 *
 *      Output 
 *       
 *       Case #1: 2 1
 *       Case #2: 3 3 4
 *
 */
#include<iostream>
#include<list>

bool debug = false;

int numBuses(std::list<std::pair<int, int> > &gbuses,
             int city, int N)
{
    int count = 0;
    for(std::list<std::pair<int, int> >::const_iterator i = gbuses.begin();
        i != gbuses.end();
        i++) {
        std::pair<int, int> pii = *i;
        if(city >= pii.first && city <= pii.second)
            count++;
    }

    return count;
}

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    int T;
    std::cin >> T;

    for(int t = 1; t <= T; t++) {
        int N;
        std::cin >> N;

        std::list<std::pair<int, int> > gbuses;
        for(int n = 1; n <= N; n++) {
            int a, b;
            std::cin >> a >> b;

            gbuses.push_front(std::pair<int, int>(a,b));
        }

        std::cout << "Case #" << t << ": "; 

        int P;
        std::cin >> P;

        for(int p = 1; p <= P; p++) {
            int city;
            std::cin >> city;

            std::cout << numBuses(gbuses, city, N);
            if(p != P)
                std::cout << " ";
            else
                std::cout << std::endl;
        }
    }
    return 0;
}
