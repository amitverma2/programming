#include <iostream>
using namespace std;

#define INF 0x7FFFFFFFFFFFFFFF

typedef long long ul;


int findMin(ul **g, int N, ul *key, bool* mstSet)
{
	int index = -1;
	ul min_val = INF;

	for(int i=0; i<N; i++)
	{
		if(key[i] <= min_val && mstSet[i] == false)
		{
			index = i;
			min_val = key[i];
		}
	}
	return index;
}



ul findweightspanning(ul **g, int N)
{
	ul *key;
	key = new ul [N];

	bool *mstSet;
	mstSet = new bool[N];

	for(int i=0; i<N; i++)
	{
		key[i] = INF;
		mstSet[i] = false;
	}

	key[0] = 0;
	int u;
	ul final_dist = 0;

	for(int i=0; i<N-1;i++)
	{
		u = findMin(g, N, key, mstSet);
		mstSet[u] = true;
		final_dist += key[u];

		for(int v=0; v<N; v++)
		{
			if( mstSet[v] == false && g[u][v] != 0 && g[u][v] < key[v])
				key[v] = g[u][v];
		}
	}

	u = findMin(g, N, key, mstSet);
	final_dist += key[u];

	delete[] key;
	delete[] mstSet;

	return final_dist;
}



int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);
	cin>>T;

	ul **g;
	int N;

	ul *xcord;
	ul *ycord;

	double E;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		g = new ul* [N];
		xcord = new ul[N];
		ycord = new ul[N];



		for(int i=0; i<N; i++)
			g[i] = new ul[N];

		for(int i=0; i<N; i++)
			cin >> xcord[i];

		for(int i=0; i<N; i++)
			cin >> ycord[i];

		cin >> E;

		long long xdiff, ydiff;

		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				if( i == j)
					g[i][j] = 0;
				else
				{
					xdiff = xcord[i]-xcord[j];
					ydiff = ycord[i]-ycord[j];


					g[i][j] = (xdiff*xdiff) + (ydiff*ydiff);
				}
			}
		}

		delete[] xcord;
		delete[] ycord;

		ul answer;
		answer = findweightspanning(g, N);

		E = E*answer;


		for(int i=0; i<N; i++)
			delete[] g[i];
		delete[] g;

		cout << "#" << test_case << " " << (unsigned long long)(E+0.5) << endl;
	}
	return 0;
}