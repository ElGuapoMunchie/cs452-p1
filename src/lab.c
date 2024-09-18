#include <string.h>
#include "../tests/harness/unity.h"
#include "lab.h"

#define MAX_LENGTH 10 // This may need to be adjusted for when you get the PATH

char *get_prompt(const char *env)
{
    if (getenv(env) != NULL)
    {
        printf("Env not null");
        char *retEnv = (char *)malloc(sizeof(char) * MAX_LENGTH);
        retEnv = strcpy(retEnv, getenv(env));
        return retEnv;
        free(retEnv);
    }
    else
    { // Env must be NULL
        printf("Env NULL");
        char *pmt = (char *)malloc(sizeof(char) * MAX_LENGTH);
        pmt[0] = 's';
        pmt[1] = 'h';
        pmt[2] = 'e';
        pmt[3] = 'l';
        pmt[4] = 'l';
        pmt[5] = '>';
        pmt[6] = '\0';
        return pmt;
        free(pmt);
    }
}

void sh_init(struct shell *sh)
{
    /* Initialize the shell with starter variables */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 1;
    sh->shell_tmodes.c_iflag = 1;
    sh->shell_terminal = 1;
    sh->prompt = "";
}

void sh_destroy(struct shell *sh)
{
    free(sh);
}