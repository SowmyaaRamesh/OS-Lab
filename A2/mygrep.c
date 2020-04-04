#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include <fcntl.h>


void main(int argc,char *argv[])
{
    int fd,c,i=0,count=0;

    char ch,line[100];

    if((fd=open(argv[2],O_RDONLY))!= -1)
    {
        while((c=read(fd,&ch,sizeof(char)))!= 0)
        {
            if(ch!='\n')
            {
                line[i]=ch;
                i++;
            }
            else
            {
		line[i]='\0';
                if(strstr(line,argv[1])!=NULL)
		{
		    count++;
                    printf("%s\n",line);
		}
                strcpy(line,"");
                i=0;
            }

        }

	printf("No. of occurence=%d\n",count);
    }   
}

/*
[csec159@sel-16 ~]$ cat hello
hello there
I just wanted to say hello
hello is a nice word
Just say hello
yolo
You only live once

[csec159@sel-16 ~]$ gcc -o a mygrep.c
[csec159@sel-16 ~]$ ./a hello hello
hello there
I just wanted to say hello
hello is a nice word
Just say hello
No. of occurence=4
*/

