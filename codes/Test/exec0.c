#include<stdio.h>
#include<stdlib.h>
int main() {      /* exec1.c */
   char *args[2];
   args[0] = "/bin/echo";
   args[1] = NULL;
  int x =  execv("Downloads/Matlab/R2011a/bin/./matlab", args);
	printf("%d %s\n",x,args[0]);
   return 0;
}
