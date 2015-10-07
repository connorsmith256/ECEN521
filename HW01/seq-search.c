#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(int argc, char *argv[])
{
    long n,element_to_find,i;

    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }

    n=atoi(argv[1]);

    element_to_find = n/2;

    i=0;
    while ((i<=n) && (i!=element_to_find)) i++;

    return 0;
}
