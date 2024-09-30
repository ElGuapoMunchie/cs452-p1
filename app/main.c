#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../src/lab.h"
#include "stdbool.h"
#include "readline/history.h"
#include "readline/readline.h"
#include "sys/wait.h"

int main(int argc, char **argv)
{
  char *prompt;
  char *line;
  char **linePointer;
  char **lineRetPointer;
  // char *retValPointer;
  // int errorNumber;
  bool validCommand;
  struct shell myShell;
  int c;

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

    /* Handle Args */
    validCommand = do_builtin(&myShell, linePointer);
    if (validCommand == false)
    {

      pid_t child_pid;
      pid_t wait_val;
      int retWaitVal;

      child_pid = fork();

      if (child_pid < 0)
      {
        fprintf(stderr, "Error: Forking a process failed. Exiting Program.\n");
        cmd_free(linePointer);
        sh_destroy(&myShell);
        return (-1);
      }
      else if (child_pid == 0)
      {
        // This is the child process
        int didItExecute = 0;
        didItExecute = execvp(linePointer[0], linePointer[1]);

        if (didItExecute == -1)
        {
          // It failed
          fprintf(stderr, "\'%s\' command does not exist.\n", linePointer[0]);
          cmd_free(linePointer);
          sh_destroy(&myShell);
          return (-1);
        }
      }
      else
      {
        // This is the parent process
        pid_t parent_pid = get_ppid(child_pid);
        int status;

        waitpid(-1, &status, 0);
        

      }

      // printf("\'%s\' is not a valid command.\n", linePointer[0]);

      // // Error and Abort
      // cmd_free(linePointer);
      // free(line);
      // sh_destroy(&myShell);
      // exit(-1);
    }

    /* Free the line */
    cmd_free(linePointer);
  }

  /* Free All Items and Data */
  cmd_free(linePointer);
  sh_destroy(&myShell);

  return 0;
}
