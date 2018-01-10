#include <iostream>

using namespace std;

#define MAX 50

int S, a, b, c;
long long dp[MAX + 1][MAX + 1][MAX + 1][MAX + 1];


int count(int s, int x, int y, int z)
{
	if (dp[s][x][y][z] != -1)
		return dp[s][x][y][z];

	long long total = 0;

	// Perfect condition
	if (s == S && x == a && y == b && z == c)
		return 1;

	if (s < S && x == a && y == b && z == c)
		return 0; // all completed their quota, but could not sing all songs

	if (s >= S)
		return 0;

	if (x<a)
		total += count(s + 1, x + 1, y, z);
	if (y<b)
		total += count(s + 1, x, y + 1, z);
	if (z<c)
		total += count(s + 1, x, y, z + 1);

	if (x<a && y<b)
		total += count(s + 1, x + 1, y + 1, z);

	if (y<b && z<c)
		total += count(s + 1, x, y + 1, z + 1);

	if (z<c && x <a)
		total += count(s + 1, x + 1, y, z + 1);

	if (x<a && y<b && z<c)
		total += count(s + 1, x + 1, y + 1, z + 1);

	total = dp[s][x][y][z] = total % 1000000007;
	return total;
}


int main()
{
	cin >> S >> a >> b >> c;
	for (int i = 0; i <= MAX; i++)
	{
		for (int j = 0; j <= MAX; j++)
		{
			for (int k = 0; k <= MAX; k++)
			{
				for (int l = 0; l <= MAX; l++)
				{
					dp[i][j][k][l] = -1;
				}
			}
		}
	}

	cout << "Total no of combination possible: " << count(0, 0, 0, 0) << endl;

}