#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
pid_t cpid;
/* Handle SIGALRM */
void handler(int sig)
{
  if (cpid == 0)
     printf("running child handler\n");
  else
     printf("running parent handler\n");
}
int main() {
   signal(SIGALRM, handler);
   if ((cpid = fork()) == 0) {
     printf("I’m the child\n");
     alarm(2);
     pause();  
     printf("child pause ret\n");
   }
   else {
     printf("I’m the parent\n");
     alarm(1);
     pause();
     printf("parent pause ret\n");
   }
}

