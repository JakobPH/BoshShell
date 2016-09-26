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
#include "parser.h"
#include "print.h"

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

  //pid = fork();

  printshellcmd(shellcmd);

  Cmd * cmd = shellcmd->the_cmds; 

  char * in  = shellcmd->rd_stdin;
  char * out = shellcmd->rd_stdout;
  char ** args = cmd->cmd;

  char * inArgs[] = {args[0],in,NULL};

  printf("%s\n", args);

  execvp(args[0],&inArgs[0]);
  //runcmd(shellcmd);
  //shellcmd->background ? forground : background);
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
      } else terminate = 1;
    }
    printf("Exiting bosh.\n");
  }    
    
  return EXIT_SUCCESS;
}
/* 
  printf("Shellcommand:\n");
  printf("   stdin : %s\n", shellcmd->rd_stdin  ? shellcmd->rd_stdin  : "<none>" );
  printf("   stdout: %s\n", shellcmd->rd_stdout ? shellcmd->rd_stdout : "<none>" );
  printf("   bg    : %s\n", shellcmd->background ? "yes" : "no");
  Cmd *cmdlist = shellcmd->the_cmds;
  while (cmdlist != NULL) {
    char **cmd = cmdlist->cmd;
    cmdlist = cmdlist->next;

    char **printcmd = cmd;
    printf("    [");
    while (*printcmd != NULL) {
      printf("%s ", *printcmd++); // print the cmd and arguments
    }
    printf("]\n");
*/

