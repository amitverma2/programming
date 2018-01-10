#include <iostream>

using namespace std;
/*
https://community.topcoder.com/stat?c=problem_statement&pm=7756

Alan and Bob are playing a game with two piles of sticks. The two players alternate turns, and Alan gets the first turn.
During each turn, the player must remove exactly n^2 sticks from each pile, where n is some positive integer.
The value of n does not have to be the same for each pile.
For example, he can remove 1^2 = 1 stick from the first pile and 3^2 = 9 sticks from the second pile.
The first player who cannot make a valid move is declared the loser.

The first pile initially contains size0 sticks and the second pile contains size1 sticks.
Suppose both players play optimally. One of them has a winning strategy (no matter how his opponent plays he can always win)
and he wants to win as fast as possible. The other player wants to lose as slowly as possible.

Return a String formatted as "<WINNER> will win after <NUMBER> moves" (quotes for clarity),
where <WINNER> is the name of the winner and <NUMBER> is the total number of turns in the game.
The total number of turns is the sum of all the successful turns taken by Alan and Bob.

Definition

Class:	PowerGame
Method:	winner
Parameters:	int, int
Returns:	String
Method signature:	String winner(int size0, int size1)
(be sure your method is public)


Constraints
-	size0 and size1 will each be between 1 and 10000, inclusive.

INPUT:
8
4
9
4
3
2
3
7
13
2136
1244
9563
8914
9456
8754
6642
6642

*/

int findsqroot(int num)
{
	int count = 0;
	int x = 1;

	for (int i = 3; x <= num; i += 2)
	{
		x = x + i;
		count++;
	}
	return count;
}

#define MAX_INT 0x7fffffff
#define MIN_INT 0x80000000
#define MAX 10001

int pile1, pile2;
int dp[MAX];

char* str[2] = { "Bob", "Alan" };

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

#define even(pos) ((pos%2==0) ? true: false)


int countutil(int pile)
{
	// find the nearest sqaure to this
	int nsqroot = findsqroot(pile);

	// one would loose since he cannot make the move
	dp[0] = 0;

	for (int i = 1; i <= pile; i++)
	{
		int min_even = MAX_INT;
		int max_odd = MIN_INT;

		for (int j = 1; j <= nsqroot; j++)
		{
			// if i is greater than or equal to j,
			// which means 1-j moves are possible
			int sqr = j*j;
			if (i < sqr)
				break;

			int pos = i - sqr;
			if (even(dp[pos]))
			{
				if (min_even > dp[pos])
					min_even = dp[pos];
			}
			else
			{
				if (max_odd < dp[pos])
					max_odd = dp[pos];
			}
		}

		if (min_even != MAX_INT)
			dp[i] = 1 + min_even;
		else
			dp[i] = 1 + max_odd;
	}
	return dp[pile];
}


int findturns()
{
	// we can play both the sticks independently
	// and find the minimum between two moves
	int val1 = countutil(pile1);
	int val2 = countutil(pile2);

	return min(val1, val2);
}


int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	// one of those rare occassion, where same DP array would help
	// in all the cases.
	for (int i = 0; i < 10001; i++)
	{
		dp[i] = -1;
	}

	for (int count = 1; count <= T; count++)
	{
		cin >> pile1 >> pile2;

		int answer = findturns();

		cout << "#" << count << " " << "Winner is: " << str[answer % 2] << ", no of turns: " << answer << endl;

	}
	return 0;
}

++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int findsqroot(int num)
{
	int count = 0;
	int x = 1;

	for (int i = 3; x <= num; i += 2)
	{
		x = x + i;
		count++;
	}
	return count;
}

#define MAX_INT 0x7fffffff
#define MIN_INT 0x80000000
#define MAX 10001

int pile1, pile2;
int dp[MAX];

char* str[2] = { "Bob", "Alan" };

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)


int countutil(int pile)
{
	int &res = dp[pile];

	if (res != -1)
		return res;

	// find the nearest sqaure to this
	int nsqroot = findsqroot(pile);

	// this is a perfect square, hence the player can end the game now
	if (pile == nsqroot*nsqroot)
		return 1;
	
	int min_even = MAX_INT;
	int max_odd = MIN_INT;
	int value;

	// going from 1 to nsqroot results in stack overflow
	// going from nsqroot to 1 would help get to base cases soon
	for (int i = nsqroot; i >= 1; i--)
	{
		value = countutil(pile - i*i);

		if (value % 2 == 0)
		{
			// player is winning the game, hence to see the minimum move
			if (min_even > value)
				min_even = value;
		}
		else
		{
			// player can't win in this case, hence take the maximum move
			if (max_odd < value)
				max_odd = value;
		}
	}


	if (min_even != MAX_INT)
		// player would win here
		return res = 1 + min_even;
	else
		// player would loose here
		return res = 1 + max_odd;
}


int findturns()
{
	// we can play both the sticks independently
	// and find the minimum between two moves
	int val1 = countutil(pile1);
	int val2 = countutil(pile2);

	return min(val1, val2);
}


int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	// one of those rare occassion, where same DP array would help
	// in all the cases.
	for (int i = 0; i < 10001; i++)
	{
		dp[i] = -1;
	}

	for (int count = 1; count <= T; count++)
	{
		cin >> pile1 >> pile2;

		int answer = findturns();

		cout << "#" << count << " " << "Winner is: " << str[answer % 2] << ", no of turns: " << answer << endl;

	}
	return 0;
}