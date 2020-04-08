
#include <sys/ipc.h>
# define NULL 0 
#include <sys/shm.h> 
#include <sys/types.h> 
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h> 
#include <sys/wait.h> 
#include<ctype.h>

int main()
{
	int pid;
	char *a,*b,c; int id,n,i;
	char name[20];

	id=shmget(111,50,IPC_CREAT); 
	pid=fork();

	if(pid>0)
	{	

		a=shmat(id,NULL,0); 
		printf("Enter name:");
		scanf("%s",name);
		strcpy(a,name); 
		wait(NULL); 
		shmdt(a);
	}
	else
	{
		sleep(3); //id=shmget(111,50,0); 
		b=shmat(id,NULL,0); 
		printf("\n In child \n");
		printf("Name in uppercase:"); 
		for(i=0;i<=strlen(b);i++)
		{
			printf("%c",toupper(b[i]));
		}
		printf("\n");
		shmdt(b);
	}
}

/*
gml-20s-Mac-mini:downloads cse28$ gcc -o a ipc.c 
gml-20s-Mac-mini:downloads cse28$ ./a
Enter name:Sowmya

 In child 
Name in uppercase:SOWMYA
*/