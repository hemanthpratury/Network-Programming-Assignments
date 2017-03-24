#include <stdio.h>
#include <unistd.h>

int main()
{
int i,sum=0;
printf("\n Entered into child process using execve() \n ");

for(i=1;i<=5;++i){
sum=sum+i;
}

printf("\n the sum of first five natural numbers is %d \n",sum);
printf("press enter \n");

return 0;
}
