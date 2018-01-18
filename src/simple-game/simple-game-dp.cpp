/*
 * simple game on N positions using dp.
 *  
 * topcoder simple algorithm games
 * community data science tutorial algorithm games
 *
 * Input
 * T          << Number of testcases
 * N1
 * N2
 * ...
 * Nt         << T testcases in all
 */
#include <iostream>

bool verbose = false;

#define MAX_POSITIONS 1000
bool dp[MAX_POSITIONS+1];

bool isWinning(int n)
{
  dp[1] = dp[3] = dp[4] = true;
  dp[2] = false;

  if(n < 5) return dp[n];

  for(int i = 5 ; i <= n; i++) {
    if(dp[i-1] && dp[i-3] && dp[i-4])
      dp[i] = false;
    else
      dp[i] = true;
  }

  return dp[n];
}

int main(int argc, char *argv[])
{
  if(argc > 1) verbose = true;

  int T;
  std::cin >> T;

  while(T--) {
    int N;
    std::cin >> N;

    std::cout << "For " << N << " position game, player 1 will "
      << (isWinning(N)?"Win!":"Lose.") << std::endl;
  }

  return 0;
}
