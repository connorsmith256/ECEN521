#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    int n,i,j,k,t;

    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);
    for(i=0;i<=n;i++)
	for(j=0;j<=n;j++)
	    for(k=0;k<=n;k++)
		t++;
    return 0;
}
