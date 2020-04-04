#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


void *calculateMin(void *param);
void *calculateMax(void *param);
void *calculateAvg(void *param);

//global variables to be used by all worker threads
int avg,min,max,num[20],len;

int main(int argc,char *argv[])
{
    int i;

    if(argc<=1)
    {
        fprintf(stderr,"\nError:Enter the numbers to work with.\n");
        return -1;
    }
    else
    {
        len=argc-1;

        //get the numbers from the string command line arguments
        for(i=1;i<argc;i++)//argv[0] will be filename
        {
            num[i-1]=atoi(argv[i]);
        }

        pthread_t min_tid,max_tid,avg_tid;
        pthread_attr_t attr_min,attr_max,attr_avg;

        //thread initiaisation
        pthread_attr_init(&attr_min);
        pthread_attr_init(&attr_max);
        pthread_attr_init(&attr_avg);

        //thread creation
        pthread_create(&min_tid,&attr_min,calculateMin,num);
        pthread_create(&max_tid,&attr_max,calculateMax,num);
        pthread_create(&avg_tid,&attr_avg,calculateAvg,num);

        //waiting for threads to terminate in the specified order
        pthread_join(min_tid, NULL); 
        pthread_join(max_tid, NULL);
        pthread_join(avg_tid, NULL);

        printf("\nThreads have been executed successfully!\n");

        printf("\nAverage is : %d\n", avg); 
        printf("Minimum is : %d\n", min);
        printf("Maximum is : %d\n\n", max);

        return 0;
    }
    
}


void *calculateMin(void *param)
{ 
    int i = 0;
    min = num[0];

    for (i = 1; i <len; i++)
    {
        if (num[i]<min)
        {
            min = num[i];
        }
    }

    pthread_exit(0);
}

void *calculateMax(void *param)
{ 
    int i = 0;
    max = num[0];

    for (i = 1; i <len; i++)
    {
        if (num[i]>max)
        {
            max = num[i];
        }
    }

    pthread_exit(0);
}

void *calculateAvg(void *param)
{ 
    int i = 0;
    avg = 0;

    for (i = 0; i < len; i++)
    {
        avg += num[i];
    }

    avg=avg/len;

    pthread_exit(0);
}

/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A13>gcc -o a threads.c
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A13>a

Error:Enter the numbers to work with.

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A13>a 1 2 3 4 5

Threads have been executed successfully!

Average is : 3
Minimum is : 1
Maximum is : 5
*/
