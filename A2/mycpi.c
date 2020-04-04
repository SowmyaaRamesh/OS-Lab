#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define SIZE 1024

int main(int argc, char** argv){

	int srcFD,destFD,nRead,nWrite;
	char buff[SIZE],ch;

	srcFD = open(argv[1],O_RDONLY);

	if(srcFD==-1){
		printf("File does not exist!");
	}

	destFD = open(argv[2],O_WRONLY);
	if(destFD==-1){
		destFD = open(argv[2],O_WRONLY|O_CREAT);
		if(destFD!=-1)
			goto cp;
	}

	else{
		printf("Do you want to overwrite '%s'? ",argv[2]);
		scanf(" %c",&ch);
		if(ch=='y')
			goto cp;
	}

	cp:
		while((nRead = read(srcFD,buff,SIZE)) > 0){
			if(write(destFD,buff,nRead) != nRead)
				printf("\nError in writing data to file");
			else
			{
				printf("Copy successful!");
			}
			
		}

		
		if(nRead == -1)
			printf("\nError in reading data from %s\n",argv[1]);

		if(close(srcFD) == -1)
			printf("\nError in closing file %s\n",argv[1]);
 
		if(close(destFD) == -1)
			printf("\nError in closing file %s\n",argv[2]);
			
}

/*

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>type file.txt
Back when dinosaurs existed, there used to be volcanoes that were erupting on the moon.

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>gcc -o a mycpi.c
C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>a file.txt copy
Copy successful!

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>type copy
Back when dinosaurs existed, there used to be volcanoes that were erupting on the moon.


C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>type file1.txt
Sunflowers can help clean radioactive soil. Japan is using this to rehabilitate Fukashima. Almost 10,000 packets of sunflower seeds have been sold to the people of the city.

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>a file1.txt copy
Do you want to overwrite 'copy'? y
Copy successful!

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A2>type copy
Sunflowers can help clean radioactive soil. Japan is using this to rehabilitate Fukashima. Almost 10,000 packets of sunflower seeds have been sold to the people of the city.

*/

		
