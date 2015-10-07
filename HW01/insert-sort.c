#include <stdio.h>
#include <stdlib.h>

void insert_sort(int *array,int n)
{
    int i,j,temp;

    for(i=1;i<=(n-1);i++)
    {
	temp=array[i];
	j=i;
	while((j>0) && (array[j-1]>temp)){
	    array[j]=array[j-1];
	    j--;
	}
	array[j]=temp;
    }
}

int main(int argc,char *argv[])
{
    int n,element_to_find,i,*array;

    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);
    srand(time(NULL));
    array=(int*)malloc(sizeof(int)*n);
    for(i=0;i<=(n-1);i++){
	array[i]=rand();
    }
    insert_sort(array,n);
}
