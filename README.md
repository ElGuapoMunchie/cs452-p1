# Project 1 (Technically 3): Simple Shell

* Author: Mark Muench
* Class: CS452 - Operating Systems
* Semester: Fall 2024

## Overview

This project represents an implementation of a simple shell program
in C. Upon launching the shell, users can call any unix-native commands, 
as well as commands such as `pwd`, `history`, `exit`, `cd`, which are 
handled internally. Additional functionality includes the user to create 
a process using `ls -l -a`.

## Reflection

This project was ***brutal***. Over the past 2 weeks, I have spent well over 61 
hours on this project (as documented by the codespace), in which I struggled
through the first 7 tasks, and then faltered with the 9th task and beyond.
Although I had a very basic knowledge of C, and had completely forgotten how 
to allocate and deallocate memory, I found that after the first week, things 
had started to progress a little more smoothly.

The point where things started to fall apart was when I hit task 9. Despite having
created a process, my inability to understand how the processes interacted, and how 
to terminate a process, ended up being my ultimate undoing. I wish we had been 
given a chance to see some examples in class about how these worked, because trying 
to parse the documentation ended up being a real challenge.

All in all, I'm proud of my work. I've worked my butt off, and despite having 
numerous other projects aligning with the deadline of this one, I'm proud of
what I was able to accomplish. I hope that future classes are given the opportunity
to complete Shane's first project- in which they can be refreshed on C, because this
was a good challenge and really pushed me as a programmer. 

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

