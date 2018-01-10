#include <iostream>

using namespace std;

/*

https://community.topcoder.com/stat?c=problem_statement&pm=12394&rd=15839

Problem Statement
    	Elly and Kris play the following game. In the beginning there are several boxes aligned in a row. The boxes may or may not contain candy. As a matter of fact, the girls know exactly how many candies each of them contains. This information is given to you in the int[] sweets.



Starting with Elly, the girls make moves in alternating order. A single move looks as follows: the player whose turn it is chooses one of the non-empty boxes and takes all the sweets from it. After that the amount of candy in the neighboring boxes is doubled. For example, suppose that there were five boxes with {20, 50, 70, 0, 30} sweets, respectively. If the girl whose turn it was chose box 0, then in the next turn the number of sweets in the boxes would be {0, 100, 70, 0, 30}. If she chose box 1, then it would be {40, 0, 140, 0, 30}. If she chose box 2, it would be {20, 100, 0, 0, 30}. If she chose box 4, it would be {20, 50, 70, 0, 0}. Note that the girl cannot choose box 3, because it is empty.

The game ends when all boxes are empty. The winner of the game is the girl who has more candies at the end of the game.



Return the name of the girl that will win the game if both girls play optimally, or "Draw" if they end up with the same number of candies.
 
Definition
    	
Class:	EllysCandyGame
Method:	getWinner
Parameters:	int[]
Returns:	String
Method signature:	String getWinner(int[] sweets)
(be sure your method is public)
    
 
Notes
-	Playing optimally means that if there is a move, which guarantees that the girl whose turn it is will win no matter what the other girl does, she will play it. If there is no such move, but there is one, which would guarantee a draw, she will use it instead.
-	The game always ends after a finite number of moves, because the number of empty boxes increases in each step.
 
Constraints
-	sweets will contain between 1 and 10 elements, inclusive.
-	Each element of sweets will be between 0 and 1000, inclusive.
 
Examples
0)	
    	
{20, 50, 70, 0, 30}
Returns: "Kris"
If Elly takes the 20, then Kris can take the 30, leaving Elly the choice between 100 and 70. Elly should take the 100, but then Kris will take 140 and win.

If Elly takes the 30, then Kris can take the 20, leaving Elly the same choice.

If Elly takes the 50, then Kris can take the 140, leaving Elly the choice between a 40 and a 30.

If Elly takes the 70, then Kris can take the 100, leaving Elly the same choice.

In any case, Kris will take more than Elly and win.
1)	
    	
{42, 13, 7}
Returns: "Elly"
Here Elly can take the 42 in her first move and win, no matter whether Kris chooses the 26 or 7.
2)	
    	
{10, 20}
Returns: "Draw"
Elly cannot win, but she can force a draw by taking the 20 (and leaving 20 to her opponent).
3)	
    	
{3, 1, 7, 11, 1, 1}
Returns: "Kris"
4)	
    	
{41, 449, 328, 474, 150, 501, 467, 329, 536, 440}
Returns: "Kris"
5)	
    	
{177, 131, 142, 171, 411, 391, 17, 222, 100, 298}
Returns: "Elly"

INPUT:

6
5
20 50 70 0 30
3
42 13 7
2
10 20
6
3 1 7 11 1 1
10
41 449 328 474 150 501 467 329 536 440
10
177 131 142 171 411 391 17 222 100 298


*/

#define MAX 10

int N;

int box[MAX];




enum player
{
	Elly,
	Kris,
	Draw
};

char* str[3] = {"Elly", "Kris", "Draw"};

player calcwinner(int Esk, int Ksk, player p)
{
	int sum =0;
	for(int i=0; i<N;i++)
		sum += box[i];

	// all boxes are empty now, time to decide winner
	if(sum == 0)
	{
		if(Esk == Ksk)
			return Draw;
		else if(Esk > Ksk)
			return Elly;
		else 
			return Kris;
	}

	bool draw_flag = false;
	int temp[MAX];
	
	for(int i=0;i<N;i++)
		temp[i] = box[i];

	for(int i=0;i<N;i++)
	{
		if(box[i] != 0)
		{
			int Eskn = Esk;
			int Kskn = Ksk;
		    (p == Elly)?(Eskn += box[i]):(Kskn += box[i]);
			box[i] = 0;

			if(i-1 >=0)
				box[i-1] *= 2;

			if(i+1 <N)
				box[i+1] *= 2;

			player p1 = calcwinner(Eskn, Kskn, ((p!=Elly)?Elly:Kris));

			for(int j=0;j<N;j++)
				box[j] = temp[j];

			if(p == p1)
				return p;
			else if (p1 == Draw)
				draw_flag = true;
		}
	}

	if(draw_flag)
		return Draw;
	
	return ( (p!=Elly)?Elly:Kris);
}

player findWinner()
{
	return calcwinner(0, 0, Elly);
}

int main()
{
	freopen("input.txt", "r", stdin);

	int T;
	cin >> T;

	for (int count = 1; count <= T; count++)
	{
		cin >> N;

		for (int i = 0; i < N; i++)
		{
			cin >> box[i];
		}

		player answer = findWinner();
		cout << "#" << count << " " << str[answer] << endl;
		getchar();
	}
	return 0;
}