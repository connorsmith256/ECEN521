#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[])
{
    long n,n2,i,j,fact,fact2;

    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);

    if (n > 16) {
	n = 16;
	n2 = (n > 26) ? 26 : n;
    } else	{
	n2 = 1;
    }

    fact2 = 1;
    for (j=17; j<=n2; j++)
	fact2= fact2 * j;

    for(j=1; j<= fact2; j++) {
	fact=1;
	for(i=1;i<=n;i++)
	    fact=fact*i;

	for(i=0;i<=fact;i++);
    }

    return 0;
}
