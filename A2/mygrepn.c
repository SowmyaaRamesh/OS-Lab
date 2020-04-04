#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>

int main(int argc, char **argv)
{
	
	int fd,r,i=0,lineno=1;
	char line[100];
	char c;


	if((fd=open(argv[2],O_RDONLY))!=0)
	{

		while((r=read(fd,&c,sizeof(char)))!=0)
		{
			if(c!='\n')
			{
				line[i++]=c;	
			}

			else
			{
				line[i]='\0';
				if(strstr(line,argv[1])!=NULL)
					printf("%d. %s\n",lineno,line);
				memset(line,0,sizeof(line));
				i=0;
				lineno++;
			}
		}
	}

	return 0;
}

/*

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>gcc -o a mygrepn.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>a am file.txt
1. Who am I?
2. I am Sowmya.
3. I am a student at SSN.

*/

		
