#include<iostream>

using namespace std;

void findC(double* dist, int* mass, int N, double* x_dist)
{
	int index;

	for(int index =1; index<=N-1; index++)
	{
		double diff1, diff2;
		double left = dist[index-1];
		double right = dist[index];

		double distance;
		double left_force, right_force;

		do
		{
			x_dist[index] = (left+right)/2;
			left_force = 0;
			right_force = 0;

			for(int i=0; i<index; i++)
			{
				distance = x_dist[index] - dist[i];
				left_force +=  mass[i]/(distance*distance);
			}

			for(int i=index; i<N; i++)
			{
				distance = dist[i] - x_dist[index];
				right_force += mass[i]/(distance*distance);
			}

			if(left_force>right_force)
			{
				diff1 = left_force-right_force;
				left = x_dist[index];
			}
			else
			{
				diff1 = right_force-left_force;
				right = x_dist[index];
			}
			diff2 = right-left;
		} while (diff1 != 0.0 && diff2 > 0.000000000001);
	}
}



int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("input.txt", "r", stdin);

	cin>>T;
	int N;
	double* dist;
	int* mass;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		dist = new double[N];
		mass = new int[N];

		for(int i=0;i<N;i++)
		{
			cin >> dist[i];
		}

		for(int i=0;i<N;i++)
		{
			cin >> mass[i];
		}

		double* xdist;
		xdist = new double[N];

		findC(dist, mass, N, xdist);


		cout << "#" << test_case;

		for(int i=1; i<=N-1; i++)
		{
			cout.precision(10);
			cout << std::fixed;
			cout << " " << xdist[i];
		}
		cout << endl;

		delete[] dist;
		delete[] mass;
		delete[] xdist;
	}
	return 0;
}