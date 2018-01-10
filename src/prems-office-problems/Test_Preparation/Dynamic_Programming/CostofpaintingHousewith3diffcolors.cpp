#include <iostream>

using namespace std;


/*
There are a row of houses, each house can be painted with three colours red, blue and green. 
The cost of painting each house with a certain colour is different. 
You have to paint all the houses such that no two adjacent houses have the same colour. 
You have to paint the houses with minimum cost. How would you do it?


Note: 
Painting house-1 with red costs different from painting house-2 with red. The costs are different for each house and each colour.


Approach:
Dynamic Programming solution:
We can paint the ith house with blue, red or green.
so we have the following equations:
cost[i,r] = min( cost[i-1,b], cost[i-1,g] ) + cost of painting i with r.
cost[i,g] = min( cost[i-1,b], cost[i-1,r] ) + cost of painting i with g.
cost[i,b] = min( cost[i-1,r], cost[i-1,g] ) + cost of painting i with b.


Final Min Cost = min (cost[n,b], cost[n,r], cost[n,g]);


---------------------------
    R      G       B
---------------------------
1   7      5       10 
---------------------------
2   3      6        1
---------------------------
3   8      7       4
--------------------------
4   6      2       9
--------------------------
5   1      4       7
--------------------------
6   2      3       6
--------------------------


Code output:

Cost matrix leading to the solution: 
0 0 0 
7 5 10 
8 13 6 
14 13 12 
18 14 22 
15 22 21 
23 18 21 
Cost of colouring the house is: 18
*/

#define min(a,b) ((a<b)?(a):(b))

// Cost are mentioned in the order 'R', 'G', 'B'
int costMatrix[][3] = {
	{7, 5, 10},
	{3, 6, 1},
	{8, 7, 4},
	{6, 2, 9},
	{1, 4, 7},
	{2, 3, 6},
};

int calcHouseColoringCost()
{
	//Solution matrix needs to be two dimensional
	// C[i][j] denotes cost of colouring house 'i' with colour 'j', when we have taken care of painting house i-1 with min cost and given constraints
	// i runs from 1 to no of houses, note that 0 would be used as base case (house before house no 1)

	// no of houses + 1, since we are indexing from 1 to n
	int row = sizeof(costMatrix)/sizeof(costMatrix[0]) + 1;
	// No of colours, Red, Green and Blue
	int col = 3;

	int** C; // Resulting Cost Matrix
	C = new int*[row];
	for(int i=0;i<row;i++)
		C[i] = new int[col];

	for(int j=0;j<col;j++)
		C[0][j] = 0; // base case for house no 0, real calculation starts with house no 1

	for(int r=1;r<row;r++)
	{
		C[r][0] = min(C[r-1][1], C[r-1][2]) + costMatrix[r-1][0];
		C[r][1] = min(C[r-1][0], C[r-1][2]) + costMatrix[r-1][1];
		C[r][2] = min(C[r-1][0], C[r-1][1]) + costMatrix[r-1][2];
	
		// Lets print the resulting cost matrix
		cout.width(3);
		cout << std::right << C[r][0] << " ";
		cout.width(3);
		cout << std::right << C[r][1] << " ";
		cout.width(3);
		cout << std::right << C[r][2] << endl;
	}

	int final_result =   min (min(C[row-1][0], C[row-1][1]), C[row-1][2]);

	return final_result;
}

int main() {

	int cost = calcHouseColoringCost();
	cout << "Cost of colouring the house is: " << cost << endl;
	return 0;
}