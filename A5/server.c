#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<ctype.h>
#include<fcntl.h>
//#include<stdio_ext.h>

int main()
{

	char *a;
	int id,n;
	char buf[50];
	int fd;
	fd=open("read",O_RDONLY);	
	int s1=read(fd,&buf,50);
	
	id=shmget(200,50,IPC_CREAT|00666);
	
		
	a=shmat(id,NULL,0);
	strcpy(a,buf);
	wait(NULL);
	shmdt(a);

}

/*
[csec172@sel-20 Desktop]$ gcc -o a server.c
[csec172@sel-20 Desktop]$ ./a
*/
