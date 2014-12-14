#ifndef CODE_VALUE_H
#define CODE_VALUE_H
#include "list.h"
typedef struct Code_Value {
    int     code;
    void    *value;
    struct  list_head p_field;
}Code_Value;

void init_CV(Code_Value *list)
{
	INIT_LI
}
#endif
