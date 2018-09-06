/*
 * Given a list of N coins, their values (V1, V2, … , VN), and the total sum S.
 * Find the minimum number of coins the sum of which is S (we can use as many
 * coins of one type as we want), or report that it’s not possible to select
 * coins in such a way that they sum up to S.
 */
#include<iostream>
#include<vector>

bool debug = false;

#define MAXS 100000

int dp[MAXS];

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    // we don't need to init as the loop itself will init
    //memset(dp, -1, sizeof(dp));

    int S;
    std::cin >> S;
    int N;
    std::cin >> N;
    std::vector<int> V(N);
    for(int i = 0; i < N; i++)
        std::cin >> V[i];

    if(debug) {
        std::cout << "S " << S << " N " << N << std::endl;
        for(int i = 0 ; i < N; i++)
            std::cout << V[i] << ' ';
        std::cout << std::endl;
    }

    for(int s = 0; s <= S; s++) {
        int bestS = -1;
        for(int c = 0; c < N; c++) {
            if(s - V[c] < 0) {
                continue;
            } else if(s - V[c] > 0) {
                if(dp[s-V[c]] != -1)
                    bestS = dp[s-V[c]] + 1;
            } else if(s - V[c] == 0) {
                bestS = 1;
            }
        }
        dp[s] = bestS;
        if(debug) {
            std::cout << "dp[" << s << "] = " << bestS << std::endl;
        }
    }

    std::cout << "Min coins : " << dp[S] << std::endl;
    return 0;
}
