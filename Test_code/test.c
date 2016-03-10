#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	printf("Coding in C\n");

	struct node
	{
		int data;
		struct node* next;
	};

	struct node* head;
	struct node* curr;
	head = (struct node*) malloc(sizeof(struct node));
	//head->data=11;
	curr = head;
	int i;
	for (i=0; i<5; i++)
	{
		curr -> data = i;
		printf("\nThis is the %dth node & its value is %d.", i, curr->data);
		curr -> next = (struct node*) malloc(sizeof(struct node));
		curr = curr -> next;
		curr->data = 11 + i + 1;
		curr->next = NULL;
	}
//	curr -> next = NULL;

	return 0;
}

