// Checking child and parent processes

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

void exam()
{
    if(fork() == 0)
        printf("Child Process\n");
    else
        printf("Parent Process\n");
}

int main()
{
    exam();
    return 0;
}