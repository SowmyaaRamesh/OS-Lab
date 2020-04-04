#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>

int main(int argc, char **argv)
{
	
	int fd,i=0,count=0;
	int r;

	char line[200];
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
				{
					count++;
				}
					
				memset(line,0,sizeof(line));
				i=0;
			}
		}
	}

	printf("Count=%d",count);

	return 0;
}

/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>type file.txt
Who am I?
I am Sowmya.
I am a student at SSN.

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>gcc -o b mygrepc.c
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>b am file.txt
Count=3

*/

		
