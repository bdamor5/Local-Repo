#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
void handler(int sig) {
   printf("Can’t be ctr-\\ed\n");
}
 
int main()
{
   signal(SIGINT, SIG_IGN);
   signal(SIGQUIT, handler);
   pause();
   execl("./do_nothing", "do_nothing", NULL);
}
