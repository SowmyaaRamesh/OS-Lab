#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *dirp;

    if ((dp = opendir(argv[1])) == NULL)
        printf("ERROR! Unable to open %s", argv[1]);

    while ((dirp = readdir(dp)) != NULL){
        struct stat fileStat;
        stat(dirp->d_name,&fileStat);   
 
       
      
        printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
        printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
        printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
        printf("\t");
        printf("%d  ",fileStat.st_nlink);
        printf("%ld  ",(long)fileStat.st_uid);
        printf("%ld  ",(long)fileStat.st_gid);
        printf("%lld",(long long)fileStat.st_size);  
        printf("\t%s ",ctime(&fileStat.st_mtime)); 
        printf(dirp->d_name);
        printf("\n");
        
    }
    return 0;
}

/*
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>gcc -o a mylsl.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>a .
drwxrwxrwx      1  0  0  0      Wed Jan 15 16:45:17 2020
 .
drwxrwxrwx      1  0  0  0      Tue Jan 14 23:01:12 2020
 ..
-rwxrwxrwx      1  0  0  148204 Wed Jan 15 16:45:17 2020
 a.exe
-rw-rw-rw-      1  0  0  83     Wed Jan 15 16:01:01 2020
 file.txt
-rw-rw-rw-      1  0  0  173    Wed Jan 15 01:56:23 2020
 file1.txt
-rw-rw-rw-      1  0  0  0      Wed Jan 15 01:46:23 2020
 hello
-rw-rw-rw-      1  0  0  780    Tue Jan 14 23:02:03 2020
 mycp.c
-rw-rw-rw-      1  0  0  1945   Wed Jan 15 01:57:25 2020
 mycpi.c
-rw-rw-rw-      1  0  0  1051   Tue Jan 14 23:02:14 2020
 mygrep.c
-rw-rw-rw-      1  0  0  777    Wed Jan 15 02:13:18 2020
 mygrepc.c
-rw-rw-rw-      1  0  0  704    Wed Jan 15 15:59:18 2020
 mygrepn.c
-rw-rw-rw-      1  0  0  778    Wed Jan 15 16:02:06 2020
 mygrepv.c
-rw-rw-rw-      1  0  0  483    Tue Jan 14 23:02:09 2020
 myls.c
-rw-rw-rw-      1  0  0  1398   Wed Jan 15 16:45:14 2020
 mylsl.c
-rw-rw-rw-      1  0  0  570    Wed Jan 15 16:06:35 2020
 mylsr.c
drwxrwxrwx      1  0  0  0      Wed Jan 15 16:04:48 2020
 sample
*/