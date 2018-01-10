/*
Mr. Kim has to deliver refrigerators to N customers. From the office, he is going to visit all the customers and then return to his home.
Each location of the office, his home, and the customers is given in the form of integer coordinates (x,y) (0≤x≤100, 0≤y≤100) .
The distance between two arbitrary locations (x1, y1) and (x2, y2) is computed by |x1-x2| + |y1-y2|,
where |x| denotes the absolute value of x; for instance, |3|=|-3|=3.
The locations of the office, his home, and the customers are all distinct. Y
ou should plan an optimal way to visit all the N customers and return to his among all the possibilities.



You are given the locations of the office, Mr. Kim’s home, and the customers;
the number of the customers is in the range of 5 to 10. Write a program that, starting at the office,
finds a (the) shortest path visiting all the customers and returning to his home. Your program only have to report the distance of a (the) shortest path.



You don’t have to solve this problem efficiently. You could find an answer by looking up all the possible ways.
If you can look up all the possibilities well, you will get a perfect score.



[Constraints]

5≤N≤10. Each location (x,y) is in a bounded grid, 0≤x≤100, 0≤y≤100, and x, y are integers.



[Input]

You are given 10 test cases. Each test case consists of two lines; the first line has N, the number of the customers,
and the following line enumerates the locations of the office, Mr. Kim’s home, and the customers in sequence.
Each location consists of the coordinates (x,y), which is reprensented by ‘x y’.



[Output]

Output the 10 answers in 10 lines. Each line outputs the distance of a (the) shortest path.
Each line looks like ‘#x answer’ where x is the index of a test case. ‘#x’ and ‘answer’ are separated by a space.



[I/O Example]

Input (20 lines in total. In the first test case, the locations of the office and the home are (0, 0) and (100, 100) respectively,
and the locations of the customers are (70, 40), (30, 10), (10, 5), (90, 70), (50, 20).)
*/

#include<iostream>

using namespace std;

#define HOME_CITY 0 // HOME City vetex is 0

template <class T> class list;
template <class T> class List_iterator;

template <class T>
class Node {
	T data;
	Node<T>* next;
	Node<T>* prev;
	Node(T& data1, Node<T>* next1, Node<T>* prev1) : data(data1), next(next1), prev(prev1){}
	friend class list<T>;
	friend class List_iterator<T>;
};

template <class T>
class list {
	Node<T>* head;
	Node<T>* tail;
	int elements;

public:
	typedef List_iterator<T> iterator;
	list() : elements(0), head(NULL), tail(NULL){}
	~list();
	void push_back(T data);
	void push_front(T data);

	void pop_back();
	void pop_front();

	T& front();
	T& back();

	iterator begin();
	iterator end();

	bool empty();
	void clear();
	void remove(T value);

	list& operator = (list & l);
};
template <class T>
void list<T>::remove(T value)
{
	Node<T> * temp;
	temp = head;
	while (temp)
	{
		if (temp->data == value)
			break;
		temp = temp->next;
	}
	if (temp == NULL) return;

	if (head == temp)
		head = temp->next;
	if (tail == temp)
		tail = temp->prev;

	if (temp->prev != NULL)
		temp->prev->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = temp->prev;

	delete temp;
	elements--;
}


template <class T>
list<T>& list<T>::operator = (list<T>& l)
{
	iterator i;
	for (i = l.begin(); i != l.end(); ++i)
	{
		push_back(*i);
	}
	return *this;
}

template <class T>
void list<T>::push_back(T data)
{
	Node<T>* temp = new Node<T>(data, NULL, tail);
	if (head == NULL)
		head = temp;
	if (tail != NULL)
		tail->next = temp;
	tail = temp;
	++elements;
}

template <class T>
void list<T>::push_front(T data)
{
	Node<T>* temp = new Node<T>(data, head, NULL);
	if (tail == NULL)
		tail = temp;
	if (head != NULL)
		head->prev = temp;
	head = temp;
	++elements;
}

template <class T>
void list<T>::pop_back()
{
	Node<T>* temp = tail;
	if (head == tail)
		head = NULL;
	tail = tail->prev;
	tail->next = NULL;

	delete temp;
	elements--;
}

template <class T>
void list<T>::pop_front()
{
	Node<T>* temp = head;
	if (tail == head)
		tail = NULL;
	if (head != NULL)
	{
		head->next->prev = NULL;
		head = head->next;
	}

	delete temp;
	elements--;
}

template <class T>
T& list<T>::front()
{
	return head->data;
}

template <class T>
T& list<T>::back()
{
	return tail->data;
}

template <class T>
bool list<T>::empty()
{
	if (elements == 0)
		return true;
	else
		return false;
}

template <class T>
list<T>::~list()
{
	Node<T> *temp, *temp1;

	temp = head;
	while (temp)
	{
		temp1 = temp;
		temp = temp->next;
		delete temp1;
	}
	head = tail = NULL;
	elements = 0;
}

template <class T>
void list<T>::clear()
{
	Node<T> *temp, *temp1;

	temp = head;
	while (temp)
	{
		temp1 = temp;
		temp = temp->next;
		delete temp1;
	}
	head = tail = NULL;
	elements = 0;

}

template <class T>
typename list<T>::iterator list<T>::begin() {
	return iterator(head);
}

template <class T>
typename list<T>::iterator list<T>::end() {
	return iterator(tail->next);
}

template <class T>
class List_iterator
{
	Node<T>* current;
public:
	List_iterator() :current(NULL) {}
	List_iterator(Node<T>* ptr) : current(ptr) {}
	typedef List_iterator<T> iterator;
	iterator operator = (iterator r);
	iterator operator ++ ();
	bool operator != (iterator r);
	T& operator * ();
};

template <class T>
List_iterator<T> List_iterator<T>::operator = (List_iterator<T> r)
{
	current = r.current;
	return *this;
}

template <class T>
bool List_iterator<T>::operator != (List_iterator<T> r)
{
	return !(current == r.current);
}

template <class T>
T& List_iterator<T>::operator* ()
{
	return current->data;
}

template <class T>
List_iterator<T> List_iterator<T>::operator++ ()
{
	current = current->next;
	return *this;
}

int current_minimum_cost = 99999999999;
list<int> tsp_solution;

// A - 0, B - 1, C - 2, D - 3, E - 4

void tsp(int **graph, list<int>& path, int total_cost, list<int>& remaining_cities, int final_city)
{
	int last_visited_city = path.back();

	if (total_cost > current_minimum_cost)
	{
		// abort, no point exploring this path
		return;
	}

	if (remaining_cities.empty())
	{
		// all cities have been visited
		// only add the distance back to the final city (salesman returns home)
		path.push_back(final_city);
		total_cost += graph[last_visited_city][final_city];

		if (total_cost < current_minimum_cost)
		{
			// we have a new winner
			current_minimum_cost = total_cost;
			tsp_solution.clear();
			tsp_solution = path;
		}
		return;
	}

	// calculate the new possibilities to travel to from the current city
	list<int>::iterator i;
	for (i = remaining_cities.begin(); i != remaining_cities.end(); ++i)
	{
		list<int> newPath;
		newPath = path;
		newPath.push_back(*i);

		int total_cost_new = total_cost + graph[last_visited_city][*i];

		// make a list of 'remaining cities' to visit
		list<int> newRemaining_cities;
		newRemaining_cities = remaining_cities;
		newRemaining_cities.remove(*i);

		tsp(graph, newPath, total_cost_new, newRemaining_cities, final_city);
	}
	return;
}


class Point {
	int x;
	int y;

public:
	Point() : x(0), y(0) {}
	Point(int x1, int y1) : x(x1), y(y1){}
	Point(Point& p) { x = p.x; y = p.y; }
	int getx(){ return x; }
	int gety(){ return y; }
};

int difference(Point a, Point b)
{
	int xa = a.getx();
	int ya = a.gety();

	int xb = b.getx();
	int yb = b.gety();

	int diffx, diffy;
	diffx = (xa>xb) ? xa - xb : xb - xa;
	diffy = (ya>yb) ? ya - yb : yb - ya;

	int result = diffx + diffy;

	return result;
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

	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int num_customers;
		cin >> num_customers;

		// Reset the current minimum cost for each iteration
		current_minimum_cost = 0x7FFFFFFF;

		int **graph;
		graph = new int*[num_customers + 2];
		for (int i = 0; i<num_customers + 2; i++)
		{
			graph[i] = new int[num_customers + 2];
		}

		Point* arr;
		arr = new Point[num_customers + 2];

		int x, y;

		cin >> x >> y;
		arr[0] = Point(x, y);

		cin >> x >> y;
		arr[num_customers + 1] = Point(x, y);

		for (int i = 1; i <= num_customers; i++) {
			cin >> x >> y;
			arr[i] = Point(x, y);
		}

		for (int i = 0; i<num_customers + 2; i++)
		{
			for (int j = 0; j<num_customers + 2; j++)
			{
				if (i == j)
				{
					graph[i][j] = 0;
					continue;
				}
				graph[i][j] = difference(arr[i], arr[j]);
			}
		}

		list<int> path; // would contain the final best path
		list<int> remaining_cities;
		//input all the cities to remaining cities except the starting city


		path.push_back(0);  //since we would start with node 0

		for (int i = 1; i <= num_customers; i++)
		{
			remaining_cities.push_back(i);
		}

		tsp(graph, path, 0, remaining_cities, num_customers + 1);


		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << current_minimum_cost << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}




/*

#include <iostream>
using namespace std;

class node
{
public:
	int data;
	node* next;
	node* prev;

	node(int d, node* n, node*p) : data(d), next(n), prev(p) {}
};

class list
{
public:
	node* head;
	node* tail;
	int elements;

	list() :elements(0), head(NULL), tail(NULL) {}
	list(list &l);
	void push_back(int val);
	int back();
	void pop_front();
	list& operator = (list& l);
	bool empty();
	~list();
	void remove(int val);
	void clear();
	void print();
};

void list::push_back(int val)
{
	node* temp = new node(val, NULL, tail);
	if (head == NULL)
		head = temp;
	if (tail != NULL)
		tail->next = temp;

	tail = temp;
	elements++;
}

int list::back()
{
	return tail->data;
}

void list::pop_front()
{
	node* temp = head;
	if (head == tail)
		head = tail = NULL;

	if (head && head->next)
	{
		head->next->prev = NULL;
		head = head->next;
	}
	elements--;
	delete temp;
}


list& list::operator = (list& l)
{
	node* temp;
	for (temp = l.head; temp != NULL; temp = temp->next)
		push_back(temp->data);

	return *this;
}

list::list(list &l)
{
	head = tail = NULL;
	elements = 0;
	node* temp;
	for (temp = l.head; temp != NULL; temp = temp->next)
		push_back(temp->data);
}

bool list::empty()
{
	return (elements == 0);
}

void list::remove(int val)
{
	node* temp;
	for (temp = head; temp != NULL; temp = temp->next)
	{
		if (temp->data == val)
		{
			if (head == temp)
				head = temp->next;

			if (tail == temp)
				tail = tail->prev;

			if (temp->prev)
				temp->prev->next = temp->next;
			if (temp->next)
				temp->next->prev = temp->prev;
			delete temp;
			elements--;
			break;
		}
	}
}

void list::clear()
{
	node *temp, *temp1;
	temp = head;
	while (temp)
	{
		temp1 = temp;
		temp = temp->next;
		delete temp1;
	}
	elements = 0;
	head = tail = NULL;
}

list::~list()
{
	clear();
}


void list::print()
{
	node* temp;
	for (temp = head; temp != NULL; temp = temp->next)
	{
		cout << temp->data << " ";
	}
	cout << endl;
}

int current_minimum_cost = 0x7FFFFFFF;
list tsp_solution;

void tsp(int** graph, list& path, int total_cost, list& remaining_cities, int final_city)
{
	int last_visited_city;
	last_visited_city = path.back();

	if (total_cost > current_minimum_cost)
		return;

	if (remaining_cities.empty())
	{
		path.push_back(last_visited_city);
		total_cost += graph[last_visited_city][final_city];
		if (total_cost < current_minimum_cost)
		{
			current_minimum_cost = total_cost;
			tsp_solution.clear();
			tsp_solution = path;
		}
		return;
	}

	int total_cost_new;
	node* temp;

	for (temp = remaining_cities.head; temp != NULL; temp = temp->next)
	{
		list new_path;
		list new_remainig_cities;
		int i;
		i = temp->data;
		//new_path.clear();
		new_path = path;
		new_path.push_back(i);

		total_cost_new = total_cost + graph[last_visited_city][i];

		//new_remainig_cities.clear();
		new_remainig_cities = remaining_cities;
		new_remainig_cities.remove(i);

		////////////////////////////////////////
	
		cout << "path is: ";
		path.print();

		cout << "new_path is: ";
		new_path.print();

		cout << "remaining_cities is: ";
		remaining_cities.print();

		cout << "new_remainig_cities is: ";
		new_remainig_cities.print();

		cout << endl;

		/////////////////////////////////////////
		tsp(graph, new_path, total_cost_new, new_remainig_cities, final_city);
	}
}

class Point{
	int x;
	int y;

public:
	Point() : x(0), y(0) {}
	Point(int x1, int y1) : x(x1), y(y1){}
	Point(Point& p) { x = p.x; y = p.y; }
	int getx(){ return x; }
	int gety(){ return y; }
};

int difference(Point a, Point b)
{
	int xa = a.getx();
	int ya = a.gety();

	int xb = b.getx();
	int yb = b.gety();

	int diffx, diffy;
	diffx = (xa>xb) ? xa - xb : xb - xa;
	diffy = (ya>yb) ? ya - yb : yb - ya;

	int result = diffx + diffy;

	return result;
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
	cin >> T;

	/*
	Read each test case from standard input.
	*/
	for (test_case = 1; test_case <= T; ++test_case)
	{
		int num_customers;
		cin >> num_customers;

		// Reset the current minimum cost for each iteration
		current_minimum_cost = 0x7FFFFFFF;

		int **graph;
		graph = new int*[num_customers + 2];
		for (int i = 0; i<num_customers + 2; i++)
		{
			graph[i] = new int[num_customers + 2];
		}

		Point* arr;
		arr = new Point[num_customers + 2];

		int x, y;

		cin >> x >> y;
		arr[0] = Point(x, y);

		cin >> x >> y;
		arr[num_customers + 1] = Point(x, y);

		for (int i = 1; i <= num_customers; i++) {
			cin >> x >> y;
			arr[i] = Point(x, y);
		}

		for (int i = 0; i<num_customers + 2; i++)
		{
			for (int j = 0; j<num_customers + 2; j++)
			{
				if (i == j)
				{
					graph[i][j] = 0;
					continue;
				}
				graph[i][j] = difference(arr[i], arr[j]);
			}
		}

		list path; // would contain the final best path
		list remaining_cities;
		//input all the cities to remaining cities except the starting city


		path.push_back(0);  //since we would start with node 0

		for (int i = 1; i <= num_customers; i++)
		{
			remaining_cities.push_back(i);
		}

		tsp(graph, path, 0, remaining_cities, num_customers + 1);


		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << current_minimum_cost << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}

*/