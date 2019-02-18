// Exploring fork()
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    fork();
    fork();
    fork();
    printf("Hello\n");
    return 0;
}