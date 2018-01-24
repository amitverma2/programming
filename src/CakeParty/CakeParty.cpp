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
    void findMaxes(int pieces[], int n, int& m, int& p, int& nm,
                   int& m2, int& p2, int& nm2);
    int lexsmaller(int a, int b);
    int lexsmallest(int low, int hi);
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
    std::string makeMove(int pieces[], int n);
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

int CakeParty::lexsmaller(int a, int b)
{
    std::stringstream s1, s2;
    s1 << a;
    s2 << b;
    if(s1.str() < s2.str()) return a;
    if(s1.str() > s2.str()) return b;
    return a;
}

int CakeParty::lexsmallest(int low, int hi)
{
    int min = low;
    for(int i = low; i <= hi; i++)
        min = lexsmaller(min, i);
    return min;
}

#undef BRUTE_FORCE
bool CakeParty::isWinning(int pieces[])
{
#ifdef BRUTE_FORCE
  // brute force
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
  return false;
#else
  return false;
#endif
}

void CakeParty::findMaxes(int pieces[], int n, int& m, int& p, int& nm,
                          int& m2, int& p2, int& nm2)
{
    // find largest, position, and counts
    m = -1;
    p = -1;
    nm = -1;
    for(int i = 0 ; i < n; i++) {
        if(pieces[i] > m) {
            m = pieces[i];
            p = i;
            nm = 1;
        } else if(pieces[i] == m) {
            nm++;
            p = lexsmaller(i, p);
        }
    }
    m2 = -1;
    p2 = -1;
    nm2 = -1;
    for(int i = 0 ; i < n; i++) {
        if(pieces[i] != m) {
            if(pieces[i] > m2) {
                m2 = pieces[i];
                p2 = i;
                nm2 = 1;
            } else if(pieces[i] == m2) {
                nm2++;
                p2 = lexsmaller(i, p2);
            }
        }
    }
}

std::string CakeParty::makeMove(int pieces[], int n)
{
#ifdef BRUTE_FORCE
    //brute force
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
#else
  int max;
  int posMax;
  int numMax;
  int max2;
  int posMax2;
  int numMax2;

  findMaxes(pieces, n, max, posMax, numMax, max2, posMax2, numMax2);

  if(verbose) {
      std::cout << "m " << max << " pm " << posMax << " nm " << numMax
          << " m2 " << max2 << " pm2 " << posMax2 << " nm2 " << numMax2
          << std::endl;
  }

  if(n == 1) {
      return std::string("CAKE 0 PIECES ") + std::to_string(max);
  } else if(numMax % 2 == 0) {
      return std::string("L:CAKE ") + std::to_string(posMax) + " PIECES 1";
  } else if(numMax != 1) {
      return std::string("CAKE ") + std::to_string(posMax) + " PIECES 1";
  } else {
      // numMax == 1 here
      if(numMax2 % 2 != 0) {
          return std::string("CAKE ") + std::to_string(posMax) + " PIECES "
              + std::to_string(max-max2);
      } else {
          return std::string("CAKE ") + std::to_string(posMax) + " PIECES "
              + std::to_string(lexsmallest(max-max2+1, max));
      }
  }
  return "!!!No move";
#endif
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
    std::cout << cakeparty.makeMove(pieces, N) << std::endl;
  }
  return 0;
}


/*
 * SOLUTION:
 *
 * https://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm338
 *
 * This problem contained two separate parts. One was plainly in sight, the
 * other slightly hidden. 
 *
 * The obvious part is solving the game. 
 *
 * Playing around with small cases, analyzing the examples, or even writing a
 * brute force solution to compute some winning positions -- these are some
 * of the ways you could discover the optimal strategy. 
 *
 * Once you get the right idea, the game is unbelievably simple: Let P be a
 * position, M the maximal number of pieces of one cake, and let C be the
 * number of cakes that have exactly M pieces left. The position P is winning
 * if and only if C is odd. 
 *
 * To prove this, we need to show two things:
 *
 * From any losing position, all moves lead to a winning position.
 * This is clearly true. The player will eat from exactly one of the maximal
 * cakes, thus their count changes from even to odd.
 * From any winning position, there is a move that leads to a losing position.
 * If we have 3 or more maximal cakes, this is similar to the previous case.
 * The interesting situation is when there is exactly one maximal cake. If
 * this happens, we count the second largest cakes. If their count is odd,
 * reduce the maximal cake to this count of pieces. If their count is even,
 * reduce the maximal cake to a smaller count. (Note that there may be many
 * valid moves here.)
 * Now, after feeling that we solved the problem, we stumble upon the hidden
 * second part: selecting the lexicographically smallest move. 
 *
 * Clearly, we may select the cake and the number of pieces independently:
 * The cake is always the lexicograpically smallest of the maximal cakes.
 * For a losing position the number of pieces is 1.
 * For a winning positition with more than one maximal cake the number of
 * pieces is 1, again.
 * For a winning position with one maximal cake and an odd count of second
 * largest cakes, there is a unique correct number of pieces.
 * Finally, for a winning position with one maximal cake and an even count of
 * second largest cakes, the winning moves correspond to some interval [A,B].
 * Thus all we need is a helper function that will find the lexicograpically
 * smallest integer in [A,B]. This one will do, for example:
 *   int digits(int x) { return (""+x).length(); }
 *
 * String lexSmallest(int min, int max) {
 *  if (digits(min)==digits(max)) return ""+min;
 *  String cand1 = ""+min;
 *  String cand2 = "1"; for (int i=0; i<digits(min); i++) cand2 += "0";
 *  if (cand1.compareTo(cand2) < 0) return cand1;
 *  return cand2;
 * }
 */
