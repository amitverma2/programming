/* TSP problem - Brute force, optimal but not efficient */
// For figure, refer: http://www.people.vcu.edu/~gasmerom/MAT131/brutefrc.html

#include<iostream>
#include<list>

using namespace std;

#define V 5   // No of vertices
#define HOME_CITY 0 // HOME City vetex is 0

int current_minimum_cost = INT_MAX;
list<int> tsp_solution;

// A - 0, B - 1, C - 2, D - 3, E - 4

void tsp(int graph[][V], list<int>& path, int total_cost, list<int>& remaining_cities)
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
		path.push_back(HOME_CITY);
		total_cost += graph[last_visited_city][HOME_CITY];

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

		tsp(graph, newPath, total_cost_new, newRemaining_cities);
	}
	return;
}

int main()
{

	int graph[][5] = { 
		{0, 500, 200, 185, 205},
		{500, 0, 305, 360, 340},
		{200, 305, 0, 320, 165},
		{185, 360, 320, 0, 302},
		{205, 340, 165, 302, 0}
	};


	list<int> path; // would contain the final best path
	list<int> remaining_cities;
	//input all the cities to remaining cities except the starting city


	path.push_back(0);  //since we would start with node 0
	
	remaining_cities.push_back(1);
	remaining_cities.push_back(2);
	remaining_cities.push_back(3);
	remaining_cities.push_back(4);

	tsp(graph, path, 0, remaining_cities);

	cout << "Well the answer for TSP by brute force:\n"
		<< "Shortest distance: " << current_minimum_cost 
		<< "\nPath is: ";
	
	list<int>::iterator i;
	for(i = tsp_solution.begin(); i!= tsp_solution.end(); ++i)
	{
		cout << *i << " ";
	}
	cout << "\n";

	getchar();

	return 0;
}