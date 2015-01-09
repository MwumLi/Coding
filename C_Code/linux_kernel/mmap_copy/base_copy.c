#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

#define COPY_NUM	512
#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char **argv)
{
	int 	src, dst;
	char *copy_byte;
	int	read_count;	

	if(argc != 3) {
		printf("Usage:%s <fromfile> <tofile>\n", argv[0]);
		return -1;
	}

	if( (src=open(argv[1], O_RDONLY)) < 0 ) {
		printf("open %s:%s\n", argv[1], strerror(errno));
		return -1;
	}	
	if( (dst=open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0 ) {
		printf("open %s:%s\n", argv[1], strerror(errno));
		return -1;
	}
	
	copy_byte = (char *)malloc(COPY_NUM);
	while(1) {
		read_count = read(src, copy_byte, COPY_NUM-1);
		if(read_count == 0)
			break;
		if(read_count < 0) {
			printf("read:%s\n", strerror(errno));
			return -1;
		}
		if(write(dst, copy_byte, read_count) < 0) {
			printf("write:%s\n", strerror(errno));
			return -1;
		}
	}	
	close(src);
	close(dst);
	return 0;
}
