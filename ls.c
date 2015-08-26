/*
	./a.out 			: 	displays all files(not starting with '.') one after the other
	./a.out -l 			:	displays all properties of every file
	./a.out -a 			:	displays even those files which begin with '.' one after the other
	./a.out <dirName> 	:	displays the content in <dirName> directory
	./a.out -R 			:	displays all files inside the current working directory
*/

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

struct dirent *directoryPtr = NULL;
DIR * dip = NULL;
char currDir[1024];
struct stat eStat;

struct node
{
	char fName[1024];
	node *next;
	node(char *item)
	{
		strcpy(this->fName,item);
		next=NULL;
	}
};

void addToList(node *&L, char *item)
{
	if(!L) L=new node(item);
	else addToList(L->next,item);
}

void ls()
{
	while((directoryPtr=readdir(dip))!=NULL)
	{
		if(directoryPtr->d_name[0]!='.')
			printf("%s\t",directoryPtr->d_name);
	}
}

void lsA()
{
	while((directoryPtr=readdir(dip))!=NULL)
		printf("%s\t",directoryPtr->d_name);
}

void lsR()
{
	node *L=NULL;
	addToList(L,currDir);
	while(L)
	{
		dip = opendir(L->fName);
		printf("%s: \n",L->fName);
		while((directoryPtr=readdir(dip))!=NULL)
		{
			if(directoryPtr->d_name[0]!='.')
			{
				printf("%s\t\t",directoryPtr->d_name);
				char temp[1024];
				strcpy(temp,L->fName);
				strcat(temp,"/");
				strcat(temp,directoryPtr->d_name);
				stat(temp,&eStat);
				if(S_ISDIR(eStat.st_mode))
					addToList(L,temp);
			}
		}
		L=L->next;
		printf("\n\n");
	}
}

void lsL()
{
	char P[10]="rwxrwxrwx", AP[10]=" ";
	int i,j;
	struct passwd *p;
	struct group *g;
	struct tm* t;
	char time[26];

	while((directoryPtr=readdir(dip))!=NULL)
	{
		stat(directoryPtr->d_name,&eStat);

		//File type.
		if(S_ISDIR(eStat.st_mode))
			printf("%c",'d');
		else if(S_ISREG(eStat.st_mode))
			printf("%c",'-');
		else if(S_ISBLK(eStat.st_mode))
			printf("%c",'b');
		else if(S_ISCHR(eStat.st_mode))
			printf("%c",'c');
		else if(S_ISLNK(eStat.st_mode))
			printf("%c",'l');
		else if(S_ISSOCK(eStat.st_mode))
			printf("%c",'s');
		else if(S_ISFIFO(eStat.st_mode))
			printf("%c",'p');

		//File permissions
		//P: Full permissions. AP: Actual permissions.
		for(i=0,j=256;i<9;i++,j=j/2)
			AP[i]=(eStat.st_mode & j)?P[i]:'-';
		printf(" %s",AP);
		
		//Number of Hard Links.
		printf(" %5d",eStat.st_nlink);

		//User name
		p = getpwuid(eStat.st_uid);
		printf(" %.9s",p->pw_name);

		//Group name
		g = getgrgid(eStat.st_gid);
		printf(" %-8.8s",g->gr_name);

		//File size.
		printf(" %8d",(int)eStat.st_size);
		
		//Data and Time of modification.
		t = localtime(&eStat.st_mtime);
		strftime(time,sizeof(time),"%b %d %H:%M:%S",t);
		printf(" %s",time);

		//File/Directory name.
		printf(" %s\n",directoryPtr->d_name);
	}
}

int main(int argc, char **argv)
{
	getcwd(currDir,sizeof(currDir));
	dip = opendir(currDir);
	if(argc==1) ls();
	else if(argc==2)
	{
		if(strcmp(argv[1],"-l")==0)
			lsL();
		else if(strcmp(argv[1],"-a")==0)
			lsA();
		else if(strcmp(argv[1],"-R")==0)
			lsR();
		else 
		{
			if((dip = opendir(argv[1]))==NULL)
				printf("ls: %s: No such file or directory\n",argv[1]);
			else ls();
		}
	}
	if(dip) closedir(dip);
	return 0;
}