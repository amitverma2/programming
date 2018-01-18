/*
 * simple game on N positions.
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

bool isWinning(int n)
{
  if(n == 1) return true;
  if(n == 3) return true;
  if(n == 4) return true;

  if(n - 1 > 0)
    if(!isWinning(n-1))
      return true;

  if(n - 3 > 0)
    if(!isWinning(n-3))
      return true;

  if(n - 4 > 0)
    if(!isWinning(n-4))
      return true;

  return false;
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
