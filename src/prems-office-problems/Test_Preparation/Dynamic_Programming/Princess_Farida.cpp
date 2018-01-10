#include <iostream>

using namespace std;


/*
Once upon time there was a cute princess called Farida living in a castle with her father, mother and uncle. On the way to the castle there lived many monsters. Each one of them had some gold coins. Although they are monsters they will not hurt. Instead they will give you the gold coins, but if and only if you didn't take any coins from the monster directly before the current one. To marry princess Farida you have to pass all the monsters and collect as many coins as possible. Given the number of gold coins each monster has, calculate the maximum number of coins you can collect on your way to the castle.

Input

The first line of input contains the number of test cases. Each test case starts with a number N, the number of monsters, 0 <= N <= 10^4. The next line will have N numbers, number of coins each monster has, 0 <= The number of coins with each monster <= 10^9. Monsters described in the order they are encountered on the way to the castle.

Output

For each test case print “Case C: X” without quotes. C is the case number, starting with 1. X is the maximum number of coins you can collect.

Example

Input:
2
5
1 2 3 4 5
1
10
Output:
Case 1: 9
Case 2: 10

Solution: if aux[i] contains answer for ith position, it can be calculated as:
       aux[i] = max( aux[i-1], aux[i-2]+ cmonster[i-1])
Let us run the index from 1 to N
0th index can have base case as '0'
*/

#define N 5

#define max(a,b) (a>b?a:b)

int cmonster[N] = 
{8,25,9,44,15};

int findmaxCoin()
{
	int aux[N+1];
	//base case
	aux[0] = 0;

	for(int i=1;i<N+1;i++)
	{
		if(i==1)
			aux[i] = cmonster[i-1];  //aux[i-1] is 0 and there is no aux[i-2]
		else
		{
			// for every other case, you would be having i-1 and i-2, since we are indexing from 1 to N
			// note that cmonster is indexed from 0 to N-1
			aux[i] = max(aux[i-1], (aux[i-2]+cmonster[i-1]));
		}
		cout << "aux[" << i << "]: " << aux[i] <<endl;
	}
	return aux[N];
}


int main()
{
	int answer;
	answer = findmaxCoin();
	cout << "Max Coint that be collected: " << answer << endl;
	cout << "wohoooooo....lets marry princess now" << endl;
	return 0;
}