#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Defining the structure
struct node
{
	int data;
	struct node* next;
};

struct node* head = NULL;
struct node* curr = NULL;

int num=0;

// Function Declarations
void create_list();
void add_to_list(int);
void display_list();
int elem_count();
void search_list(int);
void del_from_list(int);
void insert_elem(int,int);

// Main function
void main(int argc, char *argv[])
{
	int n;
	create_list();
	for (n=0; n<6; n++)
	{
		add_to_list(n+1);
	}
	display_list();
	search_list(3);
	del_from_list(3);
	display_list();
	insert_elem(12,3);
	display_list();
}

// Create List
void create_list()
{
	if (head==NULL)
	{
		head = (struct node*) malloc(sizeof(struct node));
		curr = head;
		head -> data = num;
	}
}

// Elem count
int elem_count()
{
	struct node* ptr = head;
	int ctr=0;
	while (ptr->next!=NULL)
	{
		ctr++;
		ptr = ptr->next;
	}

	return ctr;
}


// Adding elements to the list
void add_to_list(int n)
{
	curr->data=n;
	num++;
	curr->next=(struct node*) malloc(sizeof(struct node));
	curr = curr -> next;
	curr -> next = NULL;
}

// Displays the elements in the list

void display_list()
{
	printf("\n");
	struct node* ptr = head;
	int num_link =0;
	while (ptr -> next !=NULL)
	{
		printf("The %dth node has a value of %d\n",num_link, ptr->data);
		ptr = ptr->next;
		num_link++;
	}
}

// Search for Element 'n' in the linked list
void search_list(int n)
{
	struct node* ptr= head;
	int num_link = 0;
	while (ptr-> next != NULL)
	{
		if (ptr->data == n)
		{
			printf("\nElement at %dth location", num_link);
			break;
		}
		num_link++;
		ptr = ptr->next;
	}
}

// Deleting an element from the list
void del_from_list(int n)
{
	struct node* ptr = head;
	while (ptr->next != NULL)
	{
		if (ptr-> next-> data == n)
		{
			ptr -> next = ptr -> next -> next;
		}
		ptr = ptr-> next;
	}
}

// Inserting an element n in location number 'n'
void insert_elem(int n, int pos)
{
	struct node* ptr = head;
	int num_link=0;
	struct node* temp = NULL;
	while (ptr->next!=NULL)
	{
		if (pos > elem_count())
		{
			printf("Cannot Insert at that position");
			break;
		}
		else
		{
			if (pos == num_link)
			{
				temp = (struct node*) malloc(sizeof(struct node));
				temp -> next = ptr->next;
				temp -> data = n;
				ptr -> next = temp;
			}
		
			
		}
		num_link++;
		ptr = ptr->next;
	}
}
