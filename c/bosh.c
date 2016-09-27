/* 

   bosh.c : BOSC shell 

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "parser.h"
#include "print.h"
#include "forback.h"
#include "redirect.h"

/* --- symbolic constants --- */
#define HOSTNAMEMAX 100

/* --- use the /proc filesystem to obtain the hostname --- */
char *gethostname(char *hostname)
{
  FILE *hostNameFile = fopen("/proc/sys/kernel/hostname", "r");
  fgets(hostname, sizeof(hostname), hostNameFile);
  return hostname;
}

/* --- execute a shell command --- */
int executeshellcmd (Shellcmd *shellcmd)
{
  printshellcmd(shellcmd);
  Cmd * cmdlist = shellcmd->the_cmds; 
  
  int fid, fod;
  char * in  = shellcmd->rd_stdin;
  char * out = shellcmd->rd_stdout;
  char **args = cmdlist->cmd;
  
  cmdlist = cmdlist->next;

  printf("cmd: %s\n", *args);
  printf("cmdlist: %s\n", cmdlist);

  if(out != NULL)
  {
    close(1);   
    fod = open(out, O_CREAT | O_WRONLY);  
    dup2(fod, 1);
  }
  if(in != NULL)
  {
    close(0);
    fid = open(in, O_RDONLY);
    dup(fid, 0);
  }

  shellcmd->background ? foregroundcmd(*args, &args[0]) : backgroundcmd(*args, &args[0]);
  close(fid);
  close(fod);
  return 0;
}

/* --- main loop of the simple shell --- */
int main(int argc, char* argv[]) {

  /* initialize the shell */
  char *cmdline;
  char hostname[HOSTNAMEMAX];
  int terminate = 0;
  Shellcmd shellcmd;
  
  if (gethostname(hostname)) {

    /* parse commands until exit or ctrl-c */
    while (!terminate) {
      printf("%s", hostname);
      if (cmdline = readline(":# ")) {
	if(*cmdline) {
	  add_history(cmdline);
	  if (parsecommand(cmdline, &shellcmd)) {
	    terminate = executeshellcmd(&shellcmd);
	  }
	}
	free(cmdline);
      } else { terminate = 1; printf("terminating\n"); }
    }
    printf("Exiting bosh.\n");
  }    
    
  return EXIT_SUCCESS;
}

