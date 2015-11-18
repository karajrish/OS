#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
	pid_t childPID = fork();
	if(childPID < 0)
	{
		perror("fork() error");
		exit(-1);
	}
	if(childPID !=0)
	{
		printf("I'm the parent %d, my child is %d\n", getpid(), childPID);
	wait(NULL); //wait for child process to join with parent process
	}
	else
	{
		printf(" I am the child %d, my parent is %d\n", getpid(), getppid());
	execl("/bin/echo", "echo", "Hello World!", NULL);
	}

return 0;
}
