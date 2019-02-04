#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define num 5

int main()
{
	int i, stat; 
    pid_t pid[num];
    for (i=0; i<num; i++) 
        if((pid[i] = fork()) == 0) 
        { 
        	printf("Child %d calculating square of %d as %d\n", i+1, i+3, (i+3)*(i+3));
            sleep(1); 
            _exit(100 + i); 
        }
    
    //printf("Paraent executing now.\n");
    for(i=0; i<num; i++)
    {
        pid_t cpid = waitpid(pid[i], &stat, 0); 
        if(WIFEXITED(stat)) 
            printf("Child %d terminated with status: %d\n", cpid, WEXITSTATUS(stat)); 
    }
    return 0;
}
