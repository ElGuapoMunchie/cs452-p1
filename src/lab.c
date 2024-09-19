#include <string.h>
#include "../tests/harness/unity.h"
#include "lab.h"
#include "pwd.h"

#define MAX_LENGTH 10 // This may need to be adjusted for when you get the PATH

uid_t user;        // UserID Type
struct passwd *pw; // Pointer to passwd struct

char *get_prompt(const char *env)
{
    if (getenv(env) != NULL)
    {
        char *retEnv = (char *)malloc(sizeof(char) * MAX_LENGTH);
        retEnv = strcpy(retEnv, getenv(env));
        return retEnv;
        free(retEnv);
    }
    else
    { // Env must be NULL
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

int change_dir(char **dir)
{
    int retVal;

    /* Base Case: homeDir == Null, find HomeDir, goto HomeDir else throw error */
    if (*(dir) == NULL)
    {
        user = getuid();
        pw = getpwuid(user);
        if (pw == NULL)
        {
            perror("user is not valid (pwuid is NULL)");
            return -1;
        }
        retVal = chdir(pw->pw_dir); // Move to user's homeDir
        if (retVal == 0)
        {
            return retVal;
        } else {
            return retVal;
        }
    }

    /* Case: Directory NOT NULL, goto directory */
    retVal = chdir(*(dir));
    if (retVal == 0)
    {
        printf("%s~", *(dir));
        return retVal;
    }
    else
    {
        return retVal;
    }
}