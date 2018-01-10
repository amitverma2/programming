#include<iostream>

using namespace std;

int points[100000];
int max_len;


#define MAX_INT 0x7fffffff
#define MIN_INT 0x80000000


// A function to check if a given cell (row, col) can be included in DFS
int isSafe(int**g, int N, int row, int col, bool** visited)
{
	// row number is in range, column number is in range and value is 1 
	// and not yet visited
	return (row >= 0) && (row < N) &&
		(col >= 0) && (col < N) &&
		(g[row][col] && !visited[row][col]);
}

int i_min;
int j_min;

int i_max;
int j_max;

void DFS(int** g, int N, int row, int col, bool** visited)
{
	// These arrays are used to get row and column numbers of 8 neighbours 
	// of a given cell
	static int rowNbr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	static int colNbr[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	// Mark this cell as visited
	visited[row][col] = true;
	if (i_min > row)
		i_min = row;

	if (j_min > col)
		j_min = col;

	if (i_max < row)
		i_max = row;

	if (j_max < col)
		j_max = col;

	// Recur for all connected neighbours
	for (int k = 0; k < 8; ++k)
	{
		if (isSafe(g, N, row + rowNbr[k], col + colNbr[k], visited))
			DFS(g, N, row + rowNbr[k], col + colNbr[k], visited);
	}

}

int simple_plating(int** g, int N)
{

	bool** visited;

	visited = new bool*[N];
	for (int i = 0; i < N; i++)
	{
		visited[i] = new bool[N];
		for (int j = 0; j < N; j++)
			visited[i][j] = false;
	}


	int count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; ++j)
		{
			if (g[i][j] && !visited[i][j])
			{
				i_min = MAX_INT;
				j_min = MAX_INT;

				i_max = MIN_INT;
				j_max = MIN_INT;

				DFS(g, N, i, j, visited);

				int hor = i_max - i_min + 1;
				int ver = j_max - j_min + 1;

				int size = (hor > ver) ? hor : ver;


				count++;
				points[max_len++] = i_min + 1;
				points[max_len++] = j_min + 1;
				points[max_len++] = size;

				for (int ii = i_min; ii <= i_max; ii++)
				{
					for (int jj = j_min; jj <= j_max; jj++)
					{
						// Repair these cells
						g[ii][jj] = 0;
					}
				}
			}
		}
	}

	return count;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	int**g;

	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	int N;
	int no_dam;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		g = new int*[N];
		for (int i = 0; i < N; i++)
		{
			g[i] = new int[N];
			for (int j = 0; j < N; j++)
				g[i][j] = 0;
		}

		cin >> no_dam;
		int x, y;
		for (int i = 0; i < no_dam; i++)
		{
			cin >> x >> y;
			x--; y--;
			g[x][y] = 1;
		}

		/*
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << g[i][j] << " ";
			}
			cout << endl;
		}
		*/

		max_len = 0;
		int final_num = simple_plating(g, N);
		cout << "#" << test_case << " " << final_num;

		for (int i = 0; i < max_len; i++)
		{
			cout << " " << points[i];
		}

		/*
		cout << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << g[i][j] << " ";
			}
			cout << endl;
		}
		*/

		/*

		int ctr;
		ctr = 0;
		while (ctr < max_len)
		{
		cout << " " << points[ctr]; ctr++;
		cout << " " << points[ctr]; ctr++;
		cout << " " << points[ctr]; ctr++;

		int x = points[ctr - 3];
		int y = points[ctr - 2];
		int size = points[ctr - 1];

		while (ctr < max_len)
		{
		if (x + size >= points[ctr] && y + size >= points[ctr + 1])
		{
		ctr += 3;
		continue;
		}
		else
		break;
		}
		}
		*/
		cout << endl;

	}
	return 0;
}