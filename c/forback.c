#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "forback.h"


/* start the program specified by filename with the arguments in argv 
   in a new process and wait for termination */
int foregroundcmd(char *filename, char *argv[])
{
  pid_t pid = fork();
  int status = -1;
  if(0 == pid)
  {
    execvp(filename, argv);
  }
  else
  {
    waitpid(pid, &status, 0);
  }
  return 0;
}

/* start the program specified by filename with the arguments in argv 
   in a new process */
int backgroundcmd(char *filename, char *argv[])
{
  pid_t pid = fork();
  if(0 == pid)
  {
    execvp(filename, argv);
  }
  return 0;
}
