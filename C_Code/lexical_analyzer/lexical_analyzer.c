#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include "list.h"
#include "lexical_analyzer.h"


void my_error(char *str, char *error);

int judge_number(char c);
int judge_lowercase(char c);
int judge_uppercase(char c);
int judge_rw(char *str);
int judge_operator(char *str);
int judge_delimiter(char *str);

int main(int argc, char **argv)
{
	FILE		*src_fp;
	Code_Value	cv_list;	
	ID			id_list;
	UNSIGNED	us_list;
	int			code;
	char 		*unit;
	unsigned	us_value;

	Code_Value	*nnew_cv;
	ID			*nnew_id;
	UNSIGNED	*nnew_us;

	char 	*start;	//the start addr of the unit 
	int 	unit_count=0;
	char 	line[Max_Line];

	if(argc != 2)	{
		char str[20];
		strcpy(str, argv[0]);
		strcpy(str, " <soucefile>");
		my_error("Usage:", str);
	}
	
	init_CV(&cv_list) ;
	init_ID(&id_list) ;
	init_US(&us_list) ;

	src_fp = fopen(argv[1], "rt");
	if(src_fp == NULL) {
		my_error("fopen", strerror(errno));
	}
	while(fscanf(src_fp, "%s", line) != EOF) {
		int	len = strlen(line);
		int	i;
		
		unit_count=0;
		start = line;
		
		for(i=0; i<len; ) {
			unit_count = 0;
			//ID item or Reserve item
			if(	!judge_lowercase(line[i]) ||
				!judge_uppercase(line[i])	) {
				unit_count++;
				start = line+i;
				i++;
				while(	i<len &&
						(	!judge_uppercase(line[i]) ||
							!judge_lowercase(line[i]) ||
							!judge_number(line[i])	)	) {
					unit_count++;
					i++;	//*
				}
				unit=(char *)malloc(unit_count+1);
				memcpy(unit, start, unit_count);
				unit[unit_count]='\0';
				if( (code=judge_rw(unit)) == ID_define) {
					nnew_id = make_ID_node(unit);
					nnew_id = insert_ID(nnew_id, &id_list);
					nnew_cv = make_CV_node(code, nnew_id);
				} else {
					nnew_cv = make_CV_node(code, reserved_word[code]);
				}
				insert_CV(nnew_cv, &cv_list);
				continue;
			}// end Id item or Reserve item
			//unsigned item
			if( !judge_number(line[i]) )	{
				unit_count++;
				start = line + i;
				i++;
				while( i<len && !judge_number(line[i]) ) {
					unit_count++;
					i++;	//*
				}
				if(i>US_Limit) {
					char err_str[100];
					sprintf(err_str, "Number must be less than %d", 
										US_Limit);
					my_error("NUmber",err_str);
				}
				unit=(char *)malloc(unit_count+1);
				memcpy(unit, start, unit_count);
				unit[unit_count]='\0';
				us_value =(unsigned) atol(unit);
				nnew_us = make_US_node(us_value);
				nnew_us =insert_US(nnew_us, &us_list);
				nnew_cv = make_CV_node(US_define, nnew_us);
				insert_CV(nnew_cv, &cv_list);
				continue;
			}//end unsigned item
			else {
				unit_count++;
				start = line+i;
				i++;
				if(	judge_number(line[i]) && 
					judge_uppercase(line[i]) &&
					judge_lowercase(line[i])	) {
					unit_count++;
					i++;
				}
				unit=(char *)malloc(unit_count+1);
				memcpy(unit, start, unit_count);
				unit[unit_count]='\0';
				code = judge_operator(unit)	;
				if(code > 0) {
					nnew_cv = make_CV_node(code, operaor[code-OP_MIN]);
					insert_CV(nnew_cv, &cv_list);
				} 
				code = judge_delimiter(unit);
				if(code > 0) {
					nnew_cv = make_CV_node(code, delimiter[code-DE_MIN]);
					insert_CV(nnew_cv, &cv_list);
				} else 
					continue;
			}// end symbol
		}// end for
	}//end while
	display_CV(&cv_list);
	return 0;
}

void my_error(char *str, char *error) {
	printf("%s: %s\n",str, error);
	exit(-1);
}
int judge_number(char c)
{
	if(c>=48 && c<=57)
		return 0;
	return 1;
}
int judge_lowercase(char c)
{
	if(c>=97 && c<=122)
		return 0;
	return 1;
}
int judge_uppercase(char c)
{
	if(c>=65 && c<=97)
		return 0;
	return 1;
}
int judge_rw(char *str)
{
	int	i=0;
	
	for(i=0; i<RW_NUM; i++)
	{
		if( !strcasecmp(reserved_word[i], str) )
			return i;
	}
	return i;
}
int judge_operator(char *str)
{
	int	i;
	for(i=0; i<OP_NUM; i++)	{
		if( !strcmp(operaor[i], str) )
			return OP_MIN+i;
	}
	return -1;
}
int judge_delimiter(char *str)
{
	int	i;
	for(i=0; i<DE_NUM; i++)	{
		if( !strcmp(delimiter[i], str) )
			return DE_MIN+i;
	}
	return -1;
}

