#include<stdio.h>
#include <dirent.h>

void main(int argc,char** argv)
{
	struct dirent *de;  
  
   
    	DIR *dptr = opendir("lab"); 
  
    	if (dptr == NULL)  
    	{ 
        	printf("Could not open current directory" ); 
        	
    	} 
  
    	while ((de= readdir(dptr))!= NULL) 
            printf("%s\n", de->d_name); 
  
        closedir(dptr);   
}

/*
[csec159@sel-16 ~]$ ls lab
1  2  3  os

[csec159@sel-16 ~]$ gcc -o a myls.c
[csec159@sel-16 ~]$ ./a
.
..
2
1
os
3
*/
