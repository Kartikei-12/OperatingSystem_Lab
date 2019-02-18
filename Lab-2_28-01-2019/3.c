// Geting PID of child and parent processes

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    if(fork() == 0)
        printf("Child Process\nPID: %d\n", getpid());
    else
        printf("\nParent Process\nPID: %d\n", getpid());
    return 0;
}