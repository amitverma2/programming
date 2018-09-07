/*
 * Problem Statement
 * You and a friend are playing a game in which you take turns removing stones
 * from piles. Initially, every pile has at least as many stones as the pile to
 * its left. This property must be maintained throughout the game. On each
 * turn, you remove one or more stones from a single pile. You and your friend
 * alternate turns until it is no longer possible to make a valid move. The
 * last player to have made a move wins the game. Note that if you remove all
 * the stones from a pile, it is still considered a pile.
 * 
 * You are said to have made a "winning move" if after making that move, you
 * can eventually win no matter what your friend does. You are given a int[]
 * piles representing the number of stones in each pile from left to right. It
 * is your turn to move. Find a winning move and return it as a String
 * formatted as "TAKE s STONES FROM PILE k" (quotes for clarity only), where s
 * and k (a 0-based index) are each integers with no leading zeros. If there
 * are multiple winning moves, choose the one that minimizes s. If there is
 * still a tie, choose the one that minimizes k. If no winning move is
 * possible, return the String "YOU LOSE" (quotes for clarity only).
 *
 * Definition
 * Class:	StoneGameStrategist
 * Method:	play
 * Parameters:	int[]
 * Returns:	String
 * Method signature:	String play(int[] piles)
 * (be sure your method is public)
 *
 * Constraints
 * -	piles will contain between 1 and 50 elements, inclusive.
 * -	Each element of piles will be between 1 and 1000, inclusive.
 * -	piles will be sorted in non-descending order.
 *
 * Examples 0)	
 *     	
 * {6,6} Returns: "YOU LOSE" You can't win this game. Your friend will force you
 * to take stones from the first pile at each turn, and then mirror your move by
 * taking the same number of stones from the second pile.  1)	
 *     	
 * {6,12} Returns: "TAKE 6 STONES FROM PILE 1" If you take 6 stones from the
 * second pile, you can follow the strategy outlined above.  2)	
 *     	
 * {3,6,6} Returns: "TAKE 3 STONES FROM PILE 0" 3)	
 *     	
 * {3,5,9,11,16} Returns: "TAKE 2 STONES FROM PILE 0" 4)	
 *     	
 * {32,136,251,369,403,593,624,657,729,731,769} Returns: "YOU LOSE"
 *
 * Mental notes:
 * Any game with single pile is winning for the player.
 * Two piles
 * { 1, 1 } is losing
 * { 1, 2 } is winning
 * { 1, 1, 1 } is winning
 * { 1, 1, 2 } is losing because we have to maintain the constraint of
 *  the piles to be non-decreasing in size. We can NOT take 2 stones from pile
 *  2 as that would make the piles non-decreasing. We can either take one stone
 *  from pile 2, which moves the game to { 1, 1, 1 } which is winning for the
 *  other player, OR we take the the remaining stone from pile 0, which moves
 *  the game to { 0, 1, 2 } which is again winning for the other player.
 */
