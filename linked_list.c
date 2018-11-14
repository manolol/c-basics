/* reference: https://www.learn-c.org/en/Linked_lists */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int val;
	struct node *next;
} node_t;

void print_list(node_t *head){
	node_t *current = head;

	while(current != NULL){
		printf("%d\n", current->val);
		current = current->next;
	}

}

// add an item to the end of the list
void add(node_t *head, int val){
	node_t *current = head;

	while(current->next != NULL){
		current = current->next;
	}

	current->next = malloc(sizeof(node_t));
	current->next->val = val;
	current->next->next = NULL;

}

/* add an item to the beginning of the list
1. Create a new item and set its value
2. Link the new item to point to the head of the list
3. Set the head of the list to be our new item */
void push(node_t **head, int val){ // double pointer to modify head (that it's a pointer itself)
	node_t *new_node;
	new_node = malloc(sizeof(node_t));

	new_node->val = val;
	new_node->next = *head;
	*head = new_node;
}

/* remove the first item
1. Take the next item that the head points to and save it
2. Free the head item
3. Set the head to be the next item that we've stored on the site */
int pop(node_t **head){
	int retval = -1;
	node_t *next_node = NULL;

	if(*head == NULL){
		return -1;
	}

	next_node = (*head)->next;
	retval = (*head)->val;
	free(*head);
	*head = next_node;

	return retval;
}

// remove the last item of the list
int remove_last(node_t *head){
	int retval = 0;

	node_t *current = head;

	// if there is only one item in the list, remove it
	if(head->next == NULL){
		retval = head->val;
		free(head);
		return retval;
	}

	// get to the second to last node in the list (minus 1 step)
	while(current->next->next != NULL){
		current = current->next;
	}

	// now current points to the last item of the list, so let's remove it
	retval = current->next->val;
	free(current->next);
	current->next = NULL;
	return retval;
}

// removing a specific item
int remove_by_index(node_t **head, int n){
	int i = 0;
	int retval = -1;

	node_t *current = *head;
	node_t *temp_node = NULL;

	// if the selected index is equal to 0
	if (n == 0){
		return pop(head);
	}

	for(i = 0; i < n-1; i++){
		// the index is out of the range of the list
		if(current->next == NULL){
			return -1;
		}
		current = current->next;
	}

	retval = current->next->val;

	temp_node = current->next;
	current->next = current->next->next;
	free(temp_node);

	return retval;
}

int remove_by_value(node_t **head, int val){
	int retval = -1;
	node_t *current = *head;
	node_t *temp_node = NULL;

	// if the value is at the head
	if(current->val == val){
		retval = pop(head);
	}

	while(current->next != NULL && current->next->val != val){
		current = current->next;
	}

	if(current->next != NULL && val == current->next->val){
		retval = current->next->val;
		temp_node = current->next;
		current->next = current->next->next;
		free(temp_node);
	}

	return retval;
}

int main(int narg, char *argv[]){

	int val;

	// create a head that points to the first node
	node_t *head = NULL;

	// test if the list is empty
	/*
	if(head == NULL){
		return 1;
	}
	*/

	// node 1
	head = malloc(sizeof(node_t));
	head->val = 1;
	head->next = NULL;

	// node 2
	head->next = malloc(sizeof(node_t));
	head->next->val = 2;
	head->next->next = NULL;

	// node 3
	head->next->next = malloc(sizeof(node_t));
	head->next->next->val = 3;
	head->next->next->next = NULL;

	// node 4
	add(head, 4);

	// node 5
	add(head, 5);

	// node 6
	push(&head, 6);

	print_list(head);

	// pop first node
	val = pop(&head);
	printf("Removed value: %d\n", val);
	printf("New list:\n");
	print_list(head);

	// remove last item
	val = remove_last(head);
	printf("Removed value: %d\n", val);
	printf("New list:\n");
	print_list(head);

	// remove a node at a specific index
	val = remove_by_index(&head, 2);
	printf("Removed value: %d\n", val);
	printf("New list:\n");
	print_list(head);

	// remove a node which has a specific value
	val = remove_by_value(&head, 1);
	printf("Removed value: %d\n", val);
	printf("New list:\n");
	print_list(head);

	return EXIT_SUCCESS;
}
