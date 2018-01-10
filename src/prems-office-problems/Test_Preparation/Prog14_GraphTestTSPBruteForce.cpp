/* TSP problem - Brute force, optimal but not efficient */
// For figure, refer: http://www.people.vcu.edu/~gasmerom/MAT131/brutefrc.html

#include<iostream>
#include<list>

using namespace std;

//#define V 5   // No of vertices
#define HOME_CITY 0 // HOME City vetex is 0

int current_minimum_cost = INT_MAX;
list<int> tsp_solution;

// A - 0, B - 1, C - 2, D - 3, E - 4

void tsp(int **graph, list<int>& path, int total_cost, list<int>& remaining_cities, int final_city)
{
	int last_visited_city = path.back();

	if(total_cost > current_minimum_cost)
	{
		// abort, no point exploring this path
		return;
	}

	if(remaining_cities.empty())
	{
		// all cities have been visited
		// only add the distance back to the home city (salesman returns home)
		path.push_back(final_city);
		total_cost += graph[last_visited_city][final_city];

		if(total_cost < current_minimum_cost) 
		{
			// we have a new winner
			current_minimum_cost = total_cost;
			tsp_solution.clear();
			tsp_solution.assign(path.begin(), path.end());
		}
		return;
	}

	// calculate the new possibilities to travel to from the current city
	list<int>::iterator i;
	for(i=remaining_cities.begin(); i!= remaining_cities.end(); ++i)
	{
		list<int> newPath;
		newPath.assign(path.begin(), path.end());
		newPath.push_back(*i);

		int total_cost_new = total_cost + graph[last_visited_city][*i];

		// make a list of 'remaining cities' to visit
		list<int> newRemaining_cities;
		newRemaining_cities.assign(remaining_cities.begin(), remaining_cities.end());
		newRemaining_cities.remove(*i);

		tsp(graph, newPath, total_cost_new, newRemaining_cities, final_city);
	}
	return;
}


class Point {
	int x;
	int y;

public:
	Point(): x(0), y(0) {}
	Point(int x1,int y1): x(x1), y(y1){}
	Point(Point& p) { x = p.x; y=p.y;}
	int getx(){return x;}
	int gety(){return y;}
};

int difference(Point a, Point b)
{
	int xa = a.getx();
	int ya = a.gety();

	int xb = b.getx();
	int yb = b.gety();

	int diffx,diffy;
	diffx = (xa>xb)?xa-xb:xb-xa;
	diffy = (ya>yb)?ya-yb:yb-ya;

	int result = diffx+diffy;

	return result;
}

int main()
{
	int num_customers;
	scanf("%d", &num_customers);

	int **graph;
	graph = new int* [num_customers+2];
	for(int i=0; i<num_customers+2; i++)
	{
		graph[i] = new int [num_customers+2];
	}

	Point* arr;
	arr = new Point[num_customers+2];

	int x,y;

    scanf("%d %d", &x, &y);
	arr[0] = Point(x,y);

    scanf("%d %d", &x, &y);
	arr[num_customers+1] = Point(x,y);

	for(int i=1; i<=num_customers; i++) {
		scanf("%d %d", &x, &y);
		arr[i] = Point(x,y);
	}

	/*
	for(int i=0; i<=num_customers+1; i++) {
		cout << "Point: " << i << "is: " << arr[i].getx() << "," << arr[i].gety() << "\n";
	}
	*/

	for(int i=0; i<num_customers+2; i++)
	{
		for(int j=0; j<num_customers+2; j++) 
		{
			if(i==j)
			{
				graph[i][j] = 0;
				continue;
			}
			graph[i][j] = difference(arr[i], arr[j]);
		}
	}

/*
	for(int i=0; i<num_customers+2; i++)
	{
		for(int j=0; j<num_customers+2; j++) 
		{
			cout << graph[i][j] << " ";
		}
		cout << "\n";
	}
*/

	list<int> path; // would contain the final best path
	list<int> remaining_cities;
	//input all the cities to remaining cities except the starting city


	path.push_back(0);  //since we would start with node 0
	
	for(int i=1; i<=num_customers; i++)
	{
	    remaining_cities.push_back(i);
	}

    tsp(graph, path, 0, remaining_cities, num_customers+1 );

	cout << "Shortest distance: " << current_minimum_cost 
		 << "\nPath is: ";
	
	list<int>::iterator i;
	for(i = tsp_solution.begin(); i!= tsp_solution.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << "\n";

	//getchar();

	return 0;
}