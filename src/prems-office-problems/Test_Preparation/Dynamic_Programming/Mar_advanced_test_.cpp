#include <iostream>

using namespace std;

#define MAX_INT 0x7fffffff
#define MAX 20

int N;

int org[MAX];
int ncost[MAX];

int final_min;

void countUtil(int node, int cur, int temp1, int temp2, int temp3)
{
	// this would never be the case, taking extra care
	if(node > N-1)
		return;

	//there is no way we can improve current cost better than final_min, hence return.
	if (cur >= final_min)
		return;

	// Last node, cross this one and we would be done
	if (node == N - 1)
	{
		// in this case, Hire is not required
		// if Battle is possible, thats the best thing to do

		//lets battle, if possible
		if (temp1+ temp2 + temp3 >= org[node])
		{
			if (final_min > cur)
				final_min = cur;
		}
		else
		{
			//ok, pass is the only option
		    cur += ncost[node];
			if (final_min > cur)
				final_min = cur;
		}
	}
	else
	{
		// Pass, Hire and Battle is possible

		//Lets pass
		countUtil(node + 1, cur + ncost[node], temp1, temp2, temp3);

		//or lets hire
		countUtil(node + 1, cur + (2 * ncost[node]), temp1, temp2, temp3+org[node]);

		//or lets battle as well
		// if we have more orgs, then only we can fight
		// note that for node '0', we would never have orgs to fight
		if (temp1+temp2+temp3 >= org[node])
		{
			if(temp1 >= org[node])
				temp1 -= org[node];
			else if(temp2 >= org[node]-temp1)
			{
				temp2 -= org[node]-temp1;
				temp1 = 0;
			}
			else
			{
				temp3 -=org[node]-temp1-temp2;
				temp1 = temp2 = 0;
			}

			// They fought 1 battle, hence reduce the life
			temp1 = temp2;
			temp2 = temp3;
			temp3 = 0;

			countUtil(node + 1, cur, temp1, temp2, temp3);
		}
	}
}

void findmincost()
{
	// starting with min cost as worst case		
	final_min = MAX_INT;
	// node: 0, cost: 0, all org army 0
	countUtil(0, 0, 0, 0, 0);
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
			cin >> org[i] >> ncost[i];
		}

		findmincost();

		cout << "#" << count << " " << final_min << endl;
	}

	return 0;
}