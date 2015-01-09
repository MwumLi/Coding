#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "use_list_h.h"

int main(int argc, char **argv) 
{
	int choose=1;
	int insert=1;
	int delete=1;
	int find=1;

	
	List_Node *list=NULL;
	List_Node *new;
	int	data;
	int key;	
	int index;

	while(1) {
		system("clear");
	Choose_Label:
		printf("[1]-->Init list\n");
		printf("[2]-->Destory list\n");
		printf("[3]-->Insert a node\n");
		printf("[4]-->Remove a node\n");
		printf("[5]-->Find a node\n");
		printf("[6]-->Sum\n");
		printf("[7]-->Dsiplay List\n");
		printf("[0]-->quit\n");
		printf("Make your choose:");
		scanf("%d", &choose);
		switch(choose) {
			case 1: {
				if(list == NULL) 
					list = (List_Node *)malloc(sizeof(List_Node));
				else
					destory_List(list);
				init_List(list);
				Node_Number = 0;
				printf("Init successfully\n");
				}//case 1
				break;
			case 2: {
				if(list == NULL) {
					printf("Cann't destory,Please init first\n");
					goto Choose_Label;
				}
			
				destory_List(list);
				free(list);
				list=NULL;
				printf("Destroy successfully!\n");
				}	
				break;
			case 3: {	
				if(list == NULL) {
					printf("Cann't insert,Please init first\n");
					goto Choose_Label;
				}

				printf("Enter the data:");
				scanf("%d", &data);
				new = make_node(data);
			Insert_Label:	
				printf("[1] insert the node after the tail\n");
				printf("[2] insert the node after the head\n");
				printf("[3] insert the node after 'key' node\n");
				printf("Do your choose:");
				scanf("%d", &insert);
				switch(insert) {
					case 1:
						insert_tail_List(new, list);
						break;
					case 2:
						insert_head_List(new, list);
						break;
					case 3:
					Insert_Key:
						printf("Enter the key:");
						scanf("%d", &key);
						if( insert_key_List(key, new, list) != 0) {
							printf("Insert failed, no this key node\n");
							goto Insert_Key;
						}
						break;
					default:
						printf("Error:Enter choose!\n")	;
						goto Insert_Label;
				}//end switch(insert)
				}//case 3
				printf("Insert successfully\n");


				break;
			case 4:	{	
				if(list == NULL) {
					printf("Cann't delete,Please init first\n");
					goto Choose_Label;
				}

			Delete_Label:
				printf("[1]Delete 'key' node\n");
				printf("[2]Delete 'index' node\n");
				printf("Do your choose:");
				scanf("%d", &delete);
				switch(delete) {
					case 1:
					Delete_Key:
						printf("Enter the 'key':");
						scanf("%d", &key);
						if( !remove_key_List(key, list) ) {
							printf("Delete failed, no this key node\n");
							goto Delete_Key;
						}
						break;
					case 2:
					Delete_Index:
						printf("Enter the 'index'(0-%d)\n", 
							Node_Number-1);
						scanf("%d", &index);
						if( !remove_index_List(index, list) ) {
							printf("Delete failed, no this index\n");
							goto Delete_Index;
						}
					 break;
				default:
					printf("Error:Enter choose!\n");
					goto Delete_Label;
				} //end seitch(delete)
				}//case 4
				printf("Delete successfully!\n");
				break;
			case 5:{	
				if(list == NULL) {
					printf("Cann't find,Please init first\n");
					goto Choose_Label;
				}

			Find_Label:
				printf("Enter the 'index'(0-%d):", Node_Number-1);
				scanf("%d", &index);
				new = find_index_List(index, list);
				if( new == NULL) {
					printf("Find failed,no this index\n");
					goto Find_Label;
				}
				}//case 5
				printf("Find it successfully\nThe data:%d\n", 
					new->data);
				break;
			case 6: {
				if(list == NULL) {
					printf("Cann't sum,Please init first\n");
					goto Choose_Label;
				}

				if( !does_empty_List(list) ) {
					printf("Empty list\n");
					break;
				}
				data = sum_List(list);
				new = make_node(data);
				insert_tail_List(new, list);
				}//case 6
				printf("The sum: %d\n", data);
				printf("Inserted the data node\n");
				break;
			case 7: {	
				if(list == NULL) {
					printf("Cann't display,Please init first\n");
					goto Choose_Label;
				}

				printf("The list:\n");
				display_List(list);
				}//case 7
				break;
			case 0:
				if(list !=  NULL) {
					destory_List(list);
					free(list);
				}
				return 0; //end case 0
			default:
				printf("Error:Enter choose!\n");
				goto Choose_Label;
				
		}//end switch(choose)	
		printf("Press any key to return Home Page\n");
		getchar();
		getchar();
	}
}

/*
 * init_List - init a list
 * @list: a List_Node list head pointer
 * 
 * Init a empty list
 * */

void	init_List(List_Node * list)
{
	list->data = 0;
	INIT_LIST_HEAD(&(list->p_field));
}
/*
 * destory_List - destory a list
 * @list: a List_Node list head pointer
 * 
 * Remove the all nodes and free them except the head node
 * */
void	destory_List(List_Node *list)
{
        struct list_head *pos;
		struct list_head *temp;
        List_Node *cur_list;
		
	//for(pos=head->next; pos!=head; pos=pos->next)
        list_for_each(pos, &(list->p_field)) {
	
            cur_list = list_entry(pos, List_Node, p_field);
			temp = pos->prev;
            list_del(pos);  //remove the node
            free(cur_list); //free space
			pos = temp;
        }
}
/*
 * make_node - make a node
 * @data: int varible
 *
 * Alloc a List_Node space to make the node,
 * which the data field is 'data'.
 * */
List_Node	*make_node(int data)
{
	List_Node *new = (List_Node *)malloc(sizeof(List_Node));
	new->data = data;
	struct list_head *new_head = &(new->p_field);
	new_head->prev = NULL;
	new_head->next = NULL;
	return new;
}
/*
 * free_node - free a node
 * @node: the node to destory
 *
 * Free the 'node' node
 * If 'node' is NULL, return -1
 * If remove successfully, return 0
 * */
int	free_node(List_Node *node)
{
	if(node == NULL)
		return -1;
	free(node);
	return 0;
}

/*
 * find_key_List - find the node
 * @key: the key word of the node to find
 * @list: the head of the list which you'll find the key node
 *
 * Find the key node which data field is 'key' in 'list'
 * Find it, return the key node
 * or, return NULL
 **/
List_Node 	*find_key_List(int key, List_Node *list)
{
	struct list_head *pos;
	List_Node *cur_list;
	
	list_for_each(pos, &(list->p_field))	{
		cur_list = list_entry(pos, List_Node, p_field);
		if(cur_list->data == key) {
			return cur_list;
		}
	}
	return NULL;
}
/*
 * find_index_List - find the node
 * @index: the index word of the node to find
 * @list: the head of the list which you'll find the key node
 *
 * Find the 'index' node in 'list'
 * Find it, return the 'index' node
 * or, return NULL
 **/
List_Node 	*find_index_List(int index, List_Node *list)
{
	int count = 0;
	struct list_head *pos;
	List_Node *cur_list;

	list_for_each(pos, &(list->p_field)) {
		if(count == index) {
			cur_list = list_entry(pos, List_Node, p_field);
			return cur_list;
		}
		count++;
	}
	return NULL;
}
/*
 * insert_tail_List - add a new node
 * @new: the node to be inserted
 * @list: the list which the 'new' node will be inserted in
 *
 * Add the 'new' node after the tail node
 * */
void	insert_tail_List(List_Node *new, List_Node *list)
{
	struct list_head *prev = (list->p_field).prev;
	struct list_head *next = &(list->p_field);
	struct list_head *new_head = &(new->p_field);
	new_head->prev = prev;
	new_head->next = next;
	prev->next = new_head;
	next->prev = new_head;
	Node_Number++;
}
/*
 * insert_head_List - add a new node
 * @new: the node to be inserted
 * @list: the list which the 'new' node will be inserted in
 *
 * Add the 'new' node after the head node
 * */
void 	insert_head_List(List_Node *new, List_Node *list)
{
	struct list_head *prev = &(list->p_field);
	struct list_head *next = (list->p_field).next;
	struct list_head *new_head = &(new->p_field);
	new_head->prev = prev;
	new_head->next = next;
	prev->next = new_head;
	next->prev = new_head;
	Node_Number++;
}

/*
 * insert_key_List - add a new node
 * @key:insert after the node which the data field is 'key'
 * @new:the node to be inserted
 * @list:the list which the 'new' node will be inserted in
 *
 *Insert the 'new' node after 'key' node
 *If successful, return 0
 *If 'key' doesn't exist,so retun -1
 * */
int 	insert_key_List(int key, List_Node *new, List_Node *list)
{
	List_Node *key_node;
	key_node = find_key_List(key, list);
	if( key_node == NULL)	{
		return -1;
	}
	list_add(&(new->p_field), &(key_node->p_field));
	Node_Number++;
	return 0;
}
/*
 * remove_key_List - delete a node
 * @key: remove the node which the data field is 'key'
 * @list:the list includeing the node which will be removed
 *
 * Remove the 'key' node from the list
 * Return Value:
 *	If it's -1, the List has no the 'key' node
 *  If It's 0, remove successfully
 *
 * */
int remove_key_List(int key, List_Node *list)
{
	List_Node *key_node;

	key_node = find_key_List(key, list);
	if(key_node == NULL)	
		return -1;
	list_del(&(key_node->p_field));
	Node_Number--;
	return 0;
}
/*
 * remove_index_List - delete a node
 * @index: remove the 'index' node 
 * @list:the list includeing the 'index 'node
 *
 * Remove the 'index' node from the list
 * Return Value:
 *	If it's -1, the List has no the 'index' node
 *  If It's 0, remove successfully
 *
 **/
int	remove_index_List(int index, List_Node *list)
{
	List_Node *index_node = find_index_List(index, list);

	if(index_node == NULL) 
		return -1;
	list_del(&(index_node->p_field));
	Node_Number--;
	return 0;
}
/*
 * sum_List - get the sum of the all nodes's data
 * @list: the list to be summed
 * */
int	sum_List(List_Node *list)
{
	struct list_head *pos;
	List_Node *cur_list;
	int	sum = 0;

	list_for_each(pos, &(list->p_field))	{
		cur_list = list_entry(pos, List_Node, p_field);
		sum += cur_list->data;
	}
	return sum;
}

/*
 * display_List - output the node's data
 * @list: the list to be outputed
 *
 *Display the List 'data' member and the index
 * */
void display_List(List_Node *list)
{
		struct list_head *pos;
		List_Node *cur_list;
		int i=0;

		list_for_each(pos, &(list->p_field)) {
			cur_list = list_entry(pos, List_Node, p_field);
			printf("%d-->%d\n",++i, cur_list->data);
		}
		printf("The total nodes are %d\n", i);
}
