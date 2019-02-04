#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

int main()
{
	int status=33, a=34; 
    pid_t pid=fork();
    if(pid == 0)
    {//Child
    	sleep(50);
    	printf("Child created\n");
        _exit(1);
    }
    else
    {//Paraent
    	a = kill(pid, SIGSTOP);
    	printf("Kill: %d\n",a);
    	//printf("Executing Wait\n");
        //wait(&status);   
    }
    if(WIFEXITED(status))
        printf("Exit status: %d\n", WEXITSTATUS(status)); 
    else if(WIFSIGNALED(status)) 
        printf("Exit with signal %d\n", WSTOPSIG(status));
	return 0;
}
