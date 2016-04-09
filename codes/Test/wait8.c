#include<stdio.h>
#include<sys/wait.h>
int main()
{
	int i, stat;
	pid_t cpid,p[5];
	for(i=0;i<5;i++)
	{
		if ((p[i]=fork()) == 0) {
			printf("Child pid = %d\n", getpid());
			sleep(3);
			exit(1);
		} 


		/* use with -1 to wait on any child (with options) */


	}
	for(i=0;i<5;i++)
	{       
		while ((cpid = waitpid(-1, &stat, WNOHANG)) == 0) {
			sleep(1);
			printf("No terminated children\n");
		
		}
	 printf("Reaped %d with exit status: %d\n",
                        cpid, WEXITSTATUS(stat));

	}
	
}
