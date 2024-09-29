# Changelist

> 9/28/24
RECENT EVENTS:
- I need to find a way to free the memory stored from keeping a history list. I wonder if there's a way to clear it.

===== Completed =====
- I'm passing the tests for the `cd` command apparently. So that's good news.
- I've decided to ***prioritize the history command*** and completing the task. I think that fixing the memory leak in the tester will be a future me problem. Or at least something I don't need to
worry too much about.

TODO

===== Completed =====
- Fix memory leaks from the tester file.
- Add the rest of the commands into `do_builtin`.

> 9/26/24

RECENT EVENTS
- `exit` command is working. Updated `sh_init` & `sh_destroy` to no longer malloc shell, \
shell object is initialized in Main, it's placed (allocated) on the stack and doesn't need to be\
 malloc'd.
- I fixed `cmd_parse` so that the `ARG_MAX` is respected and the tokenizer correctly \
tokenizes the string.

TODO
- figure out if `cmd_parse` actually parses the args (specifically arg[1] for cd) --> Seems like it does
- Learn more about `**char` and how they reference strings.  --> Treat them like a string array. \
So we changed *(div) to div[1] to get the second part of whatever is being referred to.
