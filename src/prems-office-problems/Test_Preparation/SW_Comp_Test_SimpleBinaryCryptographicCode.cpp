#include<iostream>

using namespace std;

int a0[] = {0,0,0,1,1,0,1};
int a1[] = {0,0,1,1,0,0,1};
int a2[] = {0,0,1,0,0,1,1};
int a3[] = {0,1,1,1,1,0,1};
int a4[] = {0,1,0,0,0,1,1};
int a5[] = {0,1,1,0,0,0,1};
int a6[] = {0,1,0,1,1,1,1};
int a7[] = {0,1,1,1,0,1,1};
int a8[] = {0,1,1,0,1,1,1};
int a9[] = {0,0,0,1,0,1,1};

bool compare(int** g, int i, int j, int a[])
{
	for(int k=0;k<7;k++)
	{
		if(g[i][j+k] != a[k])
			return false;
	}
	return true;
}

int findnum(int** g, int i, int j)
{
	if (compare(g, i, j, a0))
		return 0;
	if (compare(g, i, j, a1))
		return 1;
	if (compare(g, i, j, a2))
		return 2;
	if (compare(g, i, j, a3))
		return 3;
	if (compare(g, i, j, a4))
		return 4;
	if (compare(g, i, j, a5))
		return 5;
	if (compare(g, i, j, a6))
		return 6;
	if (compare(g, i, j, a7))
		return 7;
	if (compare(g, i, j, a8))
		return 8;
	if (compare(g, i, j, a9))
		return 9;

    return  -1;
}


int findCode(int** g, int M, int N)
{
	int flag = false;
	int i,j;
	for(i=M-1; i>=0; --i)
	{
		for(j= N-1; j>=0; --j)
		{
			if(g[i][j] == 1)
			{
				flag = true;
				break;
			}
		}
		if(flag)
			break;
	}
	while(i-1 >= 0 && g[i-1][j] == 1)
		--i;

	j = j-55;

	int x1,x2,x3,x4,x5,x6,x7,x8;

	x1 = findnum(g, i, j);
	x2 = findnum(g, i, j+7);
	x3 = findnum(g, i, j+14);
	x4 = findnum(g, i, j+21);
	x5 = findnum(g, i, j+28);
	x6 = findnum(g, i, j+35);
	x7 = findnum(g, i, j+42);
	x8 = findnum(g, i, j+49);

	int code;

	code = (x1+x3+x5+x7)*3 + (x2+x4+x6) + x8;
	if( code%10 == 0)
		return x1+x2+x3+x4+x5+x6+x7+x8;
	else
		return 0;

}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	int M;
	int N;
	/* 
	The freopen function below opens input.txt in read only mode and 
	sets your standard input to work with the opened file. 
	When you test your code with the sample data, you can use the function
	below to read in from the sample data file instead of the standard input.
	So. you can uncomment the following line for your local test. But you
	have to comment the following line when you submit for your scores.
	*/

	freopen("input.txt", "r", stdin);
	cin>>T;

	/*
	Read each test case from standard input.
	*/

	int** g;
	char* str;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> M >> N;
		g = new int* [M];
		str = new char[N+1];
		for(int i=0; i<M; i++)
		{
			g[i] = new int [N];
			cin >> str;
			for(int j=0; j<N; j++)
			{
				g[i][j] = str[j]-'0';
			}
		}


		delete[] str;

		int answer;
		answer = findCode(g, M, N);



		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << answer << endl;

		for(int i=0; i<M; i++)
			delete[] g[i];
		delete[] g;
	}

	return 0;//Your program should return 0 on normal termination.
}