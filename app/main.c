#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{
  printf("hello world\n");
  
  int c;

    while ((c = getopt (argc, argv, "abc:")) != -1)
    switch (c)
      {
      // Print version
      case 'v':
        printf("OS Version: %c.%c", lab_VERSION_MAJOR, lab_VERSION_MINOR);
        break;
      case 'b':
        printf("get b here");
        break;
      case 'c':
        printf("get c here");
        break;
      case '?':
        if (isprint(c))
          fprintf(stderr, "Unknown option %c", c);
        else
          fprintf(stderr, " Unknown option %c", c);
        return 1;
      default:
        abort();
        break;
      }

  return 0;
}
