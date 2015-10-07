#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int n;
    unsigned long long i,counter;
    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);
    if ((n / 8) >= (sizeof(counter)))
    {
	printf("\nUsage: n must not exceed %d on your machine.\n",
	       ((int) sizeof(counter)) * 8 - 1);
	return 0;
    }
    counter=pow(2,n);
    for(i=0;i<=counter;i++);
    return 0;
}

