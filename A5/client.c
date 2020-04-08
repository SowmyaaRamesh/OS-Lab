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


int main()
{
	char *b;
	char name[20];
	int id;
	char buf[50];

	
	id=shmget(200,50,0);	
	sleep(5);	
	printf("In client\n");
	printf("Printing file contents of read.txt\n");
	b=shmat(id,NULL,0);
	printf("%s\n",b);
	shmdt(b);
	shmctl(id, IPC_RMID,NULL); 


}

/*
sowmya@LAPTOP-IJOMHH91:~$ cat read
This is a test to check IPC using shared memory.
[csec172@sel-20 Desktop]$ gcc -o b client.c
[csec172@sel-20 Desktop]$ ./b
In client
Printing file contents of read.txt
This is a test to check IPC using shared memory.
*/
