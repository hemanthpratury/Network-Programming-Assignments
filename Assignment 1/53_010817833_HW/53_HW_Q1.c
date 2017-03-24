#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{

	int pid1,pid2,pid3,i;
	
	pid1=fork();
	pid2=fork();
	pid3=fork();
	
	if(pid1!=0 && pid2!=0 && pid3!=0)
	printf("hi i am the parent , my pid is: %d  and my three child processes prints some natural numbers \n",getpid());
	
	else if(pid1==0 && pid2!=0 && pid3!=0)
	{
	printf("i am the child1, mypid is %d \n",getpid());
	printf(" I print natural numbers from 1 to 5 \n");
	for(i=1;i<=5;i++)
	printf("%d \n ",i);
	}
	
	else if(pid1!=0 && pid2==0 && pid3!=0)
	{
	printf("i am the child2, mypid is %d \n",getpid());
	printf(" I print natural numbers from 6 to 10 \n");
	for(i=6;i<=10;i++)
	printf("%d \n ",i);
	}
	
	else if(pid1!=0 && pid2!=0 && pid3==0)
	{
	printf("i am the child3, mypid is %d \n",getpid());	
	printf(" I print natural numbers from -10 to -15 \n");
	for(i=-15;i<=-10;i++)
	printf("%d \n ",i);
	}

return 0;
		
}
