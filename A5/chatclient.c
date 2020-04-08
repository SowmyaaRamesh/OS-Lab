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
    int id_c,n,count=0,turn_id_c;


    text=(char*)malloc(50*sizeof(char));

    id_c=shmget(140,50,0);
    turn_id_c=shmget(460,10,0);

    text=shmat(id_c,NULL,0);
    turn=shmat(turn_id_c,NULL,0);

    printf("Server:%s\n",text);
    strcpy(text,"");

    while(strcmp(text,"exit")!=0)
    {
        if(turn[0]==0)
        {
            if(count!=0)
                printf("Server:%s\n",text);

            printf("Client:");
            gets(text);
            count++;
            turn[0]=1;

        }



    }

    shmdt(text);
    shmdt(turn);
    shmctl(id_c, IPC_RMID,NULL);
    shmctl(turn_id_c, IPC_RMID,NULL);

}

/*
sowmya@LAPTOP-IJOMHH91:~$ gcc -o b chatclient.text

sowmya@LAPTOP-IJOMHH91:~$ ./b
Server:hey
Client:Hello
Server:how are you
Client:I'm fine.What about you
Server:I'm good too
Client:Good to hear that.
*/