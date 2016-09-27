#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "redirect.h"

/* start the program specified by filename with the arguments in argv 
   in a new process that has its stdin redirected to infilename and
   wait for termination */
int redirect_stdincmd(char *filename, char *argv[], char *infilename)
{
  pid_t pid = fork();
  int status = -1;
  if(0 == pid)
  {
    int fid = open(filename, O_RDONLY);
    
    close(0);
    dup(fid);

    execvp(filename, argv);
    
    close(fid);
  }
  else
  {
    waitpid(pid, &status, 0);
  }
  return 0;
}

/* start the program specified by filename with the arguments in argv 
   in a new process that has its stdout redirected to outfilename and 
   wait for termination */
int redirect_stdoutcmd(char *filename, char *argv[], char *outfilename)
{
  pid_t pid = fork();
  int status = -1;
  
  if(0 == pid)
  {
    int fid = open(filename, O_CREAT | O_WRONLY);
   
    dup2(fid, 1);
    
    execvp(filename, argv);
    close(fid);
  }
  else
  {
    waitpid(pid, &status, 0);
  }
  return 0;
}
