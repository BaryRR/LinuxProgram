#include "lib.h"
int max(int *a, int n)
{
	int i, max;
	max = a[0];
	for(i=0; i<n; i++)
	{
		if(max<a[i])
			max = a[i];	
	}
	return max;
}
void show(int *a, int n)
{
	int i;
	for(i=0;i<n;i++)
	printf("a[%d]=%d\n",i,a[i]);
}

