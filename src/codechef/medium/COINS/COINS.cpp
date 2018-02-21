/*
 * Bytelandian gold coins Problem Code: COINS
 * https://www.codechef.com/problems/COINS
 *
 * In Byteland they have a very strange monetary system.

Each Bytelandian gold coin has an integer number written on it. A coin n can be
exchanged in a bank into three coins: n/2, n/3 and n/4. But these numbers are
all rounded down (the banks have to make a profit).

You can also sell Bytelandian coins for American dollars. The exchange rate is
1:1. But you can not buy Bytelandian coins.

You have one gold coin. What is the maximum amount of American dollars you can
get for it?

Input The input will contain several test cases (not more than 10). Each
testcase is a single line with a number n, 0 <= n <= 1 000 000 000. It is the
number written on your coin.

Output For each test case output a single line, containing the maximum amount
of American dollars you can make.

Example Input: 12 2

Output: 13 2 You can change 12 into 6, 4 and 3, and then change these into
$6+$4+$3 = $13. If you try changing the coin 2 into 3 smaller coins, you will
get 1, 0 and 0, and later you can get no more than $1 out of them. It is better
just to change the 2 coin directly into $2.
*/

#include<iostream>

unsigned long int *dp;

unsigned long int maxConvertDollar(unsigned long int bCoin)
{
    if(bCoin == 0)
        return 0;

    if(dp[bCoin] != 0)
        return dp[bCoin];

    unsigned long int ifBroken = maxConvertDollar(bCoin/2) + maxConvertDollar(bCoin/3) + maxConvertDollar(bCoin/4);

    dp[bCoin] = (ifBroken > bCoin) ? ifBroken:bCoin;

    return dp[bCoin];
}

int main(int argc, char *argv[])
{
    dp = new unsigned long int[1000000001];
    if(!dp)
        return 0;

    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 4;
    while(1) {
        unsigned long int bCoin;
        std::cin >> bCoin;
        if(std::cin.eof())
            break;

        std::cout << maxConvertDollar(bCoin) << std::endl;
    }
    delete[] dp;
    return 0;
}
