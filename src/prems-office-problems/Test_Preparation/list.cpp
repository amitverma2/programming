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