#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int pid;
void hand(int a)
{
if(pid==0)
printf("I am in Child\n");
else
printf("I am in PArent\n");
}
int main()
{
signal(SIGINT,hand);
if((pid=fork())==0)
while(1)
pause();

else
while(1)
pause();
return 0;
}
