/*
 * Problem Statement
 * 
 * Julianne invited her two friends Michael and Jane to a cake party. When
 * Michael and Jane arrived, they saw that their host had prepared several
 * tables. On each table there was a plate with one of the cakes. Each cake
 * was cut into several pieces.
 *
 * Not knowing where to start, Michael and Jane decided to play the following
 * game: Players take alternating turns. In each turn the player selects one
 * cake, and takes and eats several pieces of the cake. The player must take
 * and eat at least one piece. The player who eats the last piece of the last
 * cake wins.
 *
 * However, the host would be really offended if she had the impression that
 * the guests didn't like some of her cakes. Therefore Michael and Jane agreed
 * on one additional rule: Each time a player selects a cake, he or she may
 * only select one of those cakes that have the most pieces remaining.
 *
 * Michael starts the game and plays optimally. In other words, if there is a
 * strategy that will ensure his win (no matter how Jane plays), he will
 * follow one such strategy. If he finds himself in a position where no
 * strategy can guarantee him winning the game he just makes a valid move.
 * In addition, whenever Michael has more than one move to choose from, he
 * picks the lexicographically smallest one (explained below).
 *
 * You are given a int[] pieces. The i-th element of pieces is the initial
 * number of pieces of the i-th cake. Return Michael's first move as a String
 * formatted as follows: "CAKE C PIECES P", where C is the zero-based index of
 * the cake he should select and P is the number of pieces he should eat. The
 * numbers C and P must not contain unnecessary leading zeroes. In case there
 * are multiple valid answers return the one where the resulting String is
 * lexicographically smallest
 * 
 * Definition
 * 
 * Class:  CakeParty
 * Method: makeMove
 * Parameters: int[]
 * Returns:  String
 * Method signature: String makeMove(int[] pieces)
 * (be sure your method is public)
 * 
 * Notes
 * - Ignore the appetite and eating speed of both players. In other words,
 *   assume that each of them is able to eat all the cakes in a short amount
 *   of time.
 * - When selecting the correct output, standard string comparison rules apply:
 * 
 * The string A is lexicograpically smaller than the string B if and only if
 * (A is a proper prefix of B) or (there is an integer X such that first X-1
 * characters of A and B are equal, and the X-th character of A has a smaller
 * ASCII value than the X-th character of B).
 * - Valid characters ordered by their ASCII values (smallest to largest):
 *   space, digits '0'-'9' in this order, letters 'A'-'Z' in this order.
 * 
 * Constraints
 * -  pieces will contain between 1 and 50 elements, inclusive.
 * -  Each element of pieces will be between 1 and 2,000,000,000, inclusive.
 * 
 * Examples
 * 0)  
 * 
 * {47}
 * Returns: "CAKE 0 PIECES 47"
 * With one cake the game is simple: just take everything.
 * 1)  
 * 
 * {3,3}
 * Returns: "CAKE 0 PIECES 1"
 * Two equally big cakes. This is clearly a losing position for the player to
* move. Thus we return the lexicographically smallest possible move.
 * 2)  
 * 
 * {3,5}
 * Returns: "CAKE 1 PIECES 2"
 * The winning move is to create the position from the previous example.
 * 3)  
* 
* {1,1,1,1,1,1,1,1,1,1,1,1,1,1}
* Returns: "CAKE 0 PIECES 1"
* This is an almost deterministic game. The players can not influence the
* result at all.
* 4)  
* 
* {3,3,112}
* Returns: "CAKE 2 PIECES 110"
* This is a winning position, as we can eat the entire last cake and thus
* create the position from Example 1. However, this is not the only winning
* move, and there is a lexicographically smaller winning move than the one we
* described.
* 5)  
* 
* {3,3,1}
* Returns: "CAKE 0 PIECES 1"
* Note that we can not eat the last cake now, as it is not one of the largest
*  ones.
* 6)  
* 
* {4,7,4,7,4,7,4,7,47,47,47,47}
* Returns: "CAKE 10 PIECES 1"
* 
* 
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

bool verbose = false;

class CakeParty {
    bool isWinning(int pieces[]);
    int lexorder(int a, int b, int posA, int posB);
    std::vector<int> lexorder(int from, int to);
    struct lexcompareClass {
        public:
        bool operator()(int a, int b) {
#if 1
            std::stringstream s1, s2;
            s1 << a;
            s2 << b;
            return s1.str() < s2.str();
#else
            return a < b;
#endif
        }
    } lexcompare;

  public:
    std::string makeMove(int pieces[]);
};

std::vector<int> CakeParty::lexorder(int from, int to)
{
    std::vector<int> myvector;
    for(int i = from; i <= to; ++i)
        myvector.push_back(i);

    std::sort(myvector.begin(), myvector.end(), lexcompare);

    if(verbose) {
        std::cout << "Lex ordered cakes pieces" << std::endl;
        for(std::vector<int>::const_iterator i = myvector.begin();
            i != myvector.end();
            i++) {
            std::cout << *i << ' ';
        }
        std::cout << std::endl;
    }
    return myvector;
}

int CakeParty::lexorder(int a, int b, int posA, int posB)
{
    if(a < b) return -1;
    if(a > b) return +1;

#if 1
    // numbers are same, check their position
    std::stringstream s1, s2;
    s1 << posA;
    s2 << posB;
    /*
     * N at pos 10 > N at pos 2
     */
    if(s1.str() < s2.str()) return +1;
    if(s1.str() > s2.str()) return -1;

    //this would actually never happen
    return 0;
#else
    if(posA < posB) return +1;
    if(posA > posB) return -1;
    return 0;
#endif
}

#define BRUTE_FORCE
bool CakeParty::isWinning(int pieces[])
{
  int i;
  int max = pieces[0];
  int maxI = 0;
  int x = 0;
  for(int i = 0; i < 50; i++) {
    x ^= pieces[i];
    if(lexorder(pieces[i], max, i, maxI) > 0) {
      max = pieces[i]; maxI = i;
    }
  }

  // if we can't make a move, we lose
  if(max == 0)
    return false;

#ifdef BRUTE_FORCE
  // brute force
  std::vector<int> lexpieces = lexorder(1, max);
  for(std::vector<int>::iterator j = lexpieces.begin();
      j != lexpieces.end();
      j++) {
    int p[50] = { 0 };
    for(int i = 0; i < 50; i++)
      p[i] = pieces[i];

    pieces[maxI] -= *j;
    if(!isWinning(pieces))
      return true;

    for(int i = 0; i < 50; i++)
      pieces[i] = p[i];
  }
#else
  if(x == 0)
    return false;
  else {
    return true;
  }
#endif

  return false;
}

std::string CakeParty::makeMove(int pieces[])
{
  int i;
  int max = pieces[0];
  int maxI = 0;
  for(int i = 0; i < 50; i++) {
    if(lexorder(pieces[i], max, i, maxI) > 0) {
      max = pieces[i]; maxI = i;
    }
  }

  if(verbose) {
      std::cout << "Starting with cake " << maxI << std::endl;
  }
  std::vector<int> lexpieces = lexorder(1, max);
  for(std::vector<int>::iterator j = lexpieces.begin();
      j != lexpieces.end();
      j++) {
    int p[50] = { 0 };
    for(int i = 0; i < 50; i++)
      p[i] = pieces[i];

    pieces[maxI] -= *j;
    if(!isWinning(pieces)) {
      std::string move = "CAKE ";
      move += std::to_string(maxI);
      move += " PIECES ";
      move += std::to_string(*j);

      return move;
    }

    for(int i = 0; i < 50; i++)
      pieces[i] = p[i];
  }

  std::string move = "L: CAKE ";
  move += std::to_string(maxI);
  move += " PIECES ";
  move += std::to_string(1);
  return move;
}

int main(int argc, char *argv[])
{
  if(argc > 1) verbose = true;

  int T;
  std::cin >> T;
  while(T--) {
    int N;
    std::cin >> N;

    int pieces[50] = { 0 };
    for(int i = 0 ; i < N; i++) {
      std::cin >> pieces[i];
    }
    
    if(verbose) {
      for(int i = 0 ; i < N; i++) {
        std::cout << pieces[i] << ' ';
      }
      std::cout << std::endl;
    }

    class CakeParty cakeparty;
    std::cout << cakeparty.makeMove(pieces) << std::endl;
  }
  return 0;
}
