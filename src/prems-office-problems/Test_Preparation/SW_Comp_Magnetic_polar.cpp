#include <iostream>

using namespace std;

#define GRID 100
#define TESTCASES 10
#define NORTH 1
#define SOUTH 2

void finalposition (int map[GRID][GRID])
{
	bool move[GRID];
	for(int i=0; i<GRID; i++)
		move[i] = true;

	for(int j=0; j<GRID; j++)
	{
		while(move[j])
		{
			move[j] = false;
			for(int i=GRID-1;i>=0;i--)
			{
				if(i== GRID-1 && map[i][j] == NORTH)
				{
					map[i][j] = 0;
					move[j] = true;
				}

				if(map[i][j] == NORTH && i+1<GRID && map[i+1][j] == 0)
				{
					map[i][j] = 0;
					map[i+1][j] = NORTH;
					move[j] = true;
				}
			}
			for(int i=0; i<GRID;i++)
			{
				if(i==0 && map[i][j] == SOUTH)
				{
					map[i][j] = 0;
					move[j] = true;
				}

				if(map[i][j] == SOUTH && i-1 >=0 && map[i-1][j] ==0)
				{
					map[i][j] = 0;
					map[i-1][j] = SOUTH;
					move[j] = true;
				}
			}
		}
	}
}

int findstandstill(int map[GRID][GRID])
{
	finalposition(map);
	int count = 0;
	for(int j=0;j<GRID;j++)
	{
		for(int i=0; i< GRID; i++)
		{
			if( i+1<GRID && map[i][j] == 1 && map[i+1][j] == 2)
				count++;
		}
	}

	return count;
}


int main() {
	int i, j, k;
	int map[GRID][GRID];
	int num;
	int answer;
	freopen("input.txt", "r", stdin);

	for(int i=0;i<TESTCASES;i++) {
		//initialize
		for(int j=0;j<GRID;j++)
			for(int k=0;k<GRID;k++)
				map[j][k]=0;
		answer=0;

		//read input
		cin >> num;
		for(int j=0;j<num;j++)
			for(int k=0;k<num;k++)
				cin >> map[j][k];

		answer = findstandstill(map);
		cout << "#" << i+1 << " " << answer << endl;
	}

	return 0;
}