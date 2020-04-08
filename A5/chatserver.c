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

    char *text;
    int *turn;
    int id,count=1,turn_id;

    text= (char*)malloc(50*sizeof(char));
   
    if((id=shmget(140,50,IPC_CREAT|00666))<0)
    {
            perror("shmget id failed\n");
            exit(-1);
    }

    if(( turn_id=shmget(460,10,IPC_CREAT|06666))<0)
    {
            perror("shmget turn fail\n");
            exit(-1);
    }


    text=shmat(id,NULL,0);
    turn=shmat(turn_id,NULL,0);
    turn[0]=1;//when turn contains 1 it's the server's turn. When it's 0, it's the client's turn.
    printf("Type exit to end chat.\n");
    strcpy(text,"");

    while(strcmp(text,"exit")!=0)
    {
        if(turn[0]==1)
        {

            if(count>1)
            {
                printf("Client:%s\n",text);
            }
            printf("Server:");
            gets(text);

            turn[0]=0;//client's turn next
            count++;

        }


    }
        shmdt(text);
        shmdt(turn);
        shmctl(id,IPC_RMID,NULL);
        shmctl(turn_id,IPC_RMID,NULL);

}

/*

sowmya@LAPTOP-IJOMHH91:~$ gcc -o a chatserver.c

sowmya@LAPTOP-IJOMHH91:~$ ./a
Type exit to end chat.
Server:hey
Client:Hello
Server:how are you
Client:I'm fine.What about you
Server:I'm good too
Client:Good to hear that.
Server:exit
*/