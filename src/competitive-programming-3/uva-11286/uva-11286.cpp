/*
 * Frosh commencing their studies
 * at Waterloo have diverse
 * interests, as evidenced by
 * their desire to take various
 * combinations of courses
 * from among those available.
 * University administrators
 * are uncomfortable with this
 * situation, and therefore wish
 * to offer a conformity prize
 * to frosh who choose the
 * most popular combination of
 * courses. How many frosh
 * will win the prize?
 * Input
 * The input consists of several test cases followed by a line containing ‘0’.
 * Each test case begins with an integer 1 ≤ n ≤ 10000, the number of frosh.
 * For each frosh, a line follows containing the course numbers of five
 * distinct courses selected by the frosh. Each course number is an integer
 * between 100 and 499.
 * The popularity of a combination is the number of frosh selecting exactly the
 * same combination of courses. A combination of courses is considered most
 * popular if no other combination has higher popularity.
 * Output
 * For each line of input, you should output a single line giving the total
 * number of students taking some combination of courses that is most popular.
 * Sample Input
 * 3
 * 100 101 102 103 488
 * 100 200 300 101 102
 * 103 102 101 488 100
 * 3
 * 200 202 204 206 208
 * 123 234 345 456 321
 * 100 200 300 400 444
 * 0
 * Sample Output
 * 2
 * 3
 */
#include<iostream>
#include<algorithm>
#include<map>

int main()
{
    int N;

    std::ios_base::sync_with_stdio(false);
    while(std::cin >> N, N) {
        std::map<std::string, int> courseMap;
        int maxFrosh = 0;
        while(N--) {
            std::string score[5];
            std::cin >> score[0] >> score[1] >> score[2] >> score[3] >> score[4];
            sort(score, score+5);
            std::string key = score[0] + score[1] + score[2] + score[3] + score[4];
            courseMap[key]++;
            if(courseMap[key] > maxFrosh)
                maxFrosh = courseMap[key];
        }
        int total = 0;
        for(std::map<std::string, int>::const_iterator i = courseMap.begin();
            i != courseMap.end(); i++)
            if(i->second == maxFrosh) total += maxFrosh;
        std::cout << total << '\n';
    }
    return 0;
}
