/*
 * Abridged Problem Description:
 * Let (x, y) be the coordinates of a student’s house on a 2D plane. There are 2N students
 * and we want to pair them into N groups. Let di be the distance between the houses
 * of 2 students in group i. Form N groups such that cost =
 * N
 * i=1 di is minimized.
 * Output the minimum cost. Constraints: 1 ≤ N ≤ 8 and 0 ≤ x, y ≤ 1000.
 * Sample input:
 * N = 2; Coordinates of the 2N = 4 houses are {1, 1}, {8, 6}, {6, 8}, and {1, 3}.
 * Sample output:
 * cost = 4.83.
 * Can you solve this problem?
 * If so, how many minutes would you likely require to complete the working code?
 * Think and try not to flip this page immediately!
 */
#include<iostream>
#include<set>
#include<cmath>

bool debug = false;

typedef std::pair<int, int> pii;
typedef std::set<pii> sii;

std::string recursionPrefix(int n)
{
    std::string str ;
    for(int i = 1 ; i < n; i++)
        str += " ";

    return str;
}

float distance(const pii a, const pii b)
{
    /*
    if(debug)
        std::cout << "{" << a.first << "," << a.second << "} , {"
            << b.first << "," << b.second << "}" << std::endl;
            */

    int xDist = a.first - b.first;
    int yDist = a.second - b.second;
    return std::sqrt(xDist * xDist + yDist*yDist);
}

float min(sii &pset, int n)
{
    static int level = 0;

    level++;

    if(debug)
        std::cout << recursionPrefix(level) << "Set size is " << n << std::endl;

    if(pset.size() == 2) {
        level--;
        return distance(*(pset.begin()), *(pset.rbegin()));
    }

    float m = std::numeric_limits<float>::max();
    for(sii::iterator i = pset.begin(); i != pset.end(); i++) {
        for(sii::iterator j = std::next(i); j != pset.end(); j++) {
            if(j == i)
                continue;
            pii a = *i;
            pii b = *j;
            if(debug)
                std::cout << recursionPrefix(level) << "{" << a.first << ", " << a.second << "}, {"
                    << b.first << ", " << b.second << "}" << std::endl;
            float curDistance = distance(a, b);

            sii newSet = pset;
            newSet.erase(*i);
            newSet.erase(*j);
            float curMin = min(newSet, newSet.size());
            if((curMin+curDistance) < m)
                m = curMin+curDistance;
        }
    }
    level--;
    return m;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        debug = true;

    int T;
    std::cin >> T;
    while(T-- > 0) {
        int n;
        std::cin >> n;

        sii pointSet;

        for(int i = 0 ; i < n ; i++) {
            int x, y;
            std::cin >> x >> y;

            if(debug)
                std::cout << "x = " << x << ", y=" << y << std::endl;
            pointSet.insert(pii(x, y));
        }
        std::cout << min(pointSet, n) << std::endl;
    }
    return 0;
}
