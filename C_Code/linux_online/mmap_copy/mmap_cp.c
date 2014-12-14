#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>

#define FILE_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char **argv)
{
	int 	fdin, fdout;
	void 	*src, *dst;
	struct stat statbuf;

	if(argc != 3) {
		printf("Usage:%s <fromfile> <tofile>\n", argv[0]);
		return -1;
	}

	if( (fdin=open(argv[1], O_RDONLY)) < 0 ) {
		printf("open %s:%s\n", argv[1], strerror(errno));
		return -1;
	}	
	if( (fdout=open(argv[2], O_RDWR|O_CREAT|O_TRUNC, FILE_MODE)) < 0 ) {
		printf("open %s:%s\n", argv[1], strerror(errno));
		return -1;
	}
	if(fstat(fdin, &statbuf) < 0) {
		printf("fstat:%s\n", strerror(errno));
		return -1;
	}
	
	/*set size of output file*/
	if(lseek(fdout, statbuf.st_size-1, SEEK_SET) < 0) {
		printf("lseek:%s\n", strerror(errno));
		return -1;
	}
	
	if(write(fdout,"", 1) != 1) {
		printf("write:%s\n", strerror(errno));
		return -1;
	}
	return 0;
	src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
	if(src == MAP_FAILED) {
		printf("mmap1:%s\n", strerror(errno));
		return -1;
	}	
	dst = mmap(0, statbuf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, 
			fdout, 0);
	if(dst == MAP_FAILED) {
		printf("mmap2:%s\n", strerror(errno));
		return -1;
	}
	
	memcpy(dst, src, statbuf.st_size-1);
	return 0;
}
