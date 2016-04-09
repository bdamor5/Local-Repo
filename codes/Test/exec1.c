#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
int i=6;
int *p=&i;
double *x = (double *)p;
printf("%d\n",*x);
return 0;
}
