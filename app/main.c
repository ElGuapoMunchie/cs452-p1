#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"
#include "stdbool.h"

int main(int argc, char **argv)
{
  char *line;
  char **linePointer;
  char *retValPointer;
  int errorNumber;
  bool validCommand;
  struct shell *s;

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
  sh_init();
  sh->prompt = get_prompt("MY_PROMPT");

  /* Now begin user process to handle user input */
  using_history();
  while ((line = readline("$")))
  {
    /* Print the line */
    printf("%s\n", line);

    /* Add to the history */
    add_history(line);

    /* Trim Whitespace */
    // line = trim_white(line);

    /* Parse the CommandLine */
    cmd_parse(line);

    /* Handle Args */
    validCommand = do_builtin(sh, linePointer);
    if (validCommand == false){
      // Error and Abort
      cmd_free(linePointer);
      free(line);
      sh_destroy(s);
      exit(-1);
    }

    /* Free the line */
    cmd_free(linePointer);
  }

  /* Free All Items and Data */
  cmd_free(linePointer);
  sh_destroy(s);

  return 0;
}
