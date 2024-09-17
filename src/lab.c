#include <string.h>
#include "../tests/harness/unity.h"
#include "lab.h"

const MAX_LENGTH = 4096;

char *get_prompt(const char *env){

    const char *MY_PROMPT = getenv(&env);

    char* ptr = (char *)malloc(sizeof(char *));

    if (MY_PROMPT == NULL){
        MY_PROMPT = "shell>";
    }



}
