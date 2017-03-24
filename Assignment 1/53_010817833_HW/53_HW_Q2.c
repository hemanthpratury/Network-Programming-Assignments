#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("This is main process \n");
	int pid=fork();
	if(pid==0)
	{
	
	char *const arg[1] = {};
	char *const argv[1] = {};
	execve("summ",arg,argv);

	}	
	
	return 0;
}
