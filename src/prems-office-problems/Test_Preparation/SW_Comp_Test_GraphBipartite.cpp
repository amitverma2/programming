#include<iostream>

using namespace std;

class node
{
public:
	int data;
	node* next;
	node* prev;
	node(int data1, node* next1, node* prev1):data(data1), next(next1), prev(prev1){}
};


class list
{
	node* head;
	node* tail;
	int elements;

public:
	list():head(NULL), tail(NULL), elements(0) {}
	void push_back(int val);
	int front();
	void pop_front();
	bool empty();
	~list();
};

list::~list()
{
	node* temp, *temp1;
	temp = head;
	while(temp)
	{
		temp1 = temp->next;
		delete temp;
		temp = temp1;
	}
	elements = 0;
}

void list::push_back(int data)
{
	node* temp = new node(data, NULL, tail);
	if(head == NULL)
		head = temp;

	if(tail != NULL)
		tail->next = temp;

	tail = temp;
	elements++;
}

void list::pop_front()
{
	node* temp = head;

	if(head == tail)
		head = tail = NULL;

	if(head && head->next)
	{
		head->next->prev = NULL;
		head = head->next;
	}
	delete(temp);
	elements--;
}

int list::front()
{
	return head->data;
}

bool list::empty()
{
	return (elements == 0);
}


bool isBipartiteUtil(int** g, int V, int u, int* color)
{
	if(color[u] != -1)
		return true;

	list q;
	color[u] = 1;
	q.push_back(u);

	while(!q.empty())
	{
		u = q.front();
		q.pop_front();

		for(int v=0; v<V; v++)
		{
			if( g[u][v] == 1 )
			{
				if(color[v] == -1)
				{
					color[v] = 1-color[u];
					q.push_back(v);
				}
				else if(color[v] == color[u])
					return false;
			}
		}
	}
	return true;
}

bool isBipartite(int** g, int V, int* color)
{
	for(int i =0; i<V; i++)
	{
		if(!isBipartiteUtil(g, V, i, color))
			return false;
	}
	return true;
}


int main(int argc, char** argv)
{
	int test_case;
	int **g;
	int V, E;

	freopen("input.txt", "r", stdin);

	for(test_case = 1; test_case <= 10; ++test_case)
	{
		int i;

		/*
		read test case from stdin
		number of vertex is V, number of edge is E
		ith edge value contains E1[i] and E2[i]
		*/

		cin >> V >> E;
		g = new int*[V];
		for(int i=0;i<V;i++)
			g[i] = new int[V];

		for(int i=0; i<V;i++)
		{
			for(int j =0; j<V; j++)
				g[i][j] = 0;
		}

		int u, v;


		for(i = 0; i < E; i++)
		{
			cin >> u >> v;
			--u; --v;
			g[u][v] = 1;
			g[v][u] = 1;
		}

		int* color;
		color = new int[V];
		for(int i=0; i<V;i++)
			color[i] = -1;

		bool find;
		find = isBipartite(g, V, color);
		int total;
		total = 0;

		if(find)
		{
			cout << "#" << test_case;
			for(int i=0; i<V; i++)
			{
				if(color[i] == 1)
					total++;
			}
			cout << " " << total;
			for(int i=0; i<V; i++)
			{
				if(color[i] == 1)
					cout << " " << i+1;
			}
		}
		else
		{
			cout << "#" << test_case << " " << -1;
		}
		cout << endl;
		delete[] color;
		for(int i=0; i<V; i++)
			delete[] g[i];
		delete[] g;
	}

	return 0;		//0 return if it terminated normally
}