#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM 10
int compare_int(const void *a,const void *b)
{
	return (*((int *)a))-(*((int *)b));
}
static void swap(char *a, char *b, int	item_size)
{
	char temp;

	if(a == b)
	  return ;

	while(item_size--) {
		temp = *a;
		*a++ = *b;
		*b++ = temp;
	}
}
void bubble_sort(void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *))
{
	char	*arr; 
	char	*a1, *a2;
	int		i, n;
	int		last;

	arr = (char *)base;
	n = nmemb - 1;

	while(n > 0) {
		last = 0;
		for(i=0; i<n; i++) {
			a1 = arr + i*size;
			a2 = a1 + size;
			if(compare_int(a1, a2) > 0) {
				swap(a1, a2, size);
				last = i;
			}
		}
		n = last;
	}

}
int main(int argc, const char *argv[])
{

	int i;
	int a[NUM];

	srand(time(NULL));

	for (i = 0; i < NUM; i++) {
		a[i] = rand()%NUM;
	}

	for(i=0; i<7; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

	bubble_sort(a, 7, sizeof(int), compare_int);

	for(i=0; i<7; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
	return 0;
}
