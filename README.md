# Project 2 (Technically 6): Bounded Buffer Problem


* Author: Mark Muench
* Class: CS452 - Operating Systems
* Semester: Fall 2024


## Overview


This project implements a queue and mutexes to solve the bounded buffer problem. This problem is considered a classic multithreading problem, and is solved via the usage of mutexes, and signal handlers to maintain and prevent problems that occur when multiple threads access the critical section of a program. These mutexes act as a sort of "lock" in which they lock
when a thread enters the critical section, so that only the single working thread can modify a variable as needed, and then 
unlock so that other threads may access that variable. 


## Compiling and Using


The recommended way to run this program is to use `Github Codespaces` to launch and run the program. However it can also be run
in your local MacOS or Linux environment (and Windows, but more on that later).

> Compiling using Codespaces:


First, open the project in a new codespace. Then, once the program has loaded, open a new `terminal` window and run the following to compile:
`$make clean`   // Removes old make files and cleans the repo
`$make`         // Compiles the program into an executable file

Then, run the program with:
`./myprogram [-c num consumer] [-p num producer] [-i num items] [-s queue size] <-d introduce delay>`


> Compiling and Running locally:


Please first ensure that your computer can compile and run C code and any needed dependencies:
Then run:
`make clean` to clean any executable files.
`make` to build the program
and finally `./myprogram [-c num consumer] [-p num producer] [-i num items] [-s queue size] <-d introduce delay>` 


> Using the tester files (`rapid-test` and `stress-test`)


To use the tester files, simply enter `./<rapid-test>` or `./stress-test` to run the program.
It should be noted that `stress-test` will output it's results into a new file called `test_output.txt`.


> Known issues with running (in codespaces):


Due to an unknown bug in github codespaces, you may encounter the following error:
`AddressSanitizer: DEADLYSIGNAL`. If you encounter this issue, or if `stress-test`
runs for more than 5 seconds (which means it's encountering the error and writing it
into the output file), please use `CRTL + C` in order to force-quit the program, and 
rerun the tests/program as needed.
