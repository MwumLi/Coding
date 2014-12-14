#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include "list.h"
#include <stdlib.h>

/*
 *	some limit definiion 
 * */
#define Max_Line    255
#define US_Limit    10  //decimal digits
//Reserve Word
#define RW_MIN      0   
#define RW_NUM      11
//Identifier define 
#define ID_define   (RW_MIN+RW_NUM)
//Unsigned define
#define US_define   (ID_define+1)
//Operator define
#define OP_MIN      (US_define+1)
#define OP_NUM      11
//Delimiter define
#define DE_MIN      (OP_MIN+OP_NUM) 
#define DE_NUM      5
/*
 * Build the reserved word table, operator table, delimiter table
 * */
static char reserved_word[RW_NUM][10]={ "PROGRAM", "BEGIN", "END",
                                    "VAR", "INTEGER", "WHILE",
                                    "IF", "THEN", "ELSE",
                                    "DO", "PROCEDURE"   };

static char operaor[OP_NUM][3]={"+","-","*","/",
                    ">",":=","=","<",">=","<=","<>"};

static char delimiter[DE_NUM][2]={",",":",";","(",")"};
//The list for <code, value>
typedef struct Code_Value {
    int     code;
    void    *value;
    struct  list_head p_field;
} Code_Value;
//The list for identifier
typedef struct ID {
	char *id;
	struct list_head p_field;
} ID;
//The list for unsigned 
typedef struct UNSIGNED {
	unsigned	data;
	struct list_head p_field;
} UNSIGNED;

void init_CV(Code_Value *list)
{
	INIT_LIST_HEAD(&(list->p_field));
}
void init_ID(ID *list)
{
	INIT_LIST_HEAD(&(list->p_field));
}
void init_US(UNSIGNED *list)
{
	INIT_LIST_HEAD(&(list->p_field));
}

//make node
Code_Value *make_CV_node(int code, void *value)
{
	Code_Value *nnew= (Code_Value *)malloc(sizeof(Code_Value));
	nnew->code = code;
	nnew->value = value;
	return nnew;
}
ID *make_ID_node(char *id)
{
	ID *nnew=(ID *)malloc(sizeof(ID));
	nnew->id = id;
	return nnew;
}
UNSIGNED *make_US_node(unsigned data)
{
	UNSIGNED *nnew= (UNSIGNED *)malloc(sizeof(UNSIGNED));
	nnew->data = data;
	return nnew;
}
//insert node
void insert_CV(Code_Value *nnew, Code_Value *list)
{
	list_add_tail(&(nnew->p_field), &(list->p_field));
}
ID *insert_ID(ID *nnew, ID *list)
{
	list_add_tail(&(nnew->p_field), &(list->p_field));
	struct list_head *lp=(list->p_field).prev;
	return list_entry(lp, ID, p_field);
}
UNSIGNED *insert_US(UNSIGNED *nnew, UNSIGNED *list)
{
	list_add_tail(&(nnew->p_field), &(list->p_field));
	struct list_head *lp=(list->p_field).prev;
	return list_entry(lp, UNSIGNED, p_field);
}
static inline char *__print_binary(unsigned data)
{
	int	i;
	int	bit_size = sizeof(unsigned)*8;
	char *str=(char *)malloc(bit_size+1);
	char *p=str;
	for(i=bit_size-1; i>=0; i--) {
		if(data & (1<<i))
			*p++='1';
		else
			*p++='0';
	}
	*p='\0';
	return str;
}
void display_CV(Code_Value *list)
{
	struct list_head *pos;
	Code_Value *cur_list;
	int		code;
	
	printf("词法解析如下:\n");
	list_for_each(pos, &(list->p_field)) {
		cur_list = list_entry(pos, Code_Value, p_field)	;
		code = cur_list->code;
		if(code>=RW_MIN && code <=(RW_MIN+RW_NUM-1)) {
			char *str = (char *)cur_list->value;
			printf("(#%s, %s)\n",reserved_word[code], str);
		} else if(code == ID_define) {
			ID *cur_id=(ID *)cur_list->value;
			printf("(ID, %s)\n", cur_id->id);
		
		} else if(code == US_define) {
			UNSIGNED *cur_us=(UNSIGNED *)cur_list->value;
			printf("<us, %s>\n", __print_binary(cur_us->data));
	//		printf("<us, %d>\n", cur_us->data);
		} else if(code>=OP_MIN && code<=(OP_MIN+OP_NUM-1)) {
			char *str = (char *)cur_list->value;
			printf("<OP, %s>\n", str);
		} else if(code>=DE_MIN && code<=(DE_MIN+DE_NUM-1)) {
			char *str = (char *)cur_list->value;
			printf("<DE, %s>\n", str);
		} else {
			printf("None\n");
		}
	}	
	printf("词法解析结束\n一些说明:\n");
	printf("#str--->Reserver Word\n");
	printf("ID--->Identifier\n");
	printf("DE--->Delimiter\n");
	printf("OP--->Operator\n");

}
#endif
