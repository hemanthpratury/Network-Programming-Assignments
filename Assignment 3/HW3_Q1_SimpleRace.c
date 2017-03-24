#include <stdio.h>	
#include <pthread.h>	

int count = 0;	
	
int  thread_ids[3] = {0,1,2};	

void *inc_count(void *idp)	
{	
    long tid=(long)idp;
    count++;
    if(count==700)
	{
	   printf("Entering condition\n");
	    int y=count*2;
	    printf("Value of y is :%d and count is : %d\n",y,count);
	}
    //printf("in thread : %ld, count val :%d\n", tid,count);
	
}
	
int main(void)	
{	
     long      i;	
     pthread_t threads[3];	
     	
     for (i = 0; i < 10000; i++) {	
             pthread_create(&threads[0],NULL,(void * (*)(void *))inc_count, (void *)i);
     }	
  pthread_exit(NULL);
}	

