/*
 * Long Long Nim
 *
 * https://community.topcoder.com/stat?c=problem_statement&pm=6856&rd=10010
 *
 * Problem Statement
 *     	
 * LongLongNim is a game played by two players who alternate turns. n coins
 * are arranged in a pack. A valid move consists of removing exactly X coins
 * from the pack, where X is an element of the set moves. If a player cannot
 * perform a valid move during his turn, he loses the game, and the other
 * player, of course, wins.
 * 
 * You are given the set moves as a int[], and you are also given an int maxN.
 * Return the number of different values of n between 1 and maxN, inclusive,
 * that make the game possible to win for the second player (assuming both
 * players play optimally).
 * 
 * Definition
 *     	
 * Class:	LongLongNim Method:	numberOfWins Parameters:	int, int[]
 * Returns:	int Method signature:	int numberOfWins(int maxN, int[]
 * moves) (be sure your method is public)
 *     
 *  
 * Constraints -	maxN will be between 1 and 1000000000 (109), inclusive.  -
 * moves will contain between 1 and 22 elements, inclusive.  -	Each
 * element of moves will be between 1 and 22, inclusive.  -	moves will
 * be sorted in strictly increasing order (i.e., no duplicates).
 *  
 * Examples 0)	
 *     	
 * 20 {1,2,3} Returns: 5 If n is a multiple of 4, the second player can win by
 * simply removing 4-L coins each time, where L is the number of coins the
 * first player removed on his last turn. If n is not a multiple of four, the
 * first player can always choose to remove the remainder of dividing n by 4,
 * thereby leaving a multiple of 4 and the second player in. After that, he
 * just uses the strategy described at the beginning to win. Altogether, the
 * second player only wins if n is a multiple of 4, and there are 5 multiples
 * of 4 between 1 and 20.  1)	
 *     	
 * 999 {1} Returns: 499 The second player wins when n is even and loses when n
 * is odd.  2)	
 *     	
 * 1000000000 {1,2} Returns: 333333333 Similarly to example 0, the second
 * player only wins when n is a multiple of 3.  3)	
 *     	
 * 6543 {2,4,7,11,20} Returns: 1637 Any player who is left with 0 or 1 coin
 * loses because the least number of coins that can be removed is 2.
 */

