/*
	does not delete if the provided file is a directory.
*/
	
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	int pos=1;
	char ch='y';
	struct stat eStat;

	if(strcmp(argv[1],"-i")==0)
		pos=2;

	for(int i=pos;i<argc;i++)
	{
		stat(argv[i],&eStat);
		if(S_ISDIR(eStat.st_mode))
			printf("rm: %s: is a directory\n",argv[i]);
		else
		{
			ch='y';
			if(pos==2)
			{
				printf("remove? (y/n) ");
				scanf("%c",&ch);	
			}	
			if(ch=='y' || ch=='Y')
			{
				if((unlink(argv[i]))!=0)
					printf("rm: %s: No such file or directory\n",argv[i]);
			}
		}
	}
	return 0;
}