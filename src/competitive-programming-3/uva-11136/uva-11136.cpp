/*
 * Each Mal-Wart supermarket has prepared a promotion scheme run by the
following rules:
• A client who wants to participate in the promotion (aka a sucker) must
write down their phone number on the bill of their purchase and put the
bill into a special urn.
• Two bills are selected from the urn at the end of each day: first the
highest bill is selected and then the lowest bill is selected. The client
who paid the largest bill receives a monetary prize equal to the difference
between his bill and the lowest bill of the day.
• Both selected bills are not returned to the urn while all the remaining ones are kept in the urn
for the next day.
• Mal-Wart has many clients such that at the end of each day there are at least two bills in the
urn.
• It is quite obvious why Mal-Wart is doing this: they sell crappy products which break quickly
and irreparably. They give a short-term warranty on their products but in order to obtain a
warranty replacement you need the bill of sale. So if you are gullible enough to participate in the
promotion you will regret it.
Your task is to write a program which takes information about the bills put into the urn and
computes Mal-Wart’s cost of the promotion.
Input
The input contains a number of cases. The first line in each case contains an integer n, 1 ≤ n ≤ 5000,
the number of days of the promotion. Each of the subsequent n lines contains a sequence of non-negative
integers separated by whitespace. The numbers in the (i + 1)-st line of a case give the data for the i-th
day.
The first number in each of these lines, k, 0 ≤ k ≤ 105
, is the number of bills and the subsequent k
numbers are positive integers of the bill amounts. No bill is bigger than 106
. The total number of all
bills is no bigger than 106
.
The case when n = 0 terminates the input and should not be processed.
Output
For each case of input print one number: the total amount paid to the clients by Mal-Wart as the result
of the promotion

Sample Input
5
3 1 2 3
2 1 1
4 10 5 5 1
0
1 2
2
2 1 2
2 1 2
0
Sample Output
19
2

*/
#include<iostream>
#include<set>

bool debug = false;

int main(int argc, char *argv[])
{
    if(argc > 1) debug = true;

    std::ios_base::sync_with_stdio(false);

    int n;
    while(std::cin >> n, n) {
        if(debug) std::cout << "Test case with " << n << " days\n";
        std::multiset<int> billsSet;
        long long int total = 0;
        for(int i = 0; i < n; i++) {
            int k = 0;
            std::cin >> k;
            for(int bills = 0 ; bills < k; bills++) {
                int bill;
                std::cin >> bill;
                billsSet.insert(bill);
            }
            int min = *billsSet.begin(); 
            int max = *--billsSet.end();

            total += (max-min);

            if(debug) std::cout << "Day " << i+1 << ' ' << max << ' ' << min << ' ' << total << std::endl;

            billsSet.erase(billsSet.begin());
            billsSet.erase(--billsSet.end());
        }
        std::cout << total << std::endl;
    }
    return 0;
}
