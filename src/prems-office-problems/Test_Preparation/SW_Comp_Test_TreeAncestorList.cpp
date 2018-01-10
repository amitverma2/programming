#include<iostream>

using namespace std;
#define NULL 0

class list
{
	struct node {
		int data;
		struct node* next;
		struct node* prev;
		node(int data1, node* next1, node* prev1): data(data1), next(next1), prev(prev1) {}
	};
	node* head;
	node* tail;
	int elements;

public: 
	list():head(NULL), tail(NULL), elements(0) {}
	void push_back(int value);
	int front();
	void pop_front();
	bool empty();
	~list();
};

list::~list()
{
	node *temp, *temp1;
	temp = head;
	while(temp)
	{
		temp1 = temp;
		temp = temp->next;
		delete temp1;
	}
	elements = 0;
	head = NULL;
	tail = NULL;
}

void list::push_back(int value)
{
	node* temp = new node(value, NULL, tail);
	if(head == NULL)
		head = temp;
	if(tail!=NULL)
		tail->next = temp;
	tail = temp;
	elements++;
}

int list::front()
{
	return head->data;
}

void list::pop_front()
{
	node* temp = head;
	if(tail == head)
		tail = head = NULL;
	if(temp->next != NULL)
	{
		temp->next->prev = NULL;
		head = temp->next;
	}
	delete temp;
	elements--;
}

bool list::empty()
{
	return (elements == 0);
}


class Graph {
	int V;
	int* parent;
	int** child;
public:
	Graph(int V);
	int findAncestor(int v1, int v2);
	int bfs(int s);
	void addEdge(int u, int v);
	void print_parent(int v);
	~Graph();
};

Graph::Graph(int num)
{
	V = num;
	parent = new int[V];
	child = new int*[V];

	for(int i=0; i<V; i++)
	{
		parent[i] = -1;
		child[i] = new int[2];
		child[i][0] = child[i][1] = -1;
	}
}

void Graph::addEdge(int u, int v)
{
	int temp;

	parent[v] = u;
	if(child[u][0] == -1)
		child[u][0] = v;
	else
		child[u][1] = v;
}

Graph::~Graph()
{
	for(int i=0; i<V; i++)
		delete[] child[i];
	delete[] child;
	delete[] parent;
}

class Array
{
public:
	int pos;
	int *arr;
	Array(int n);
	void push(int n);
	~Array();
	int pop();
};

Array::Array(int n)
{
	pos = 0;
	arr = new int[n];
}

void Array::push(int n)
{
	arr[pos++] = n;
}

int Array::pop()
{
	return arr[--pos];
}

Array::~Array()
{
	pos = -1;
	delete[] arr;
}

int Graph::findAncestor(int v1, int v2)
{
	Array a1(V);
	Array a2(V);
	do
	{
		a1.push(v1);
		v1 = parent[v1];
	} while (v1 != -1);

	do
	{
		a2.push(v2);
		v2 = parent[v2];
	} while (v2 != -1);

	while(a1.pop() == a2.pop());
	return a1.arr[++(a1.pos)];
}

int Graph::bfs(int s)
{
	list q;
	int count = 0;
	int u;

	q.push_back(s);

	while(!q.empty())
	{
		u = q.front();
		q.pop_front();
		count++;

		if(child[u][0] != -1)
		{
			q.push_back(child[u][0]);
			if(child[u][1] != -1)
			{
				q.push_back(child[u][1]);
			}
		}

	}
	return count;
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

	Graph* g;
	int V;
	int E;
	int vertex1;
	int vertex2;
	int u,v;
	int parent;
	int number;
    /*
	Read each test case from standard input.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> V >> E >> vertex1 >> vertex2;
		vertex1--;
		vertex2--;

		g = new Graph(V);
		for(int i=0; i<E; i++)
		{
			cin >> u >> v;
			u--; v--;
			g->addEdge(u,v);
		}

		parent = g->findAncestor(vertex1, vertex2);
		number = g->bfs(parent);
		delete g;

		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << parent+1 << " " << number << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}