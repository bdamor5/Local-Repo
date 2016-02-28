#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
	int n,i;
	char cmd[25];
	pid_t pid = getpid();
	scanf("%d",&n);
	int x[n],y[n];
	int count=1;
	printf("[%d] pid %d, ppid %d\n",count,getpid(),getppid());
	for(i=0;i<n-1;i++)
	{
	//	printf("[%d] pid %d, ppid %d\n",count,getpid(),getppid());
		if((x[i]=fork())!=0)
		{
			if((y[i]=fork())!=0)
			{
				if(x[i]<y[i])
				{
					printf("[%d] pid %d created left child with PID %d\n",count,getpid(),x[i]);
					printf("[%d] pid %d created right child with PID %d\n",count++,getpid(),y[i]);
					printf("[%d] pid %d, ppid %d\n",count++,x[i],getpid());
					printf("[%d] pid %d, ppid %d\n",count++,y[i],getpid());

				}
				else
				{
					printf("[%d] pid %d created left child with PID %d\n",count,getpid(),y[i]);
					printf("[%d] pid %d created right child with PID %d\n",count++,getpid(),x[i]);
					printf("[%d] pid %d, ppid %d\n",count++,y[i],getpid());
					printf("[%d] pid %d, ppid %d\n",count++,x[i],getpid());
				}
				break;
			}
			else
			{
				count++;
				continue;
			}
		}
		else
		{
			count++;
			continue;
		}
	}

	/*if(x[0]!=0 && y[0]!=0)	
	  {
	  sprintf(cmd,"pstree -p %d\n",pid);
	  system(cmd);
	  }*/
	int stat;

	if(x[i]>y[i])
	{
		int tmp = x[i];
		x[i] = y[i];
		y[i] = tmp;
	}
	int pid1 = waitpid(x[i],NULL,0);	
	int pid2 = waitpid(y[i],NULL,0);
	if(pid1!=-1)
	printf("[%d] left  child %d of %d exited with status %d\n",count,pid1,getpid(),WEXITSTATUS(stat));
	if(pid2!=-1)
	printf("[%d] right child %d of %d exited with status %d\n",count,pid2,getpid(),WEXITSTATUS(stat));
	//printf("[%d] %d exited with status %d\n",count,getpid(),WEXITSTATUS(stat));
	return 0;
}
