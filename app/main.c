#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{

  /* Read and process command line arguments */
  printf("%c", **argv);

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

  
  /* Now begin user process to handle user input */
  char *line;
  using_history();
  while ((line = readline("$")))
  {
    printf("%s\n", line);
    add_history(line);
    free(line);
  }

  return 0;
}
