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
 *		2 -- dest does not exists
 * */
int cp_by_fgetc_fputc(const char *source, const char *dest);
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

int main(int argc, const char *argv[])
{

	const char	*source, *dest, *option;
	int		opt;
	int		ch;
	int		ret;
	int		i;

	//Init some varibles
	source = dest = option = NULL;
	opt = OPT_OPT;

	if (argc == 2 || argc == 3) {
		//for loop -- get source, dest and option
		for (i=1; argv[i] != NULL; i++) {
			//If it is option
			if(argv[i][0] == '-') {
				if(strcmp(argv[i], "-h") == 0) 
				  opt = OPT_HELP;
				else if (strcmp(argv[i], "-f") == 0) 
				  opt = OPT_FORCE;
				else
				  opt = OPT_ERROR;
				option = argv[i];
				continue;
			}

			//if it is not option
			if(source == NULL)
			  source = argv[i];
			else
			  dest = argv[i];
		} // end for loop

		//run depend on `option`
		switch(opt) {
			case OPT_OPT:
				{
					//假如目标文件存在，提示...
					if ( does_exist(dest) ) {
						printf("The destination file '%s' exists\n", argv[2]);
						printf("Are you sure to overwrite it?[y/n]");
						ch = getchar();
						if(ch == 'y') 
						  goto COPY;
						return 0;	// not copy
					}

				}
			case OPT_FORCE:
				goto COPY;
			case OPT_HELP:
				goto HELP;
			case OPT_ERROR:
				printf("No option '%s'\n", argv[1]);
				printf("Please use '%s -h' to see usage\n", argv[0]);
				return 1;
		}
	} else {
HELP:
		print_help(argv[0]);
		return 0;
	}

//Detailed copy process and error handing
COPY:
		ret = cp_by_fgetc_fputc(source, dest);

		if (ret == 0) 
		  return 0;	//copy successfully
		else if (ret == 1) {	
			printf("The source file '%s' does not exist\n", argv[1]);
			exit(EXIT_FAILURE);	
		} else {
			printf("Copy error\n");
			return 1;
		}
}

int cp_by_fgetc_fputc(const char *source, const char *dest)
{
	int		ch;
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
int does_exist(const char *file)
{
	FILE *fp;

	fp = fopen(file, "r");
	if(fp == NULL)	
	  return 0;
	return 1;
}
void print_help(const char *exe_name)
{
	printf("Usage:\n");
	printf("%s source_file dest_file -- if the file existed, prompt it \n", exe_name);
	printf("%s -f source_file dest_file -- omit existed file\n", exe_name);
	printf("%s -h -- print help info\n", exe_name);
}

