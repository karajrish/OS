#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
	DIR *first,*sec;
	struct dirent *f1,*f2;
	struct stat s;
	char ch[100],name[100],buf[10],dirt[100],f[100];// = "/proc";
	first = opendir("/proc");
	char dir[100]; getcwd(dir,sizeof(dir));printf("\n cwd %s\n",dir);
	printf("PID	TTY	TIME 	CMD\n");
	fork();
	while((f1 = readdir(first))!=NULL)
	{
		strcpy(ch,"/proc/");
		strcat(ch,f1->d_name);
		strcpy(dirt,f1->d_name);
		//printf("%s			",f1->d_name);
		
		sec = NULL;
		int x = stat(ch,&s);
		if(S_ISDIR(s.st_mode)&&f1->d_name[0]>='0'&&f1->d_name[0]<='9')
		{
			sec = opendir(ch);
			while((f2 = readdir(sec))!=NULL)
			if(strcmp(f2->d_name,"status")==0)
			{
				char file[100];strcpy(file,ch);strcat(file,"/");strcat(file,f2->d_name);
				int fd = open(file,O_RDONLY),k=0;
				read(fd,&buf,6);
				while(read(fd,&buf,1))
				{
					if(buf[0]=='\n')break;f[k++] = buf[0];
				}
					
			        read(fd,&buf,8);buf[8]='\0';
					if(buf[7]!='S'||argc>1){f[k]='\0';printf("%s			%s\n",dirt,f);}
			}
			
		}
	}

return 0;
}
