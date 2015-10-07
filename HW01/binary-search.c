#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    int n,element_to_find,i,key,last,first;

    if (argc==1)
    {
	printf("\nUsage: temp -n\n n: The range of elements to consider\n");
	exit(0);
    }
    n=atoi(argv[1]);
    srand(time(NULL));
    for(i=0;i<100;i++)
	element_to_find=rand()%n;
    i=0; //Set i to 1 when element is found
    last=n;
    first=0;

    while((!i) && (first<last)){
	key=(first+last)/2;
	if(element_to_find>key)
	    first=key;
	else if(element_to_find<key)
	    last=key;
	else i=1;
	sleep(1);
    }

    return 0;
}	

