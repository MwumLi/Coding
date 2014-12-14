#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int parse(char **argv, int argc);
int str2oct(char *str);
void err_str(char *program);

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage:%s mode filename\n", argv[0]);
		return -1;
	}
	
	int mode = parse(argv, argc);
	if(chmod(argv[2], mode) < 0) {
		perror("chmod");
		exit(errno);
	}
	return 0;
}
int parse(char **argv, int argc)
{
	struct stat attr;
	mode_t		mode;
	mode_t		change=0;
	int			len=strlen(argv[1]);
	int			i;


	if (stat(argv[2], &attr) < 0) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	mode = attr.st_mode;	//the original mode

	//if mode is number
	for(i=0; i<len; i++) 
	{
		if(argv[1][i]<'0' || argv[1][i]>'9')
		  break;
	}
	if(i == len) {

		change = str2oct(argv[1]);
		mode >>=9;
		mode <<=9;
		mode |= change;
		return mode;
	} 

	//if mode is letter
	if(argv[1][0] == 'a' || argv[1][0] == 'u' ||
	   argv[1][0] == 'g' || argv[1][0] == 'o') {
		//if + or -
		if(argv[1][1] == '+' || argv[1][1]== '-') {
			for (i = 2; i < len; i++) {
				if(argv[1][i] == 'r')	//read
					change |= 4;
				else if( argv[1][i] == 'w') //write
					change |= 2;
				else if( argv[1][i] == 'x') //exec
					change |= 1;
				else 
				  ;//omit
			}
		} else {	//+/-之外的字符
			err_str(argv[0]);
		}
	} else 	{	//user error
		err_str(argv[0]);
	}
	
	switch(argv[1][0]) {
		case 'a':
			{
				int temp=change;
				change <<=3;
				change |= temp;
				change <<=3;
				change |= temp;
			 }
			break;
		case 'u':
			change <<=6;
			break;
		case 'g':
			change <<=3;
		default:
			;
	}

	if(argv[1][1] == '+') 
	  mode |= change;
	else {
	  int m=1,t;
	  int a,b;
	  for(i=0; i<9; i++)
	  {
			a=b=0;
			t=m<<i;
			if(mode & t) 
			  a=1;
			if(mode & t)
			  b=1;
			if(a-b>0)
			  mode |= t;
			else 
			  mode &= ~t;
	  }
	} 
	return mode;
}

int str2oct(char *str)
{
	int oct=0;
	while(*str != '\0') {
		oct |= (*str)-'0';
		oct<<=3;
		str++;
	}
	oct>>=3;
	return oct;
}
void err_str(char *program)
{
	printf("chmod: invalid mode: '%s'\n", program);
	printf("Try 'chmod --help' for more \n");
	exit(EXIT_FAILURE);
}

