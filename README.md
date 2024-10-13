# Project 2 (Technically 6): Bounded Buffer Problem

* Author: Mark Muench
* Class: CS452 - Operating Systems
* Semester: Fall 2024

## Overview

## Reflection

## Compiling and Using

If you don't have it already, install a C compiler to your computer, then run:
`make clean` to clean any executable files.
`make` to build the program
and finally `./myprogram < -v >` (note, the '-v' is optional to print the version)

You could also run the program with a custom prompt using the following:
`<MY_PROMPT=foo> ./myprogram < -v >`

Upon running, the program requires user input in order to run.
Supported commands include:
> `cd <optional directory>`, `pwd`, `history`, and `exit`
> This program also supports commands that can be found by the `execvp` unix command.
Read about the documentation here: https://linux.die.net/man/3/execvp
> Users can create a process using `ls -l -a`.

_Note, this program can also be exited using `CRTL+D`_

