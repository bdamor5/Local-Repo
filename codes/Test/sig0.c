#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int i = 0;
void handler(int a) {
   if (!i) {
      kill(getpid(), SIGINT);
   }
   i++;
}

int main() 
{
   int k=0;
   signal(SIGINT, handler);
   kill(getpid(), SIGINT);
 
   printf("%d\n", i);
   return 0;


	
}
