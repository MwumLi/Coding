#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	if(argc != 2) {
		printf("Usage:%s fielname\n", argv[0]);
		return 1;
	}

	FILE	*op;
	op = fopen(argv[1], "w");
	if(op == NULL) {
		printf("fopen:%s\n", strerror(errno));
		return errno;
	}
	fclose(op);
	return 0;
}
