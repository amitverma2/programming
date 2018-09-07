/*
 * Given a sequence of N numbers – A[1] , A[2] , …, A[N] . Find the length of the longest non-decreasing sequence.
 * https://www.topcoder.com/community/data-science/data-science-tutorials/dynamic-programming-from-novice-to-advanced/
 *
 */
#include<iostream>
#include<vector>

bool debug = false;

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);

    if(argc > 1) debug = true;

    int T;
    std::cin >> T;

    while(T-- > 0) {
        int N;
        std::cin >> N;

        std::vector<int> ints(N);
        std::vector<int> dp(N);

        for(int i = 0 ; i < N; i++)
            std::cin >> ints[i];

        dp[0] = 1;
        int max = dp[0];
        for(int i = 1 ; i < N; i++) {
            if(ints[i] > ints[i-1]) {
                dp[i] = dp[i-1] + 1;
            } else
                dp[i] = 1;
            if(dp[i] > max)
                max = dp[i];
        }
        std::cout << max << std::endl;
    }
    return 0;
}
