/*
	does not delete if the provided file is a directory.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string>
int main(int argc, char **argv)
{
	bool toConfirm=false;
	int pos=1;
	struct stat eStat;
	if(argc >= 2 && strcmp(argv[1],"-i")==0)
	{
		toConfirm=true;
		pos=2;
	}
	for(int i=pos;i<argc;i++)
	{
		stat(argv[i],&eStat);
		if(S_ISDIR(eStat.st_mode))
			printf("%s : is a directory\n",argv[i]);
		else
		{
			char ch='y';
			if(toConfirm)
			{
				printf("remove? (y/n)\n");
				scanf("%c",&ch);
			}
			if(ch=='y' || ch=='Y')
			{
				if(unlink(argv[i])!=0)
					printf("rm: %s: No such file or directory\n",argv[i]);
			}
		}
	}
	return 0;
}