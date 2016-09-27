/* 

   Opgave 3

   pipe.c

 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "pipe.h"

   /* create a pipe between two new processes, executing the programs 
   specified by filename1 and filename2 with the arguments in argv1
   and argv2 and wait for termination */
int pipecmd(char *filename1, char *argv1[], char *filename2, char *argv2[])
{
  FILE *file;
  int nchar, fd[2];
  char buffer[10000],buffer2[10000];
  pipe(fd);
  int fid;
  pid_t pid = fork();
  
  if(pid == 0){
  	close(1);
  	fid = open(file, O_WRONLY);
  	dup2(1,fid);
  //	close(fd[1]);
  //	printf("%s\n","Stu");
  	execvp(filename1,argv1);
//  	printf("%s\n","Stuff");
//  	nchar = write(fd[1],buffer,sizeof(buffer));
//  	printf("%s\n","Stuff2");
  	//close(buffer);
  	exit(0);
  }
  else {
  	
  	int status;
  	waitpid(pid,&status,0);
  	
	int fod = open(file, O_RDONLY);

  	close(0);
  	dup2(fod,0);
  	//close(fd[0]);


  	//nchar = read(fd[0],buffer2,sizeof(buffer2));

  	printf("%s\n", "hello1");
  	char * argv3[] = {argv2[0], argv2[1], NULL};
  	printf("%s\n", "hello2");

  	printf("%s\n", argv2[0]);
  	printf("%s\n", argv2[1]);
  	printf("BUFFER: %s\n", buffer);

  	execvp(filename2,argv3);
  	close(buffer2);
  //	exit(0);
  }

  return 0;

  /*
	  
  if(pid == 0){
  	close(1);
  	dup2(fd[0], 1);
  	close(fd[1]);
  	execvp(filename1,argv1);
  }
  else {
  	close(0);
  	dup2(fd[1], 0);
  	close(fd[0]);
  	int status;
  	waitpid(pid,&status,0);
  	execvp(filename2,argv2);
  }

  */

}

int main(int argc, char* argv[]) {
	char * arg1[2] = {"ls",NULL};
	char * arg2[3] = {"wc","-l",NULL};
	//pipecmd(arg2[0],arg2,arg1[0],arg1);
	int status = pipecmd(arg1[0],arg1,arg2[0],arg2);
	return status;
}
