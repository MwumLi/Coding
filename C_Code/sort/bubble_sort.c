#include "sort.h"

void bubble_sort(void *base, size_t nmemb, size_t size,
			int (*compar)(const void *, const void *))
{
	char	*arr; 
	char	*a1, *a2;
	int		i, n;
	int		last;	//the last number for comparing

	arr = (char *)base;
	n = nmemb - 1;

	while(n > 0) {
		last = 0;
		for(i=0; i<n; i++) {
			a1 = arr + i*size;
			a2 = a1 + size;
			if(compar(a1, a2) > 0) {
				swap(a1, a2, size);
				last = i;
			}
		}
		n = last;
	}

}
