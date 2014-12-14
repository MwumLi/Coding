#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>

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
			int (*compar)(const void *, const void *));

#endif
