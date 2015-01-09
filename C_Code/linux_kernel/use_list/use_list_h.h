#ifndef USE_LIST_H
#define USE_LIST_H
#include "list.h"

typedef struct List_Node {
    int     data;
    struct list_head p_field;
}List_Node;

int Node_Number = 0;

/*
 * init_List - init a list
 * @list: a List_Node list head pointer
 * 
 * Init a empty list
 * */
void        init_List(List_Node *list);
/*
 * destory_List - destory a list
 * @list: a List_Node list head pointer
 * 
 * Remove the all nodes and free them except the head node
 **/
void 		destory_List(List_Node *list);

int does_empty_List(List_Node *list) 
{
	struct list_head *p = &(list->p_field);
	if(p->prev == p &&p->next == p)
			return 0;
	return 1;	//not empty
}
/*
 * make_node - make a node
 * @data: int varible
 *
 * Alloc a List_Node space to make the node,
 * which the data field is 'data'.
 **/
List_Node   *make_node(int data);
/*
 * free_node - free a node
 * @node: the node to destory
 *
 * Free the 'node' node
 *	If 'node' is NULL, return -1
 *	If remove successfully, return 0
 **/
int         free_node(List_Node *node);

/*
 * find_key_List - find the node
 * @key: the key word of the node to find
 * @list: the head of the list which you'll find the key node
 *
 * Find the key node which data field is 'key' in 'list'
 * Find it, return the key node
 * or, return NULL
 **/
List_Node   *find_key_List(int key, List_Node *list);
/*
 * find_index_List - find the node
 * @index: the index word of the node to find
 * @list: the head of the list which you'll find the key node
 *
 * Find the 'index' node in 'list'
 * Find it, return the 'index' node
 * or, return NULL
 **/
List_Node 	*find_index_List(int index, List_Node *list);

/*
 * insert_tail_List - add a new node
 * @new: the node to be inserted
 * @list: the list which the 'new' node will be inserted in
 *
 * Add the 'new' node after the tail node
 * */
void        insert_tail_List(List_Node *new, List_Node *list);
/*
 * insert_head_List - add a new node
 * @new: the node to be inserted
 * @list: the list which the 'new' node will be inserted in
 *
 * Add the 'new' node after the head node
 * */
void        insert_head_List(List_Node *new, List_Node *list);
/*
 * insert_key_List - add a new node
 * @key:insert after the node which the data field is 'key'
 * @new:the node to be inserted
 * @list:the list which the 'new' node will be inserted in
 *
 * Insert the 'new' node after 'key' node
 *	If successful, return 0
 *	If 'key' doesn't exist,so retun -1
 **/
int			insert_key_List(int key, List_Node *new, 
                                List_Node *list);
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
int         remove_key_List(int key, List_Node *list);
/* 
 * remove_index_List - delete a node 
 * @index: remove the 'index' node  
 * @list:the list includeing the 'index 'node 
 * 
 * Remove the 'index' node from the list 
 * Return Value: 
 *	If it's -1, the List has no the 'index' node 
 *	If It's 0, remove successfully 
 * 
 **/
int			remove_index_List(int index, List_Node *list);
/*
 * sum_List - get the sum of the all nodes's data
 * @list: the list to be summed
 * */
int         sum_List(List_Node *list);
/*
 * display_List - output the node's data
 * @list: the list to be outputed
 *
 *Display the List 'data' member and the index
 * */
void        display_List(List_Node *list);
#endif
