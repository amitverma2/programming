#include <stdio.h>
#include <stdlib.h>

//# define NULL (void *)0
struct node {
    int data;
	struct node* link;
};

/*
struct dlist {
	int data;
    struct node* prev;
	struct node* next;
};

struct tree {
	int data;
	struct tree* left;
	struct tree* right;
};
*/

void insert (struct node **head, int num)
{
	struct node* temp = (struct node*) malloc(sizeof(struct node));
	temp->data = num;
	temp->link = *head;
	*head = temp;
}

void display(struct node* head)
{
	while(head != NULL)
	{
		printf("%d ", head->data);
		head = head->link;
	}
}

void remove(struct node** head)
{
	struct node *temp = *head;
	struct node *temp1 = NULL;;

	while(temp!=NULL)
	{
		temp1 = temp->link;
		free(temp);
		temp = temp1;
	}
	*head = NULL;
}

void removeLoop(struct node* head, struct node* ptr)
{
	struct node* temp;
	temp = head;

	struct node* ptr1;
	// One pointer starts from the beginning of list while other pointer starts from where slow and fasr ptr met
	while(temp != ptr)
	{
		temp = temp->link;
		ptr1 = ptr;
		ptr = ptr->link;
	}

	// ptr1 shoukd be the node which is causing the cycle, make its link to NULL to stop the cycle
	ptr1->link = NULL;
}

int detectAndRemoveLoop(struct node* head)
{
	struct node* fast_ptr;
	struct node* slow_ptr;

	slow_ptr = fast_ptr = head;

	while(slow_ptr && fast_ptr && fast_ptr->link)
	{
		slow_ptr = slow_ptr->link;
		fast_ptr = fast_ptr->link->link;

		if(slow_ptr == fast_ptr) {
			removeLoop(head, slow_ptr);
			return 1;
		}
	}
	return 0;
}

int main()
{
	struct node* head = NULL;
	insert(&head, 80);
	insert(&head, 70);
	insert(&head, 60);
	insert(&head, 50);
	insert(&head, 40);
	insert(&head, 30);
	insert(&head, 20);
	insert(&head, 10);

	display(head);

	printf("\nPresence of cycle %d \n", detectAndRemoveLoop(head));

	head->link->link->link->link->link->link->link->link = head->link->link->link;
    //head->link->link->link->link->link->link->link->link = head;


	printf("Presence of cycle %d \n", detectAndRemoveLoop(head));

	display(head);

	remove(&head);

	getchar();
	return 0;
}