#include<stdio.h>
int main()
{
	if(fork()==0)
		printf("Terminating child's PID= %d\n",getpid());
	else
	{
		printf("Running parent program\n");
		while(1);
	}
}
