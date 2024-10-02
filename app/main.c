#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../src/lab.h"
#include "stdbool.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "sys/types.h"
#include "sys/wait.h"
#include <signal.h>

int main(int argc, char **argv)
{
  char *prompt;
  char *line;
  char **linePointer;
  char **lineRetPointer;
  bool validCommand;
  struct shell myShell;
  int c;
  int process_counter = 0;
  bool ambFlag;

  while ((c = getopt(argc, argv, "v")) != -1)
    switch (c)
    {
    // Print version
    case 'v':
      printf("OS Version: %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    case '?':
      if (optopt == 'c')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      return 1;
    default:
      abort();
      break;
    }

  /* Implement Custom Prompt Here */

  sh_init(&myShell);
  prompt = get_prompt("MY_PROMPT");
  myShell.prompt = prompt;

  /* Now begin user process to handle user input */
  using_history();
  while ((line = readline("$")))
  {
    /* Print the line */
    printf("%s\n", line);

    /* Add to the history */
    add_history(line);

    /* Trim Whitespace */
    line = trim_white(line);

    /* Parse the CommandLine */
    lineRetPointer = cmd_parse(line);
    linePointer = *(&lineRetPointer);

    


    /* Free the line */
    cmd_free(linePointer);

    //=====================================================================================================
    //       Unable to implement-- used for Task 9+
    //=====================================================================================================
    //  Note - if you uncomment this, move the cmd_free(linePointer) above to below this code,
    //         and comment out the above stuff (also located between '===')
    //=====================================================================================================
    // /* Search for & */
    // // Walk through string array to find last valid string
    // int idx = 0;
    // while (linePointer[idx] != NULL)
    // {
    //   idx++;
    // }
    // idx--;

    // // Check for '&' symbol as final arg
    // char *stringWAmbs = strchr(linePointer[idx], '&');
    // if (stringWAmbs != NULL)
    // {
    //   for (int j = 0; j < strlen(stringWAmbs) - 1; j++)
    //   {
    //     if (stringWAmbs[j] == '&')
    //     {
    //       stringWAmbs[j] = '\0';
    //       break;
    //     }
    //   }
    //   ambFlag = true;
    // }
    // else
    // {
    //   ambFlag = false;
    // }

    // // Split Child
    // pid_t pid;
    // pid_t parent_pid;
    // int retWaitVal;

    // pid = fork();
    // parent_pid = getppid();

    // // Check & and [print counter, pid, and cmd] if needed.
    // if (ambFlag)
    // {
    //   printf("[%d] %d %s\n", process_counter, getpid(), *linePointer);
    //   process_counter++;
    // }

    // if (pid < 0) // fork FAILED
    // {
    //   fprintf(stderr, "Error: Forking a process failed. Exiting Program.\n");
    //   cmd_free(linePointer);
    //   sh_destroy(&myShell);
    //   return (-1);
    // }
    // else if (pid == 0) // CHILD process
    // {
    //   int didItExecute = 0;

    //   pid_t child = getpid();
    //   setpgid(child, child);
    //   tcsetpgrp(myShell.shell_terminal, child);
    //   signal(SIGINT, SIG_DFL);
    //   signal(SIGQUIT, SIG_DFL);
    //   signal(SIGTSTP, SIG_DFL);
    //   signal(SIGTTIN, SIG_DFL);
    //   signal(SIGTTOU, SIG_DFL);

    //   validCommand = do_builtin(&myShell, linePointer);

    //   if (!validCommand) // Is it a builtIn Command? NO -> check cmd files
    //   {
    //     didItExecute = execvp(linePointer[0], linePointer);
    //     if (didItExecute == -1)
    //     {
    //       // It failed
    //       fprintf(stderr, "\'%s\' command does not exist.\n", linePointer[0]);
    //       cmd_free(linePointer);
    //       sh_destroy(&myShell);
    //       return (-1);
    //     }
    //     return 0; // Kill the child process? YES
    //   }
    // }
    // else // PARENT PROCESS ========================================
    // {
    //   int status = 0;

    //   if (!ambFlag) // If no flag, wait for child
    //   {
    //     waitpid(pid, &status, 0);                     // Set status of output of child process (if it finished)
    //     tcsetpgrp(myShell.shell_terminal, getpgrp()); // Reclaim terminal control
    //   }
    //   else
    //   {
    //     pid_t result;
    //     result = waitpid(pid, &status, WNOHANG); // Else periodically check on child
    //   }
    // }
  }

  /* Free All Items and Data */
  cmd_free(linePointer);
  sh_destroy(&myShell);

  return 0;
}
