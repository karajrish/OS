/*
	does not delete the directory. But goes into the directories and deletes non-directory files.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string>

void removeDirec(char *path, char *spaces)
{
	struct dirent *directoryPtr = NULL;
	struct stat eStat;
	DIR *dp = opendir(path);
	char x[1000];
	if(!dp) return;
	while((directoryPtr=readdir(dp))!=NULL)
	{
		if(strcmp(directoryPtr->d_name,".") && strcmp(directoryPtr->d_name,".."))
		{
			strcpy(x,path);
			path = strcat(path,"/");
			path = strcat(path,directoryPtr->d_name);
			stat(path,&eStat);
			if(S_ISDIR(eStat.st_mode))
			{
				char spc[1000];
				strcpy(spc,spaces);
				strcat(spc,"    ");
				removeDirec(path,spc);
			}

			printf("%s",spaces);
			if(unlink(path)==0)
				printf("%s deleted. \n",path);
			else
				printf("%s : is a directory\n",path);

			strcpy(path,x);
		}
	}
}

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
		{
			char str[100];
			str[0]=' ';
			removeDirec(argv[i],str);
		}
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
				if(unlink(argv[i])==0)
					printf("%s deleted. \n",argv[i]);
				else
					printf("%s : is a directory\n",argv[i]);
			}
		}
	}
	return 0;
}