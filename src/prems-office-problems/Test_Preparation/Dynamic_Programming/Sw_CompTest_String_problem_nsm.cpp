#include <iostream>

using namespace std;

#define MAX 100

char arr[MAX];
int num, manfC, recC;

//both indexes run from 1 to 100
// this is DP Aux array
// repVal[i][j] denotes minimum cost of recording i width with recording block length of j
int repVal[MAX+1][MAX+1];


// maximum +ve int possible, see if we want to use long long
int MAX_INT = 0x7fffffff;

bool rightCandidate(int cur, int valLen)
{
	if (cur < 0)
		return false;

	char lval = arr[cur];
	for (int ct = 0; ct < valLen; ct++)
	{
		// Case 1:
		// anytime you find '*', continue
		if (arr[cur - ct] == '*')
			continue;

		// Case 2:
		// we started with base as non '*', if left char does not match with base, then stop here.
		if (lval != '*' && arr[cur - ct] != lval)
			return false;

		// Case 3:
		// we started with base as '*'
		if (lval == '*' && arr[cur - ct] != '*')
		{
			// Found the first left character which is not '*', hence this becomes the new base
			// this is now becomes same as starting with a non '*' base, i.e Case 2
			lval = arr[cur - ct];
		}
	}

	// We were able to move till valLen, hence recording of valLen is possible
	return true;
}

void findMinRecCost()
{

	//////////iterate for all the indexes
	for (int cur = 0; cur < num; cur++)   // 1st loop, for each index ranging from 0 to 99 in the string array
	{
		char curCh = arr[cur];
		//////////////////iterate all previous  indexes now /////////////////////
		for (int prv = cur; prv >= 0; prv--)  // 2nd loop
		{
			int valLen = (cur - prv) + 1;
			if (!rightCandidate(cur, valLen))
			{
				// if prv is not possible, then no need to look till 0 for prv
				break;
			}
			else
			{
				for (int len = 1; len <= valLen; len++) // 3rd loop, for length 1 to valLen possible, hence O(n^3)
				{
					// if the other part cannot support the len, then we should not proceed for len
					if(repVal[cur + 1 - valLen][len] == MAX_INT)
						continue;

					// how many times, recording is needed with len in the width of valLen
					int nocurright = (valLen % len == 0) ? (valLen / len) : (valLen / len) + 1;

					//calculate recording cost
					int right_rcost = nocurright * recC;

					// note that every cur we would hit once only, so no need to check minimum here 

					// total cost, right cost + left cost
					int temp = right_rcost + repVal[cur + 1 - valLen][len];

					// if the new cost temp is minimum so far, take it
					if(repVal[cur+1][len] > temp)
						repVal[cur+1][len] = temp;
				}
			}
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int count = 1; count <= T; count++)
	{
		cin >> num >> manfC >> recC;

		for (int ct = 0; ct < num; ct++)
		{
			cin >> arr[ct];
		}


		///////////////initialize your DP array /////////////////
		for (int cur = 0; cur <= num; cur++)
		{
			for (int len = 0; len <= num; len++)
			{
				repVal[cur][len] = MAX_INT;
			}
		}

		////////////base case, consider this as -1 index ////////
		for (int len = 0; len <= num; len++)
		{
			repVal[0][len] = 0;
		}
		///////////////////////////////////////////////////////////////////////


		///////Now, lets calculate cost of recording for each item from index 1 to num and len 1 to num
		findMinRecCost();

		/////////////////////////////////////////////////////////////////////
		int mn = MAX_INT;
		for (int len = 1; len <= num; len++)
		{
			// if len unit is possible.....
			if(repVal[num][len] != MAX_INT)
			{
				int val = manfC * len;
				val += repVal[num][len];

				if (val < mn)
					mn = val;
			}
		}
		cout << "#" << count << " " << mn << endl;
	}
	return 0;
}