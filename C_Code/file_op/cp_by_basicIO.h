#ifndef CP_BY_BASICIO_H
#define CP_BY_BASICIO_H
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define OPT_OPT 0
#define OPT_HELP 1
#define OPT_FORCE 2
#define OPT_ERROR 3

/*
 *	Intro: copy source to dest
 *	@source -- source file 
 *	@dest -- destination file
 *	Return Value: 
 *		0 -- Success 
 *		1 -- source does not exists
 *		2 -- open/create dest file error
 *		3 -- copy error
 * */
int cp_by_fgetc_fputc(const char *source, const char *dest);

/*
 *	Intro: copy source to dest
 *	@source -- source file 
 *	@dest -- destination file
 *	Return Value: 
 *		0 -- Success 
 *		1 -- source does not exists
 *		2 -- open/create dest file error
 *		3 -- copy error
 *		4 -- read data error from source file
 * */		
int cp_by_fread_fwrite(const char *source, const char *dest, int buf_size);

/*
 *	Intro: copy source to dest
 *	@source -- source file 
 *	@dest -- destination file
 *	Return Value: 
 *		0 -- Success 
 *		1 -- source does not exists
 *		2 -- open/create dest file error
 *		3 -- copy error
 *	Bug: only used to copy simple text file
 * */
int cp_by_fgets_fputs(const char *source, const char *dest, int buf_size);

/*
 * Intro: judge whether the file exists
 * If the file exists, return 1
 * or return 0
 * */
int does_exist(const char *file);

/*
 * Intro: print help information
 * */
void print_help(const char *exe_name);

#endif

