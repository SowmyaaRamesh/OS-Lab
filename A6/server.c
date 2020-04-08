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
#include <semaphore.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include<time.h>

extern int errno;
#define SIZE 20 /* size of the shared buffer*/
#define SHMPERM 0666

int shmid; /* id for shared memory bufer */
int empty_id;
int full_id;
int mutex_id;
int *buff;



sem_t *empty;
sem_t *full;
sem_t *mutex;


void produce()
{
    int i=0,j=1,n;
    int num[20];

    printf("Enter the no. of random no. to generate:");
    scanf("%d",&buff[0]);


    printf("Generating random numbers...\n");
    srand(time(0));

    for(i=1;i<=buff[0];i++)
    {
        num[i]=(rand()%(20-0+1));
    }


    while(1)
    {
        if(j>=i)
        {
            printf("\n Producer exited \n");
            exit(1);
        }

        printf("\nProducer trying to aquire Semaphore Empty \n");
        sem_wait(empty);

        printf("\nProducer successfully aquired Semaphore Empty \n");

        printf("\nProducer trying to aquire Semaphore Mutex \n");
        sem_wait(mutex);

        printf("\nProducer successfully aquired Semaphore Mutex \n");

        buff[j]=num[j];

        printf("\nProducer Produced Item [ %d ] \n",buff[j]);


        printf("\nItems in Buffer %d \n",j);
        j++;
        sem_post(mutex);

        printf("\nProducer released Semaphore Mutex \n");
        sem_post(full);

        printf("\nProducer released Semaphore Full \n");

    }
}

int main()
{

    if((shmid = shmget (213,SIZE, IPC_CREAT | IPC_EXCL | SHMPERM ))<0)
    {
            perror("shmid failed\n");
            exit(-1);
    }

     if((empty_id=shmget(301,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM))<0)
    {
            perror("empty_id failed\n");
            exit(-1);
    }

    if((full_id=shmget(920,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM))<0)
    {
            perror("full_id failed\n");
            exit(-1);
    }

    if((mutex_id=shmget(137,sizeof(sem_t),IPC_CREAT|IPC_EXCL|SHMPERM))<0)
    {
            perror("mutexid failed\n");
            exit(-1);
    }




    buff = shmat(shmid,NULL, 0 );
    empty = shmat(empty_id,(char *)0,0);
    full = shmat(full_id,(char *)0,0);
    mutex = shmat(mutex_id,(char *)0,0);

        
    // Initializing Semaphores Empty , Full & Mutex
    sem_init(empty,1,SIZE);
    sem_init(full,1,0);
    sem_init(mutex,1,1);

    printf("SERVER\n");
    produce();

    shmdt(buff);
    shmdt(empty);
    shmdt(full);
    shmdt(mutex);

    shmctl(shmid, IPC_RMID, NULL);

    semctl( empty_id, 0, IPC_RMID, NULL);
    semctl( full_id, 0, IPC_RMID, NULL);
    semctl( mutex_id, 0, IPC_RMID, NULL);

    sem_destroy(empty);
    sem_destroy(full);
    sem_destroy(mutex);

    printf("\n Server process exited \n\n");
    return(0);

}

/*
sowmya@LAPTOP-IJOMHH91:~$ gcc -o a server.c -lpthread
sowmya@LAPTOP-IJOMHH91:~$ ./a

SERVER
Enter the no. of random no. to generate:4
Generating random numbers...

Producer trying to aquire Semaphore Empty

Producer successfully aquired Semaphore Empty

Producer trying to aquire Semaphore Mutex

Producer successfully aquired Semaphore Mutex

Producer Produced Item [ 17 ]

Items in Buffer 1

Producer released Semaphore Mutex

Producer released Semaphore Full

Producer trying to aquire Semaphore Empty

Producer successfully aquired Semaphore Empty

Producer trying to aquire Semaphore Mutex

Producer successfully aquired Semaphore Mutex

Producer Produced Item [ 8 ]

Items in Buffer 2

Producer released Semaphore Mutex

Producer released Semaphore Full

Producer trying to aquire Semaphore Empty

Producer successfully aquired Semaphore Empty

Producer trying to aquire Semaphore Mutex

Producer successfully aquired Semaphore Mutex

Producer Produced Item [ 15 ]

Items in Buffer 3

Producer released Semaphore Mutex

Producer released Semaphore Full

Producer trying to aquire Semaphore Empty

Producer successfully aquired Semaphore Empty

Producer trying to aquire Semaphore Mutex

Producer successfully aquired Semaphore Mutex

Producer Produced Item [ 7 ]

Items in Buffer 4

Producer released Semaphore Mutex

Producer released Semaphore Full

 Producer exited
*/