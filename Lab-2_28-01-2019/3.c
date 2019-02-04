// Geting PID of child and parent processes

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int pid, a;
    if(fork() == 0)
    {
        pid = getpid();
        printf("Child Process\nPID: %d\n", pid);
    }
    else
    {
        pid = getpid();
        printf("\nParent Process\nPID: %d\n", pid);
    }
    return 0;
}