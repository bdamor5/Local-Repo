#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
void wait0()
{
  int stat;
  if (fork() == 0)
     while(1);
  else
     wait(&stat);
printf("%d\n",stat);
  if (WIFEXITED(stat))
     printf("Exit status: %d\n", WEXITSTATUS(stat));
  else if (WIFSIGNALED(stat))
     psignal(WTERMSIG(stat), "Exit signal");
}
int main()
{
wait0();
return 0;
}
