#include<stdio.h>
#include<sys/wait.h>
int main()
{

	pid_t p[5];
	int i=0,stat;
	for(i=0;i<5;i++)
	{
		if((p[i]=fork())==0)
		{
			sleep(1);
			exit(100+i);
		}

	}
	for(i=0;i<5;i++)
	{
	pid_t result = waitpid(p[i],&stat,0);
	if(WIFEXITED(stat))
	{
		printf("child %d terminate with status: %d\n",result,WEXITSTATUS(stat));		
		sleep(1);
	}
	}
	
	return 0;
}


