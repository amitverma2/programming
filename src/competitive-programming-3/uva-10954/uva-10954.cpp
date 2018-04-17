/*
 * Yup!! The problem name reflects your task; just add a set of numbers. But you may feel yourselves
condescended, to write a C/C++ program just to add a set of numbers. Such a problem will simply
question your erudition. So, lets add some flavor of ingenuity to it.
Addition operation requires cost now, and the cost is the summation of those two to be added. So,
to add 1 and 10, you need a cost of 11. If you want to add 1, 2 and 3. There are several ways
1 + 2 = 3, cost = 3 1 + 3 = 4, cost = 4 2 + 3 = 5, cost = 5
3 + 3 = 6, cost = 6 2 + 4 = 6, cost = 6 1 + 5 = 6, cost = 6
Total = 9 Total = 10 Total = 11
I hope you have understood already your mission, to add a set of integers so that the cost is minimal.
Input
Each test case will start with a positive number, N (2 ≤ N ≤ 5000) followed by N positive integers
(all are less than 100000). Input is terminated by a case where the value of N is zero. This case should
not be processed.
Output
For each case print the minimum total cost of addition in a single line.
Sample Input
3
1 2 3
4
1 2 3 4
0
Sample Output
9
19
*/
#include<iostream>
#include<queue>
#include<functional>

bool debug = false;

int main(int argc, char * argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    int N;
    while(std::cin >> N, N) {
        long long int cost = 0;
        long long int sum = 0;
        std::priority_queue<int, std::vector<int>, std::greater<int> > myQ;
        for(int n = 0; n < N; n++) {
            int i;
            std::cin >> i;
            myQ.push(i);
        }
        int i1, i2;
        i1 = myQ.top(); myQ.pop();
        if(debug) std::cout << "First " << i1 << std::endl;
        i2 = myQ.top(); myQ.pop();
        if(debug) std::cout << "Second " << i2 << std::endl;
        sum = cost = i1+i2;
        if(debug) std::cout << "First sum " << sum << " first cost " << cost << std::endl;
        myQ.push(sum);
        while(myQ.size() != 1) {
            int i1 = myQ.top(); myQ.pop();
            int i2 = myQ.top(); myQ.pop();
            sum = i1 + i2;
            cost += sum;
            myQ.push(sum);
            if(debug) std::cout << " i1 " << i1 << " i2 " << i2  << " Sum " << sum << " cost " << cost << " size " << myQ.size() << std::endl;
        }
        std::cout << cost << std::endl;
    }
    return 0;
}
