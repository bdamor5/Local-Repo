#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int i = 0;

void handler(int sig) {
   i++;
}
 
int main()  {
   int temp;
    
   signal(SIGALRM, handler);
   alarm(1);
pause(); 
   temp = i;
   temp = temp + 1;
   i = temp;

//   pause();
   printf("%d\n", i);
}
