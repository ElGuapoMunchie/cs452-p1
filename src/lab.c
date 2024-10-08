#include <string.h>
#include "../tests/harness/unity.h"
#include "../src/lab.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <pwd.h>
#include <bits/getopt_core.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#define _POSIX_SOURCE

#define MAX_LENGTH 10 // This may need to be adjusted for when you get the PATH
#define ARG_MAX 4096  // MAX SIZE allowed

uid_t user;        // UserID Type
struct passwd *pw; // Pointer to passwd struct
char *home;
char **homePtr;
bool retVal;
HIST_ENTRY **history_entries;
char cwd[1024];

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
    /* See if we are running interactively.  */
    sh->shell_terminal = STDIN_FILENO;
    sh->shell_is_interactive = isatty(sh->shell_terminal);

    if (sh->shell_is_interactive)
    {
        /* Loop until we are in the foreground.  */
        while (tcgetpgrp(sh->shell_terminal) != (sh->shell_pgid = getpgrp()))
            kill(-sh->shell_pgid, SIGTTIN);

        /* Ignore interactive and job-control signals.  */
        signal(SIGINT,  SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
        signal(SIGTSTP, SIG_IGN);
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);

        /* Put ourselves in our own process group.  */
        sh->shell_pgid = getpid();
        if (setpgid(sh->shell_pgid, sh->shell_pgid) < 0)
        {
            perror("Couldn't put the shell in its own process group");
            exit(1);
        }

        /* Grab control of the terminal.  */
        tcsetpgrp(sh->shell_terminal, sh->shell_pgid);

        /* Save default terminal attributes for shell.  */
        tcgetattr(sh->shell_terminal, &sh->shell_tmodes);
    }
}

void sh_destroy(struct shell *sh)
{
    // TODO: May need to free other shell structures
    free(sh->prompt);
}

int change_dir(char **dir)
{
    int retVal;

    /* Base Case: If NULL, find home directory and go to it */
    if (dir[1] == NULL)
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
    retVal = chdir(dir[1]);
    // if (retVal == 0)
    // {
    //     printf("successfully changed directory\n");
    // }
    if (retVal != 0)
    {
        fprintf(stderr, "\'cd\' command failed. \'%s\' is not a valid directory.\n", dir[1]);
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

    // TODO: If line is NULL, do nothing somehow.

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
        perror("Failed to allocate memory\n");
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

    // fprintf(stdout, "Printing arg[1]: %s\n", arguments[1]);
    free(lineCopy);

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
    for (int i = 0; line[i] != NULL; i++)
    {
        free(line[i]);
    }
    free(line);
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
char *trim_white(char *line)
{
    char *p = (char *)line; // Pointer to read from
    char *q;                // Pointer to write to

    // Count leading whitespace
    while (isspace((unsigned char)*p))
        p++;

    // Create a buffer to store the normalized string
    char *normalized = (char *)malloc(strlen(line) + 1); // Allocate maximum needed space
    if (!normalized)
    {
        perror("Failed to allocate memory");
        return NULL; // Return NULL on allocation failure
    }
    q = normalized; // Set the write pointer to the beginning of the buffer

    // Traverse through the string and normalize spaces
    while (*p != '\0')
    {
        // If the current character is not a space, copy it to the output
        if (!isspace((unsigned char)*p))
        {
            *q++ = *p; // Copy non-whitespace character
        }
        else if (q != normalized && *(q - 1) != ' ')
        {
            *q++ = ' '; // Replace multiple spaces with a single space
        }
        p++;
    }

    // Remove trailing whitespace
    if (q != normalized && isspace((unsigned char)*(q - 1)))
    {
        q--; // Move back to remove the last space if it exists
    }

    *q = '\0'; // Null terminate the modified string

    // Copy dup string to original, free dup
    strcpy(line, normalized);

    int i = 0;
    char c = line[i];
    while (c != '\0')
    {
        c = line[i];
        i++;
    }
    while (i < strlen(line))
    {
        line[i] = '\0';
    }

    free(normalized);

    return line; // Return the modified string
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
bool do_builtin(struct shell *sh, char **argv)
{
    /* Compare input args to argsList */
    retVal = false;

    /* Variables to do something? */
    char const *argv0 = argv[0];

    // Exit Calls: ("exit" and CRTL+D)
    int c = argv0[0];
    if (strcmp(argv0, "exit") == 0 || (c == EOF))
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

        // Clear history if not already gone
        // clear_history();
        // free(history_entries);

        printf("\n"); // print new line to make the console look pretty

        /* Free the shell */
        sh_destroy(sh);
        exit(0);
    }

    // Change Directory:
    if (strcmp(argv0, "cd") == 0)
    {
        change_dir(argv);
        retVal = true;
    }

    // History Command:
    if (strcmp(argv0, "history") == 0)
    {
        retVal = true;
        history_entries = history_list(); // Store the returned history entries
        if (history_entries)
        {
            // Print history to user
            for (int i = 0; history_entries[i] != NULL; i++)
            {
                printf("%d %s\n", i + 1, history_entries[i]->line);
            }
        }
        else
        {
            printf("No history available.\n");
        }
    }

    if (strcmp(argv0, "pwd") == 0)
    {
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
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