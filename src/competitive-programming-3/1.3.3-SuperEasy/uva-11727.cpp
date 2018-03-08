/*
 * 11727 - Cost Cutting
 *
 * https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=2827
 *
 * Company XYZ have been badly hit by recession and is taking a lot of cost
 * cutting measures. Some of these measures include giving up office space,
 * going open source, reducing incentives, cutting on luxuries and issuing pink
 * slips.  They have got three (3) employees working in the accounts department
 * and are going to lay-off two (2) of them. After a series of meetings, they
 * have decided to dislodge the person who gets the most salary and the one who
 * gets the least. This is usually the general trend during crisis like this.
 * You will be given the salaries of these 3 employees working in the accounts
 * department. You have to find out the salary of the person who survives.
 * Input The first line of input is an integer T (T < 20) that indicates the
 * number of test cases. Each case consists of a line with 3 distinct positive
 * integers. These 3 integers represent the salaries of the three employees.
 * All these integers will be in the range [1000, 10000].  Output For each
 * case, output the case number followed by the salary of the person who
 * survives.
 *
 * Sample Input
 * 3
 * 1000 2000 3000
 * 3000 2500 1500
 * 1500 1200 1800
 * Sample Output
 * Case 1: 2000
 * Case 2: 2500
 * Case 3: 1500
 */
#include<iostream>
#include<algorithm>
#include<vector>

int main()
{
    int T;
    std::cin >> T;

    for(int i = 1; i <= T; i++) {
        std::vector<int> emp(3);
        std::cin >> emp[0] >> emp[1] >> emp[2];

        std::cout << "Case " << i << ": ";

        sort(emp.begin(), emp.end());

        std::cout << emp[1] << std::endl;
    }
    return 0;
}
