# Changelist

> 10/19/2024
I've fixed all memory issues, all tests (whenever the address sanitizer bug doesn't show up)
are passing without any issues.

I made a second test file called "stress-test" that uses a bunch of for loops to test different
combinations of variables that a user could imput. The output of each of these tests is placed
into a file named `test_output.txt`.

One issue with the tester exists- it can't handle when an address sanitizer error occurs, so 
the program will just keep writing to the file for as long as it's running.

>10/18/2024
Good news first- `main.c` is running!

The "not so good" news:
- Running `main` has an intermittint locking error: `deq-lock` will engage and not give it up when `shutdown` gets flagged. 

>10/17/2024
I managed to pass all the tests. There's still a memory issue that's going on...
I think it's being caused by setting the elements to NULL when I free them? Either
that or I don't need to free items in the void* array.

Much to consider.

>10/17/2024
AHHHHHHHHHH
Maybe the Mutex isn't locking properly? How tf do I find the HBO?

> 10/17/2024
Good news first- I'm passing all the tests. I've got a bunch of memory leaks coming
from my init and destroy functions as shown by the tester, I've got a heap buffer overflow occurring when I allocate my pointer array, and there's 15,000 nukes at stake.

Just another day at the office.

And the bad news?

I'm getting sick of minecraft music.

> 10/15/2024

Check out this [link](https://www2.it.uu.se/education/course/homepage/os/vt20/module-4/bounded-buffer/#:~:text=The%20bounded%2Dbuffer%20problems%20(aka,read%20data%20from%20the%20buffer)
which explains the bounded-buffer-problem in depth. 

> 10/12/2024

I've added all of the starter code. I'm going to complete a drawing and visual
walkthrough so I have a thorough understanding of how everything is supposed to 
work before I begin implementing it.

Hopefully this makes it so that I don't waste time refactoring everything later 
on. 
