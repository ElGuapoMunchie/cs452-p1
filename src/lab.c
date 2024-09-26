#include <string.h>
#include "../tests/harness/unity.h"
#include "lab.h"
#include "pwd.h"

#define MAX_LENGTH 10 // This may need to be adjusted for when you get the PATH
#define ARG_MAX 4096  // MAX SIZE allowed

uid_t user;        // UserID Type
struct passwd *pw; // Pointer to passwd struct
char *home;
char **homePtr;
bool retVal;

char *get_prompt(const char *env)
{
    if (getenv(env) != NULL)
    {
        char *retEnv = (char *)malloc(sizeof(char) * MAX_LENGTH);
        retEnv = strcpy(retEnv, getenv(env));
        // printf("%s", retEnv);
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
        // printf("%s", pmt);
        return pmt;
        free(pmt);
    }
}

void sh_init(struct shell *sh)
{
    /* Allocate Shell Memory --> DON"T NEED TO DO THIS*/
    // sh = (struct shell *)malloc(sizeof(struct shell));

    /* Initialize the shell with starter variables */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 1;
    sh->shell_tmodes.c_iflag = 0; // TODO: Does this need to be set? Set all off??
    sh->shell_terminal = 1;
    sh->prompt = NULL;
}

void sh_destroy(struct shell *sh)
{
    // TODO: May need to free other shell structures
    free(sh->prompt);
}

int change_dir(char **dir)
{
    int retVal;
    // printf("directory selected: %s\n", *(dir));

    /* Base Case: If NULL, find home directory and go to it */
    if (*(dir) == NULL)
    {
        user = getuid();
        pw = getpwuid(user);
        if (pw == NULL)
        {
            perror("user is not valid (pwuid is NULL)\n");
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
    // if (retVal == 0)
    // {
    //     printf("successfully changed directory\n");
    // }
    if (retVal != 0)
    {
        fprintf(stderr, "ch command failed. %s is not a valid directory.\n", *(dir));
    }
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
    /*
    NOTE: FIRST element of args will be the COMMAND.
          FINAL element of args will be the NULL POINTER.
     */
    char *lineCopy;
    char **arguments = (char **)malloc(sizeof(char *) * ARG_MAX); // Allocate memory for args
    char *token;
    int tracker = 0;

    // Check that there was enough space for arguments:
    if (arguments == NULL)
    {
        perror("Failed to allocate memory");
        exit(-1); // Exit if allocation fails
    }

    // Copy the line
    lineCopy = strdup(line);

    // Parse lineCopy to get command
    token = strtok(lineCopy, " ");
    arguments[tracker] = strdup(token);
    // printf("first token: %s\n", arguments[tracker]);

    tracker++;

    // Parse arguments
    token = strtok(NULL, " ");
    while (token != NULL && tracker < ARG_MAX - 1)
    {
        arguments[tracker] = strdup(token);
        // printf("next token: %s\n", arguments[tracker]);
        tracker++;

        // printf("%s\n", arguments[tracker]);
        token = strtok(NULL, " ");
    }

    arguments[tracker] = NULL; // Set end NULL pointer

    // Get retVal and GTFO
    return arguments;
}

/**
 * @brief Free the line that was constructed with parse_cmd
 *
 * @param line the line to free
 */
void cmd_free(char **line)
{
    free(*line);
    line = NULL;
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
// char *trim_white(char *line)
// {

// }

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
bool do_builtin(struct shell *sh, char **argv)
{
    /* Compare input args to argsList */
    retVal = false;

    /* Variables to do something? */
    char const *argv0 = argv[0];
    char **argv1ptr = &argv[1];

    // Exit Calls: ("exit" and CRTL+D)
    if (strcmp(argv0, "exit") == 0 || (argv0 == NULL))
    {
        retVal = true;
        if (argv != NULL)
        {
            for (int i = 0; argv[i] != NULL; i++)
            {
                free(argv[i]); // Free each string
            }
            free(argv); // Free the array of pointers
        }
        // free(*argv);

        /* Free the shell */
        sh_destroy(sh);
        exit(0);
    }

    // Change Directory:
    if (strcmp(argv0, "cd") == 0)
    {
        change_dir(argv1ptr);
        retVal = true;
    }
    return retVal;
}

/**
 * @brief Parse command line args from the user when the shell was launched
 *
 * @param argc Number of args
 * @param argv The arg array
 */
void parse_args(int argc, char **argv);