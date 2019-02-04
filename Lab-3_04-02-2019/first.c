#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int pid=33, status=34;
	pid = fork();
	if(pid==-1)
	{
		printf("Child not created.\n");
		return 1;
	}
	if(pid==0)
		printf("Child success\n");
	else
	{
		wait(&status);
		printf("Paraent Created\n");
	}
	return 0;
}
