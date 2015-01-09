#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "cp_by_basicIO.h"
#define BUF_SIZE 80

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
//		ret = cp_by_fgetc_fputc(source, dest);
//		ret = cp_by_fgets_fputs(source, dest, BUF_SIZE );
		ret = cp_by_fread_fwrite(source, dest, BUF_SIZE );

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


