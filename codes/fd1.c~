#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main()
{
int fd1, fd2;
    char c;
    fd1 = open("foobar.txt", O_RDWR, 0);
    fd2 = open("foobar.txt", O_RDONLY, 0);
   
   // write(fd1,"uttam",5);
    read(fd1, &c, 1);
    read(fd2, &c, 1);
    printf("c = %c\n", c);
    exit(0);
}
