#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include "parser.h"

int runcmd(Shellcmd *shellcmd)
{
  Cmd *cmdlist = shellcmd->the_cmds;
  while(cmdlist != NULL)
  {
    char **cmd = cmdlist->cmd;
    cmdlist = cmdlist->next;
    if(strcmp(*cmd, "ls") == 0)
    {
      lscmd();
    }
    else if(strcmp(*cmd, "cat") == 0)
    {
      catcmd(cmdlist);
    }
    else if(strcmp(*cmd, "wc") == 0)
    {
      wccmd();
    }   
    else
    {
      printf("Command >%s< not found.\n", *cmd);
    }
    break;
  }
  return 0;
}

//displays names of all files in current directory
void lscmd()
{
  DIR           *d;
  struct dirent *dir;
  d = opendir(".");
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      printf("%s ", dir->d_name);
    }
    printf("\n");
    closedir(d);
  }
}

//Read file given in cmdlist.
//Only supports one file atm.
void catcmd(Cmd *cmdlist)
{
  if(cmdlist != NULL)
  {
    int c;
    char **cmd = cmdlist->cmd;
    FILE *file = fopen(*cmd, "r");
    if (file) 
    {
      while ((c = getc(file)) != EOF)
        putchar(c);

      fclose(file);
    }
    else printf("No file with given name found.\n");
  }
  else printf("Command >Cat< taking zero arguments not found.\n");
}

void wccmd()
{
  printf("wc\n");
}

/*
int executeshellcmd (Shellcmd *shellcmd)
{
  printshellcmd(shellcmd);
  Cmd *cmdlist = shellcmd->the_cmds;
  while(cmdlist != NULL)
  {
    char **cmd = cmdlist->cmd;
    cmdlist = cmdlist->next;
    if(strcmp(*cmd, "ls") == 0)
    {
      DIR           *d;
      struct dirent *dir;
      d = opendir(".");
      if (d)
      {
        while ((dir = readdir(d)) != NULL)
        {
          printf("%s ", dir->d_name);
        }
        printf("\n");
        closedir(d);
      }
    }
    else break;
  }
  return 0;
}

*/
