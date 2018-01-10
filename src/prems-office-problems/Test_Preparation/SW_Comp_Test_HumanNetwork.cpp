#include<iostream>

using namespace std;

#define MAX_INT 0x7FFFFFFF

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


int bfs(int** g, int V, int u)
{
	int* dist;
	int count = 0;
	bool* visited;
	visited = new bool[V];
	dist= new int[V];

	for(int i=0; i<V; i++)
	{
		dist[i] = MAX_INT;   // this should have been 0, if the graph is disconnected, it may cause some issue
		visited[i] = false;
	}

	dist[u] = 0;

	list q;
	q.push_back(u);
	visited[u] = true;

	while(!q.empty())
	{
		u = q.front();
		q.pop_front();

		for(int v=0; v<V; v++)
		{
			if(g[u][v] == 1 && visited[v] == false)
			{
				visited[v] = true;
				q.push_back(v);
				dist[v] = dist[u] + 1;
			}
		}
	}

    for(int i=0; i<V; i++)
	{
		count += dist[i];
	}

	delete[] visited;
	delete[] dist;

	return count;
}



int findDist(int**g, int V)
{
	int new_dist;
    int current_node = -1;
	int current_max_distance = MAX_INT;

	for(int u=0; u<V; u++)
	{
		new_dist = bfs(g, V, u);
		if(new_dist < current_max_distance)
		{
			current_max_distance = new_dist;
			current_node = u;
		}
	}
	return current_max_distance;
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

		g = new int* [V];
		for(int i=0; i<V; i++)
			g[i] = new int [V];

		for(int i=0; i<V; i++)
		{
			for(int j=0; j<V;j++)
			{
				cin >> u;
				g[i][j] = u;
			}
		}

		distance = findDist(g, V);
		for(int i=0; i<V; i++)
			delete[] g[i];
		delete[] g;

		// Print the answer to standard output(screen).
		cout << "#" << test_case << " " << distance << endl;
	}
	return 0;//Your program should return 0 on normal termination.
}