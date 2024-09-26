# Changelist
> 9/26/24

RECENT EVENTS
- `exit` command is working. Updated `sh_init` & `sh_destroy` to no longer malloc shell, \
shell object is initialized in Main, it's placed (allocated) on the stack and doesn't need to be\
 malloc'd.
- I fixed `cmd_parse` so that the `ARG_MAX` is respected and the tokenizer correctly \
tokenizes the string.

TODO
- figure out if `cmd_parse` actually parses the args (specifically arg[1] for cd)
- Learn more about `**char` and how they reference strings.

