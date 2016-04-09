#include<stdio.h>
int main()
{
int a[3];
a[0]=0;
a[1]=1;
a[2]=2;
void *bp=&a[3];
printf("%d\n",*((char **)(bp)-1));
}
