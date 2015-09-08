/*
	./a.out rm file_1 file_2 .... file_n
		: deletes n files without confirmation.
	./a.out rm -i file_1 file_2 .... file_n
		: deletes n files after the user confirms the deletion.
	(doesn't check for directory)
*/
#include <stdio.h>
int main(int argc, char **argv)
{
	int pos;
	char ch='y';
	if(argv[1][0]!='-')
		pos=1;
	else pos=2;
	if(pos==2)
	{
		printf("remove file(s)?(y/n)\n");
		scanf("%c",&ch);	
	}
	if(ch=='y'||ch=='Y')
	{
		for(int i=pos;i<argc;i++)
			remove(argv[i]);
	}
	return 0;
}
