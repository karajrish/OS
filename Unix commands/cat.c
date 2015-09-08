/*
	./a.out cat file_1 file_2 .... file_n
		: Displays content of all n files
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	for(int i=1;i<argc;i++)
	{
		int fd = open(argv[i],O_RDONLY);
		if(fd==-1)
			printf("cat: %s: No such file or directory\n",argv[i]);
		else
		{
			char buff;
			while((read(fd,&buff,1))!=0)
				printf("%c",buff);
			printf("\n\n\n");
		}
	}
}