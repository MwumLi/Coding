#include <syscall.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	long  p = syscall(SYS_getppid);

	printf("%ld\n", p);
	printf("%ld\n", getpid());
	return 0;
}
