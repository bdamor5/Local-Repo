#include<stdio.h>
int main()
{
int x,y;
scanf("%d %d",&x,&y);
unsigned char *p = (unsigned char *)&x;
unsigned char *q = (unsigned char *)&y;
int z=y-*q;
z=z+*p;
printf("%x %x %x\n",x,y,z);
return 0;
}
