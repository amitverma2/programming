/*

In the 2nd World War, the battle between theAllied Forces and the German troops are getting fiercer. Many parts of the roads in the region where the battle is taking place are
damaged. As seen in the figure 1(a), vehicles such as trucks and tanks cannot use the roads due to massive bombings and street battle. To win the battle, there must be roads 
on which Armored Division and Supply Unit move promptly. 

The Corps of Engineers will do the road repair work within a short amount of time so that the travel can be possible from the starting place(S) to the arrival place(G). 
The repair time increases in proportion to the depth by which the roads are damaged. 
Find the total repair time for the path with the shortest repair time among the paths from the starting place to the arrival place. 
Assume if the depth is 1, 1 hour is needed for repair work. 

Map information is represented in the form of two-dimensional array as seen in the figure 1(b).  
The starting point is section S in the upperleft corner, 
and the arrival place is section G in the lower right corner.

Movement can be made in up, down, left, and right directions, and it can be made by one section. 
For map information, the depth by which the roads are damaged is given in each section. Movement to another section is possible only 
after repair of the current section is completed.



﻿

 

 

 

 



Assume it takes much more time to repair the roads compared to the time needed for moving. Therefore, you do not need to consider the distance from the starting place to 
the arrival place. 


The map information, as seen in the figure 2, has two-dimensional array format. The starting place(S) and arrival place(G) are inthe upper left and lower right side respectively, 
and are represented as 0 in input data. Sections represented as 0 other than the starting and arrival places do not need repair work. 



s
 
4
 
9
 
2
 
1
 
3
 
1
 
2
 
2
 

3
 
2
 
8
 
0
 
1
 
3
 
8
 
2
 
1
 

2
 
0
 
7
 
2
 
3
 
0
 
3
 
0
 
 
 

4
 
5
 
2
 
0
 
3
 
2
 
4
 
2
 
0
 

1
 
1
 
1
 
7
 
0
 
2
 
8
 
3
 
4
 

2
 
0
 
0
 
0
 
5
 
3
 
0
 
3
 
4
 

0
 
1
 
2
 
1
 
3
 
2
 
1
 
2
 
1
 

0
 
2
 
0
 
0
 
1
 
0
 
4
 
1
 
G
 


Figure 2 MapFormat


 


In the map below, the minimum time for repair work is 2 and the grey area will be the path. 



s
 
1
 
0
 
0
 

1
 
1
 
1
 
0
 

1
 
0
 
1
 
1
 

1
 
0
 
1
 
G
 


 


 


 


[Input]


10 test cases are given continuously through standard input.  


The size of the map(N x N) is given for each test case. The maximum size of the map is 100 x 100.


From the next line, map information in the form of two-dimensional array is given. 


[Output]


Print answers for each of the test cases in order, and print “#C” at start of line for each test case with C being the case number.
Leave a blank space in the same line, and print out the repair time of the pathwith the shortest repair time among the paths from the starting place to the arrival place.  


 


[Input/output example]


Input



4

0100

1110

1011

1010

6

011001

010100

010011

101001

010101

111010

8

. . .
 


Output



#1 2

#2 2

. . .
 


 

 */



#include<iostream>

using namespace std;

#define MAX_INT 0x7FFFFFFF

int findMin(int* dist, bool* sptSet, int total)
{
	int min = MAX_INT;
	int index;

	for(int i=0; i< total; i++)
	{
		if( dist[i] <= min && sptSet[i] == false)
		{
			index = i;
			min = dist[i];
		}
	}
	return index;
}


int findMinDist(int** g, int V)
{
	int *dist;
	bool *sptSet;
	int *parent;
	int total = V*V;
	int final_distance = -1;

	dist = new int [total];
	sptSet = new bool[total];
	//parent = new int[total];


	for(int k=0; k< total ; k++)
	{
		dist[k] = MAX_INT;
		sptSet[k] = false;
	}

	//parent[0] = -1;
	dist[0] = 0;
	int u;
	int i, j;

	for(int count=0; count < total-1 ; count++)
	{
		u = findMin(dist, sptSet, total);
		sptSet[u] = true;

		i = u/V;
		j = u%V;

		/*
		cout << "u: " << u << " " << "i: " << i << " " << " j: " << j << " " << "dist[u]: " << dist[u] << endl;
		*/

		if( u == total - 2 || u == total-1-V)
		{
			final_distance = dist[u];
			break;
		}


		// check for each of the 4 neighbour

		if( i-1 >= 0 && sptSet[u-V] == false && dist[u] != MAX_INT && dist[u]+g[i-1][j] < dist[u-V] )
		     dist[u-V] = dist[u]+g[i-1][j];
		     //parent[u-V] = u;


		if( i+1 < V && sptSet[u+V] == false && dist[u] != MAX_INT && dist[u]+g[i+1][j] < dist[u+V] )
			dist[u+V] = dist[u]+g[i+1][j];
		    //parent [u+V] = u;
			

		if( j-1 >= 0 && sptSet[u-1] == false && dist[u] != MAX_INT && dist[u]+g[i][j-1] < dist[u-1] )
			dist[u-1] = dist[u]+g[i][j-1];
		    //parent[u-1] = u;;

		if( j+1 < V && sptSet[u+1] == false && dist[u] != MAX_INT && dist[u]+g[i][j+1] < dist[u+1] )
			dist[u+1] = dist[u]+g[i][j+1];
		    //parent[u+1] = u;
	}

	delete[] dist;
	delete[] sptSet;
/*
	i = u;
	cout << "path: " << total-1 << " " << u;
	while(parent[u] != -1) {
		cout << " " << parent[u];
		u = parent[u];
	}
	cout << endl;
*/
	//delete[] parent;
	return final_distance;
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
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

	int **g;
	int V;
	int u;
	int distance;

    /*
	   Read each test case from standard input.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> V;
		char* str;
		str = new char[V+1];

		g = new int* [V];
		for(int i=0; i<V; i++)
			g[i] = new int [V];

		for(int i=0; i<V; i++)
		{
			cin >> str;
			for(int j=0; j<V;j++)
			{
				g[i][j] = str[j] - '0';
			}
		}

		distance = findMinDist(g, V);

		for(int i=0; i<V; i++)
			delete[] g[i];

		delete[] g;
		delete[] str;

		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << distance << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}