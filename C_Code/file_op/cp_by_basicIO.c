#include "cp_by_basicIO.h"

/*
 *	Intro: copy source to dest
 *	@source -- source file 
 *	@dest -- destination file
 *	Return Value: 
 *		0 -- Success 
 *		1 -- source does not exists
 *		2 -- dest does not exists
 *		3 -- copy error
 * */

int cp_by_fgetc_fputc(const char *source, const char *dest)
{
	int		ch;	//try change type int to char, happen messy code
	FILE	*source_fp, *dest_fp;

	source_fp = fopen(source, "r");
	if ( source_fp == NULL )
	  return 1;
	dest_fp = fopen(dest, "w");
	if ( dest_fp == NULL ) {
		fclose(source_fp);
		return 2;
	}

	while((ch=fgetc(source_fp)) != EOF) {
		//if write error
		if( fputc(ch, dest_fp) == EOF) {
			fclose(dest_fp);
			fclose(source_fp);
			//delete the failed destination file 
			char rm_file[20]="rm ";
			strcat(rm_file, dest);
			system(rm_file);
			return 3;
		}	
	}

	fclose(source_fp);
	fclose(dest_fp);
	return 0;
}

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
int cp_by_fread_fwrite(const char *source, const char *dest, int buf_size)
{
	int *buf;
	int count;
	FILE *source_fp, *dest_fp;

	source_fp = fopen(source, "r");
	if(source_fp == NULL)
		return 1;	//source file does exist

	dest_fp = fopen(dest, "w");
	if(dest_fp == NULL)
	  return 2;

	buf = (int *)calloc(sizeof(int), buf_size);

	while( (count = fread(buf,	sizeof(int), 
								buf_size, 
								source_fp)) > 0) {

		if(fwrite(buf, sizeof(int), count, dest_fp) != count) {
			fclose(dest_fp);
			fclose(source_fp);
			//delete the failed destination file 
			char rm_file[20]="rm ";
			strcat(rm_file, dest);
			system(rm_file);

			return 3;
		}
	}// end while
	
	if(ferror(source_fp) != 0)
	  return 4;

	return 0;
}

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
int cp_by_fgets_fputs(const char *source, const char *dest, int buf_size)
{
	char *buf;
	FILE *source_fp, *dest_fp;

	source_fp = fopen(source, "r");
	if(source_fp == NULL)
		return 1;	//source file does exist

	dest_fp = fopen(dest, "w");
	if(dest_fp == NULL)
	  return 2;

	buf = (char *)calloc(sizeof(char), buf_size+1);
	
	while(fgets(buf, buf_size, source_fp) !=  NULL) {
		if(fputs(buf, dest_fp) == EOF) {
			fclose(dest_fp);
			fclose(source_fp);
			//delete the failed destination file 
			char rm_file[20]="rm ";
			strcat(rm_file, dest);
			system(rm_file);

			return 3;
		}
	}

	free(buf);
	return 0;
}

/*
 * Intro: judge whether the file exists
 * If the file exists, return 1
 * or return 0
 * */

int does_exist(const char *file)
{
	FILE *fp;

	fp = fopen(file, "r");
	if(fp == NULL)	
	  return 0;
	return 1;
}
/*
 * Intro: print help information
 * */

void print_help(const char *exe_name)
{
	printf("Usage:\n");
	printf("%s source_file dest_file -- if the file existed, prompt it \n", exe_name);
	printf("%s -f source_file dest_file -- omit existed file\n", exe_name);
	printf("%s -h -- print help info\n", exe_name);
}

