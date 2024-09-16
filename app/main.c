#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{  
  printf("%c", **argv);

  int c;

    while ((c = getopt (argc, argv, "v")) != -1)
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
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort();
        break;
      }

  return 0;
}
