#include<stdio.h>
void foo(int *p)
{
int y = 10;
p = &y;
}
int main()
{
int x = 5000;
int *p = &x;
printf("%p\n",p);
foo(p);
printf("%p\n",p);
}

