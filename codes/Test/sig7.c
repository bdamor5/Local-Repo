#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
  alarm(4);
  if (fork() == 0) {
     alarm(5);
     printf("I am the child\n");
     sleep(2);
     execl("./do_nothing", "do_nothing", NULL);
  }
  else while (1) {
     printf("I am the parent\n");
     sleep(1);
  }
}
