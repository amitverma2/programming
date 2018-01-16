/*
 * Kris Elly Game Candy game
 *
 * http://www.programering.com/a/MTNzYTNwATE.html
 *
 * Elly and Kris play the following game. In the beginning there are several
 * boxes aligned in a row. The boxes may or may not contain candy. As a matter
 * of fact, the girls know exactly how many candies each of them contains.
 * This information is given to you in the vector <int> sweets.
 *
 * Starting with Elly, the girls make moves in alternating order. A single
 * move looks as follows: the player whose turn it is chooses one of the
 * non-empty boxes and takes all the sweets from it. After that the amount of
 * candy in the neighboring boxes is doubled. For example, suppose that there
 * were five boxes with {20, 50, 70, 0, 30} sweets, respectively. If the girl
 * whose turn it was chose box 0, then in the next turn the number of sweets
 * in the boxes would be {0, 100, 70, 0, 30}. If she chose box 1, then it
 * would be {40, 0, 140, 0, 30}. If she chose box 2, it would be
 * {20, 100, 0, 0, 30}. If she chose box 4, it would be {20, 50, 70, 0, 0}.
 * Note that the girl cannot choose box 3, because it is empty.  The game
 * ends when all boxes are empty. The winner of the game is the girl who has
 * more candies at the end of the game.
 *
 * Return the name of the girl that will win the game if both girls play
 * optimally, or "Draw" if they end up with the same number of candies.
 *
 * Class:	EllysCandyGame
 * Method:	getWinner
 * Parameters:	vector <int>
 * Returns:	string
 * Method signature:	string getWinner(vector <int> sweets)
 * (be sure your method is public)
 *
 * Limits
 * Time limit (s):	2.000
 * Memory limit (MB):	256
 *
 * Notes:
 * - Playing optimally means that if there is a move, which guarantees that the
 * girl whose turn it is will win no matter what the other girl does, she will
 * play it. If there is no such move, but there is one, which would guarantee
 * a draw, she will use it instead.
 * - The game always ends after a finite number of moves, because the number
 *   of empty boxes increases in each step.
 *
 * Constraints
 * sweets will contain between 1 and 10 elements, inclusive
 * ach element of sweets will be between 0 and 1000, inclusive.
 *
 * Examples
 * {20, 50, 70, 0, 30}
 * Returns: "Kris"
 * If Elly takes the 20, then Kris can take the 30, leaving Elly the choice
 * between 100 and 70. Elly should take the 100, but then Kris will take 140
 * and win.
 * If Elly takes the 30, then Kris can take the 20, leaving Elly the same choice.
 * If Elly takes the 50, then Kris can take the 140, leaving Elly the choice
 * between a 40 and a 30.
 * If Elly takes the 70, then Kris can take the 100, leaving Elly the same
 * choice.
 * In any case, Kris will take more than Elly and win.
 *
 * {42, 13, 7}
 * Returns: "Elly"
 * Here Elly can take the 42 in her first move and win, no matter whether Kris
 * chooses the 26 or 7
 *
 * {10, 20}
 * Returns: "Draw"
 * Elly cannot win, but she can force a draw by taking the 20 (and leaving
 * 20 to her opponent)
 *
 *
 * {3, 1, 7, 11, 1, 1}
 * Returns: "Kris"
 *
 * {41, 449, 328, 474, 150, 501, 467, 329, 536, 440}
 * Returns: "Kris"
 *
 * {177, 131, 142, 171, 411, 391, 17, 222, 100, 298}
 * Returns: "Elly"
 *
 * Input
 * T                << Number of test cases
 * N1               << Number of boxes for test 1
 * C1 C2 ... CN1    << Candies in each box
 * N2               << NUmber of boxes for test 2
 * CI CII ... CN2   << Candies in each box
 */

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

bool verbose = false;

class Game {
    int N;
    enum Player { Elly, Kris, Draw };

    public:
    Game(int _N):N(_N) { }
    std::string getWinner(std::vector<int> &sweets);

    private:
    Player play(Player player, std::vector<int> &sweets, int kris, int elly);
    std::string prefix(int n);
};

std::string Game::prefix(int n)
{
  std::string spacer;
  int N = n;

  while(n-- > 0) {
    spacer += std::to_string(N);
  }
  spacer += " ";

  return spacer;
}

Game::Player Game::play(Player player, std::vector<int> &sweets, int kris, int elly)
{
  static int nest = 0;
  nest++;

  if(verbose) {
    std::cout << prefix(nest) << ((player == Elly)?"Elly's":"Kris's") << " turn. Elly at " << elly << " Kris at " << kris << " sweets @ [ ";
    for(std::vector<int>::const_iterator i = sweets.begin(); i != sweets.end(); i++)
      std::cout << *i << ' ';
    std::cout << "]" << std::endl;
  }

  int sum;
  sum = std::accumulate(sweets.begin(), sweets.end(), 0);

  if(sum == 0) {
    if(elly > kris) {
    if(verbose)
	    std::cout << prefix(nest) << "Elly is the winner. Elly " << elly << " Kris " << kris << std::endl;
      nest--;
      return Elly;
    } else if(kris > elly) {
    if(verbose)
	    std::cout << prefix(nest) << "Kris is the winner. Elly " << elly << " Kris " << kris << std::endl;
      nest--;
      return Kris;
    } else {
    if(verbose)
	    std::cout << prefix(nest) << "We have a draw. Elly " << elly << " Kris " << kris << std::endl;
      nest--;
      return Draw;
    }
  }
  
  bool draw_possible = false;
  std::vector<int> dup = sweets;
  for(std::vector<int>::iterator i = sweets.begin(); i != sweets.end(); i++) {
    if(*i != 0) {
      int elly_2 = elly;
      int kris_2 = kris;

      if(player == Elly) {
        elly_2 += *i;
        if(verbose)
          std::cout << prefix(nest) << "Elly took " << *i << " sweets." << std::endl;
      }
      else if(player == Kris) {
        kris_2 += *i;
        if(verbose)
          std::cout << prefix(nest) << "Kris took " << *i << " sweets." << std::endl;
      }


      *i = 0;
      if(i != sweets.begin()) *(i-1) *= 2;
      if(i != sweets.end()) *(i+1) *= 2;

      Player p = play((player == Elly)?Kris:Elly, sweets, kris_2, elly_2);

      if(p == player) {
        if(verbose) std::cout << prefix(nest) << "Winner is " << ((player == Elly)?"Elly":"Kris") << std::endl;
        nest--;
        return p;
      }
      else if(p == Draw) draw_possible = true;

      sweets = dup;
    }
  }

  if(draw_possible) {
    if(verbose) std::cout << prefix(nest) << "Draw possible." << std::endl;
    nest--;
    return Draw;
  }

  if(verbose) std::cout << prefix(nest) << "Returning winner as other player. " << ((player == Elly)?"Kris":"Elly") << std::endl;
  nest--;
  return (player == Elly)?Kris:Elly;
}

std::string Game::getWinner(std::vector<int> &sweets)
{
    if(verbose)
        std::cout << " **** Playing game with " << N << " boxes ****" << std::endl;

    Player winner = play(Elly, sweets, 0, 0);

    if(winner == Elly) return "Elly";
    else if(winner == Kris) return "Kris";
    else return "Draw";
}

int main(int argc, char *argv[])
{
    if(argc > 1)
        verbose = true;

    int T;
    std::cin >> T;
    for(int i = 1; i <= T; i++) {
        int N;
        std::cin >> N;

        Game game(N);
        std::vector<int> sweets(N);

        for(std::vector<int>::iterator i = sweets.begin(); N--; i++)
            std::cin >> *i;

        if(verbose) {
            std::cout << "Test case " << i << " Boxes are : " << std::endl;
            for(std::vector<int>::iterator i = sweets.begin(); i != sweets.end();
                i++)
                std::cout << *i << ' ';
            std::cout << std::endl;
        }

        std::cout << game.getWinner(sweets) << std::endl;
    }

    return 0;
}
