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
        }
        else
        {
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

    /**
     * @brief Convert line read from the user into to format that will work with
     * execvp. We limit the number of arguments to ARG_MAX loaded from sysconf.
     * This function allocates memory that must be reclaimed with the cmd_free
     * function.
     *
     * @param line The line to process
     *
     * @return The line read in a format suitable for exec
     */
    char **cmd_parse(char const *line)
    {

        // If line is NULL -> CRTL + D so gtfo
        if (line == NULL)
        {
            cmd_free(&line);
            exit();
        }

        /* STEPS:
        1. Tokenize string to get arguments for
        */
        char *tokenArray = char * malloc(sizeof((char)) * _SC_ARG_MAX);

        // Parse line to get all args and commands
        char *token = strtok(line, " ");

        // Copy into array to be returned while respecting ARGMAX
        int tokenCounter = 0;
        while (token[i] != NULL || i < _SC_ARG_MAX)
        {
            tokenArray[i] = token[i];
            i++;
        }

        // Grab the first command from the tokenizer
        if (strcmp(token[0], "exit") == 0)
        { // EXIT
            cmd_free();
            exit();
        }

        /**
         * @brief Free the line that was constructed with parse_cmd
         *
         * @param line the line to free
         */
        void cmd_free(char **line)
        {
        }

        /**
         * @brief Trim the whitespace from the start and end of a string.
         * For example "   ls -a   " becomes "ls -a". This function modifies
         * the argument line so that all printable chars are moved to the
         * front of the string
         *
         * @param line The line to trim
         * @return The new line with no whitespace
         */
        char *trim_white(char *line)
        {
        }

        /**
         * @brief Takes an argument list and checks if the first argument is a
         * built in command such as exit, cd, jobs, etc. If the command is a
         * built in command this function will handle the command and then return
         * true. If the first argument is NOT a built in command this function will
         * return false.
         *
         * @param sh The shell
         * @param argv The command to check
         * @return True if the command was a built in command
         */
        bool do_builtin(struct shell * sh, char **argv);

        /**
         * @brief Initialize the shell for use. Allocate all data structures
         * Grab control of the terminal and put the shell in its own
         * process group. NOTE: This function will block until the shell is
         * in its own program group. Attaching a debugger will always cause
         * this function to fail because the debugger maintains control of
         * the subprocess it is debugging.
         *
         * @param sh
         */
        void sh_init(struct shell * sh);

        /**
         * @brief Destroy shell. Free any allocated memory and resources and exit
         * normally.
         *
         * @param sh
         */
        void sh_destroy(struct shell * sh);

        // /**
        //  * @brief Parse command line args from the user when the shell was launched
        //  *
        //  * @param argc Number of args
        //  * @param argv The arg array
        //  */
        // void parse_args(int argc, char **argv);

    }