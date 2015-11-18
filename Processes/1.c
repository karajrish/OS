//executing fork and exec
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	int x = 1;
	int returnValue = fork();
	if(returnValue == 0)
	{
		printf("Child process = %d\n", ++x);
	}
	else
	{
		//only parent process executes
		printf("parent process = %d\n", --x);
	}
	printf("exiting with x = %d\n",x);
	return 0;
}
