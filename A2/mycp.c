

#include<stdio.h>
#include <fcntl.h>
#include<errno.h> 
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>


void main(int argc,char** argv)
{


	char buf[100];
	
	
	
	int c=creat(argv[2],777);
	if(c==-1)
	{
		printf("Cannot create file %s.\n",argv[2]);
	}

	int f1=open(argv[1],O_RDONLY);
	int f2=open(argv[2],O_WRONLY);

	if(f1==-1)
	{
		printf("Error in opening:%s.\n",argv[1]);
	}

	if(f2==-1)
	{
		printf("Error in opening:%s.\n",argv[2]);
	}
	
	int r=read(f1,&buf,50); 
    	r=write(f2,buf,strlen(buf));
  
    	printf("Copy Successful\n"); 
  
    	close(f1); 
    	close(f2); 
	

}

/*
[csec159@sel-16 ~]$ cat hello
hello there
[csec159@sel-16 ~]$ gcc -o a mycp.c
[csec159@sel-16 ~]$ ./a hello copy
Copy Successful
[csec159@sel-16 ~]$ cat copy
hello there
*/
