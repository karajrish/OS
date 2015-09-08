/*
	./a.out wc file_1 file_2 ... file_n
		: Displays the numner of lines, characters and words in each file.
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
int main(int argc, char **argv)
{
	int val=0,pos=1;
	if(argv[1][0]=='-')
	{
		pos=2;
		if(strcmp(argv[1],"-l")==0)
			val=1;
		if(strcmp(argv[1],"-w")==0)
			val=2;
		if(strcmp(argv[1],"-c")==0)
			val=3;
		
	}
	for(int i=pos;i<argc;i++)
	{
		int fd = open(argv[i],O_RDONLY);
		char buff;
		int numChar=0, numWord=0, numLine=0;

		int x=0;
		while((read(fd,&buff,1))>0)
		{
			numChar++;
			if(buff=='\n')
				numLine++;

			if(x==0 && (buff==' ' || buff=='\t' || buff=='\n'))
			{
				numWord++;
				x=1;
			}
			else if(buff!=' ' && buff!='\t' && buff!='\n')
				x=0;
		}
		numWord++;
		printf("%s\n",argv[i]);
		if(val==0 || val==1) printf("Number of lines: %d\n", numLine);
		if(val==0 || val==2) printf("Number of words: %d\n", numWord);
		if(val==0 || val==3) printf("Number of chars: %d\n", numChar);
		printf("\n");
	}
}