#include<stdio.h>
#include<stdlib.h>

int *aux_array;

void mymergesort(int array[],int l,int r)
{
    int i,j,k,m;

    if (r>l)
    {
	m=(r+l)/2;
	mymergesort(array,l,m);
	mymergesort(array,m+1,r);
	for(i=m+1;i>l;i--) aux_array[i-1]=array[i-1];
	for(j=m;j<r;j++) aux_array[r+m-j]=array[j+1];
	for(k=l;k<=r;k++)
	    array[k]=(aux_array[i]<aux_array[j])?aux_array[i++]:aux_array[j--];
    }
}    

int main(int argc, char *argv[])
{
    int n,i,*array;
    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);

    array=(int*)malloc(sizeof(int)*n);
    aux_array=(int*)malloc(sizeof(int)*n);
    srand(time(NULL));
    for(i=0;i<n;i++)
	array[i]=rand();
    mymergesort(array,0,n-1);
/*for(i=0;i<n;i++)
  printf("array[%d]: %d\n",i,array[i]);*/
}
