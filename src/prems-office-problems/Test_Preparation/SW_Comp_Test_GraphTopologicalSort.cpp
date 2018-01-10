/////////////////////////////////////////////////////////////////////////////////////////////
// Standard Input
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            
// cin >> b >> c;                       
// cin >> d >> e >> f;                  
// cin >> g;                            
// cin >> var;                          
// cin >> AB;                           
/////////////////////////////////////////////////////////////////////////////////////////////
// Standard Output
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           
// cout << b << " " << c;               
// cout << d << " " << e << " " << f;   
// cout << g;                           
// cout << var;                         
// cout << AB;                          
/////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>

using namespace std;

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
	int back();
	void pop_back();
	bool empty();
};

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

int list::back()
{
	return tail->data;
}

void list::pop_back()
{
	node* temp = tail;
	if(tail == head)
		tail = head = NULL;
	if(temp->prev != NULL)
	{
		temp->prev->next = NULL;
		tail = temp->prev;
	}
	delete temp;
	elements--;
}

bool list::empty()
{
	return (elements == 0);
}


void getOrderUtil(int **g, int V, int s, list& stack, bool* visited)
{
	visited[s] = true;

	for(int v=0; v<V; v++)
	{
		if(g[s][v] == 1)
		{
			if(!visited[v])
				getOrderUtil(g, V, v, stack, visited);
		}
	}
	stack.push_back(s);
}

void getOrder(int **g, int V, list& stack)
{
	bool* visited;

	visited = new bool[V];

	for(int i=0; i<V; i++)
		visited[i] = false; // none are visited;

	for(int i=0; i<V; i++)
		if(!visited[i])
			getOrderUtil(g, V, i, stack, visited);
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
	T = 10;

	/*
	   Read each test case from standard input.
	*/

	int **g;
	int V, E;
	int u,v;
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> V >> E;
		g = new int* [V];
		for(int i=0; i<V; i++)
		{
			g[i] = new int[V];
			for(int j=0;j<V;j++)
				g[i][j] = -1;
		}

		for(int i=0; i<E; i++)
		{
			cin >> u >> v;
			u--; v--;
			g[u][v] = 1;
		}

		list stack;
		getOrder(g, V, stack);



		// Print the answer to standard output(screen).
		cout << "#" << test_case;
		while(!stack.empty() )
		{
			cout << " " << stack.back()+1;
			stack.pop_back();
		}

		cout << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}