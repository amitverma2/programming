#include <iostream>
using namespace std;

// Assuming max row value 10 and max col value is 30
int arr[10][30];
int dp[1 << 10][30];

int ROW;
int COL;

void printmask(int mask, int col)
{
	cout << "Mask: ";
	for(int i=0;i<ROW;i++)
	{
		if(mask & 1<<i)
			cout << "1";
		else
			cout << "0";
	}
	cout << ", COL: " << col << endl;
}

int getmask(int col)
{
	int mask = 0;
	for (int i = 0; i < ROW; i++)
	{
		if (arr[i][col] == 1)
			mask = mask | (1 << i);
	}
	return mask;
}

int findmaxcell(int col)
{
	if (col == COL - 1)
		return 0;
	// Lets get the current mask for this coloumn
	int mask = getmask(col);
    // printmask(mask, col);

	if (dp[mask][col] != -1)
		return dp[mask][col];

	int max_val = 0x80000000;
	// We ensured we are playing in the range till ROW-1 and COL-1
	// hence boundary check wont be required
	for (int i = 0; i < ROW - 1; i++)
	{
		if (arr[i][col] == 1 && arr[i][col + 1] == 1
			&& arr[i + 1][col] == 1 && arr[i + 1][col + 1] == 1)
		{
			arr[i][col] = 0;
			arr[i][col + 1] = 0;
			arr[i + 1][col] = 0;
			arr[i + 1][col + 1] = 0;
			int cur_val = findmaxcell(col);
			if (max_val < cur_val+1)
				max_val = cur_val + 1;

			arr[i][col] = 1;
			arr[i][col + 1] = 1;
			arr[i + 1][col] = 1;
			arr[i + 1][col + 1] = 1;
		}
	}
	int next_val = findmaxcell(col + 1);
	if (max_val < next_val)
		max_val = next_val;
	return dp[mask][col] = max_val;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int count = 1; count <=T; count++)
	{
		cin >> ROW >> COL;
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				cin >> arr[i][j];
			}
		}

		//Initialize the DP array
		for (int i=0; i< 1<< ROW; i++)
		{
			for (int j=0; j < COL; j++)
			{
				dp[i][j] = -1;
			}
		}
		// Starting with colomn 0
		int answer = findmaxcell(0);

		cout << "#" << count << " " << answer << endl;
	}
	return 0;
}