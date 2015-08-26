#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
	int pos=1, sig = SIGKILL;
	char *temp;
	if(argv[1][0]=='-')
	{
		pos=2;
		temp=argv[1];
		temp++;
		sig = atoi(temp);
	}
	for(int i=pos;i<argc;i++)
		kill(atoi(argv[i]),sig);
    return 0;
}