//////////////////////Bipartite Matching////////////////////////

#include <iostream>

using namespace std;

// M is number of applicants and N is number of jobs
#define M 6
#define N 6

bool bpm(int bpGraph[M][N], int u, bool seen[N], int matchR[N])
{
    // Try every job one by one
    for (int v=0; v < N; v++)
    {
		if( bpGraph[u][v] && !seen[v])
		{
			seen[v] = true;

			if(matchR[v] < 0 || bpm(bpGraph, matchR[v], seen, matchR))
			{
				matchR[v] = u;
				return true;
			}
		}
	}
	return false;
}


int maxBPM(int bpGraph[M][N], int matchR[N])
{
	int result = 0;
	bool seen[N];

	for(int u=0; u<M; u++)
	{
		for(int i=0; i<N;i++)
			seen[i] = false;

		if(bpm(bpGraph, u, seen, matchR))
			result++;
	}
	return result;
}


int main()
{
	// For figure refer to: 
	// http://www.geeksforgeeks.org/maximum-bipartite-matching/
	int bpGraph[M][N] = {  
		{0, 1, 1, 0, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{1, 0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0, 0},
		{0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 1}
	};

	// An array to keep track of the applicants assigned to
    // jobs. The value of matchR[i] is the applicant number
    // assigned to job i, the value -1 indicates nobody is
    // assigned.
    int matchR[N];
 
    // Initially all jobs are available
    memset(matchR, -1, sizeof(matchR));

	cout << "Maximum number of applicants that can get job is: "
         << maxBPM(bpGraph, matchR) << endl;

	for(int v=0; v<N; v++)
		cout << "Job No: " << v << "   Applicant no: " << matchR[v] << endl;

	int matchA[M];
	for(int i=0; i<M;i++)
	{
		matchA[i] = -1;
	}
	for(int i=0; i<N;i++)
	{
		matchA[matchR[i]] = i;
	}

	cout << endl;

	for(int u=0; u<M; u++)
	{
		cout << "Applicant no: " << u << "   Job no: ";
		cout.width(2);
		cout << std::right << matchA[u] << endl;
	}
 
    return 0;
}