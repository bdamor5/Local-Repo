#include<stdio.h>
#include<sys/wait.h>
int main()
{
	if(fork()==0)
	{
		int t = waitpid(getppid(),NULL,0);
		printf("%d\n",t);
	}
	else
	{
		wait(NULL);
		printf("HI\n");
	}
	printf("HELLO\n");
return 0;
} 
