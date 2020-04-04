#include<stdio.h>
#include<dirent.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>



void main()
{
    int f;
    struct dirent *de;
    struct dirent *DE;

    DIR *dp;

    DIR *dptr=opendir("C:/Users/Sowmya/Desktop/test");

    if(dptr==NULL)
    {
        printf("error\n");
    }

    while((de=readdir(dptr))!=NULL)
    {
        struct stat fileStat;
        stat(de->d_name,&fileStat);
        
        printf("%s\n",de->d_name);
        if(S_ISDIR(fileStat.st_mode))
        {
            
            dp=opendir(de->d_name);

            while((DE=readdir(dp))!=NULL)
            {
                printf("    %s\n",DE->d_name);
            }
        }
    }

    closedir(dptr);
    closedir(dp);
}