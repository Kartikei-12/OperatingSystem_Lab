#include <wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(int argc, const char* const* argv)
{
    int *pointer=NULL;
    int status;
    pid_t pid=fork();
    if (pid==0) {
        printf("Child is: %d\n", getpid());
        if (argc>1) {
            printf("%d Going to crash myself\n",getpid());
            *pointer=1; //Segmentation fault as of null pointer dereference
        }
        else
            pointer=NULL; //Safe code
    }
    else {
        printf("Parent is: %d\n",getpid());
        pid_t terminated=waitpid(-1, &status, 0);
        printf("Child %d  exited ",terminated);
        if (WIFEXITED(status))
        	printf("GOOD\n");
        else {
             printf("BAD\n");
             // Is it worth here to also check for WIFSIGNALED or is it redundant?
        }
        printf("\n");
    }
    printf("%d exiting normally.\n",getpid());
    return 0;
}
