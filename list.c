#include <stdio.h>
#include <stdlib.h>

#define MAX_INTS 1000

/* A node in the linked list */
struct node {
    int data;
    struct node *next;
};

//Function Declarations:
struct node* create_list(int intarray[], int len);

struct node* add_item_at_start(struct node *head, int data);

int search_array(int integers[], int numints, int element);

int search_list(struct node *head, int element);

struct node* create_sorted_list(struct node *head);

struct node* add_item_sorted(struct node *head, int data);

int copy_list_to_array(struct node *head, int *array);

void print_list(struct node *head);

void print_array(int integers[], int len);


int main(int argc, char *argv[]){
    /* TODO: Complete the main method according to the steps outlined */

    /* Open a file for reading */
    FILE *file=fopen("numbers.txt","r");    //
    
    if(file==NULL){
        printf("Error opening file!\n");
        return 1;
    }

    /* Read the numbers from the file, into an array */
    int num = 0;   //number count
    int arr[MAX_INTS];   //arr as a container to save the numbers from the file that read
    // int *ptr = arr;      // ptr points to the frist element of the arr
			
    // when pinter count less than the lenth of the arr 
    // and scan the file until arr[num] = EOF then exit
    while(num <MAX_INTS && fscanf(file,"%d",&arr[num])!=EOF){  //EOF means EndOfFile
        //process the integer
	num++;
    }
    fclose(file);

    /* Print the array */
    printf("Original Array: \n");
    print_array(arr,num);

    /* Create a linked list with the integers from the array */
    struct node *head = create_list(arr, num);
    
    /* Print the linked list */
    printf("Original Linked List: \n");
    print_list(head);

    /* Repeatedly prompt the user for a number to be searched.
    *  Search the array for the number and print out the result as shown in the specs.
    *  Search the linked list for the number and print out the result as shown in the specs.
    *  Stop prompting when the user enters 'q' (just the character q without the single quotes).
    */
    char user_input[1000];
    //use while(1) to repeat the loop letting user put a number to be searched
    while(1){
        printf("Enter a number to search (or 'q' to quit): ");
	scanf("%s",user_input);
   
	if(user_input[0]=='q' && user_input[1]=='\0'){
	   break;
	}

	int num = atoi(user_input);              //convert input to int
	int index = search_array(arr,num,num);   // search in arr
	int position = search_list(head,num);    //search in linked list
	
	if(index != -1 || position!=-1){
	    printf("Found %d in array at index %d\n", num, index);
	    printf("Found %d in linked list at position %d\n", num, position);
	}else{
	    printf("%d not found in array \n",num);
	    printf("%d not found in linked list \n",num);
	}
    }

    /* Create a sorted list(in ascending order) from the unsorted list */
    struct node *sorted_head = create_sorted_list(head);
    /*Print the sorted list */
    printf("Sorted Linked List:\n");
    print_list(sorted_head);

    /*Copy the sorted list to an array with the same sorted order*/
    int sorted_arr[MAX_INTS];
    int sorted_count = copy_list_to_array(sorted_head, sorted_arr);

    /*print out the sorted array */
    printf("Sorted Array:\n");
    print_array(sorted_arr, sorted_count);

    /*print the original linked list again */
    printf("Original Linked List Again:\n");
    print_list(head);

    /* print the origianl array again */
    printf("Original Array Again:\n");
    print_array(arr,num);

    /* Open a file for writing */
    FILE *sorted_file = fopen("sorted_numbers.txt", "w");
    if(sorted_file == NULL){
        printf("Error opening file for writing!\n");
	return 1;
    }

    /* write the sorted array to a file named "sorted_numbers.txt" */
    for(int i=0; i<sorted_count; i++){
        fprintf(sorted_file, "%d\n", sorted_arr[i]);
    }
    fclose(sorted_file);

    /*print out the number of integers written to the file */
    printf("Wrote %d numbers to sorted_number.txt\n", sorted_count);

    return 0;
}


    struct node* create_list(int intarray[],int len){
        struct node *head = NULL;
	struct node *tail = NULL;
	for(int i=0; i<len; i++){
	    struct node *new_node = (struct node*)malloc(sizeof(struct node));
	    new_node->data = intarray [i];    
	    new_node->next = NULL;

	    if(head == NULL){
	        head = new_node;
		tail = new_node;
	    }
	    else{
	        tail->next = new_node;
		tail = new_node;
	    }
	}
	return head;
    
    }
    
    //each new item is added to the start of the list, returns a pointer to the head
    struct node* add_item_at_start(struct node *head, int data){

	struct node *new_node = (struct node*)malloc(sizeof(struct node));

	new_node->data = data;

	new_node->next = head;

	return new_node;

    }
  
    int search_list(struct node *head, int element){
        struct node *temp = head;
	int index = 1;
	while (temp != NULL){
	    if(temp->data == element){
	        return index;
	    }
	    temp = temp->next;
	    index++;
	}
	return -1;         //if not found
    }
    
    int search_array(int integers[],int numints, int element){
        for(int i =0; i< numints; i++){
	    if(integers[i]==element){
	        return i;
	    }
	}
	return -1; //if not found
    }

    int copy_list_to_array(struct node *head, int *array){
        int count = 0;
	struct node *temp = head;
	while(temp != NULL){
	    array[count++] = temp->data;
	    temp = temp->next;
	}
	return count;
    }

    struct node* create_sorted_list(struct node *head){
        struct node *sorted_head = NULL;
	struct node *curr = head;

	while(curr != NULL){
	    sorted_head = add_item_sorted(sorted_head, curr->data);
	    curr = curr->next;
	}
	return sorted_head;
    }

struct node* add_item_sorted(struct node *sorted_head, int data){
        struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;

	if(sorted_head == NULL || sorted_head->data >= data){
	    new_node->next = sorted_head;
	    return new_node;
	}

	struct node *curr = sorted_head;
	while(curr->next != NULL && curr->next->data < data){
	    curr = curr->next;
	}
	new_node->next = curr->next;
	curr->next = new_node;


	return sorted_head;
}

void print_list(struct node *head){
    if(head==NULL){
        printf("Linked List is Empty.\n");
    }else{
        struct node *temp = head;
        printf("head->");
        while (temp != NULL) {
            printf("|%d|->", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void print_array(int integers[], int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("| %d ", integers[i]);
    }
    printf("|\n");
}
