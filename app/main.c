#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{
  char *prompt;
  char *home;
  char **homePtr;
  int success;
  char *path;

  int c;

  while ((c = getopt(argc, argv, "v")) != -1)
    switch (c)
    {
    // Print version
    case 'v':
      printf("OS Version: %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    case 'b':
      printf("get b here");
      break;
    case 'c':
      printf("get c here");
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
  prompt = get_prompt("MY_PROMPT");

  /* Now begin user process to handle user input */
  char *line;
  // char *lineCompare = "";
  using_history();
  while ((line = readline("$")))
  {
    printf("%s\n", line);
    add_history(line);
    if (strcmp(line, "exit") == 0 || line == NULL) // EXIT
    {
      free(line);
      break;
    }
    if (strncmp(line, "cd", 2) == 0)
    { // 'cd' CHANGE DIRECTORY

      /* Case1: User enters nothing -> GOTO home directory*/
      /*
      - Readline -> delimmit on whitespace
      - Check for 'cd'
      - anything after that is 
      */
      if (strcmp(line, "cd") == 0) // Litterally just "cd"
      {
        home = getenv("HOME");
        homePtr = &home;
        success = change_dir(homePtr);

        if (success == -1){ // ERROR ENCOUNTERED
          exit(1);
        }
      }

      /* Case2: Change directory --> match directory name, goto directory || print error */

    }
    free(line);
  }

  /* Free All Items and Data */
  free(prompt);

  return 0;
}
