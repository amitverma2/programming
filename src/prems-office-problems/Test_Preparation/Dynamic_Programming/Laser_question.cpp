#include <iostream>

using namespace std;

#define MAX 600

int N;
int arr[MAX][MAX];

int matchR[MAX];
bool seen[MAX];


bool bpm(int u)
{
	for (int v = 0; v < N; v++)
	{
		if (arr[u][v] && !seen[v])
		{
			seen[v] = true;
			if (matchR[v] < 0 || bpm(matchR[v]))
			{
				matchR[v] = u;
				return true;
			}
		}
	}
	return false;
}

int findmaxBPM()
{
	for (int i = 0; i < N; i++)
		matchR[i] = -1;

	int result = 0;
	for (int u = 0; u < N; u++)
	{
		for (int i = 0; i < N; i++)
			seen[i] = false;

		if (bpm(u))
			result++;
	}
	return result;
}

int main()
{
	//freopen("input.txt", "r", stdin);

	int T;
	cin >> T;
	int num_stars;

	int x, y;

	for (int count = 1; count <= T; count++)
	{
		cin >> N;
		cin >> num_stars;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
				arr[i][j] = 0;
		}
		for (int i = 0; i < num_stars; i++)
		{
			cin >> x >> y;
			arr[--x][--y] = 1;
		}

		int answer = findmaxBPM();

		cout << "Case #" << count << endl;
		cout << answer << endl;
	}
	return 0;
}