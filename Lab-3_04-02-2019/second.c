#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t cpid;
	int status = 33;
	if(fork()==0)
	{
		printf("1Child's ID: %d\n", getpid());
		_exit(21);
	}
	else
		cpid = wait(&status);
	printf("2Paraent's ID: %d\n", getpid());
	printf("3Child's ID: %d\n", cpid);
	printf("4Status: %d\n", WEXITSTATUS(status));
	return 0;
}
