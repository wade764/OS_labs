#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

/*
Write a program (q8.c) that creates two children, and connects the standard output of
one to the standard input of the other, using the pipe system call. One child is the reader
and the other child is the writer. The program reads a string argument from the command
line. The writer child process writes to the pipe (a) the string argument (b) followed by
some other string (c) followed by closing the pipe. The reader child process reads from
the pipe until it is closed. The reader child process must print to standard output the
string received on the pipe followed by the reverse of the string argument. The following
demonstrates the running of this program.

./q8 gusty
Parent of two children connected via pipe. (pid:8587)
parentpid:8587 of child1pid:8588 and child2pid:8589
child 1: pipe reader: (pid:8588)
child 2: pipe writer: (pid:8589)
gustyCooperytsug
childpid: 8589 finished
childpid: 8588 finished

The following demonstrates running the program without the string argument.
$ ./q8
usage: q8 <string>
 */

int main(int argc, char *argv[])
{
    int x = 100;

    printf("This is the value of x before calling fork(): %d\n", x);

    int didIFork = fork();
    if (didIFork < 0)
    {
        // fork returned a negative value indicating that the fork
        // function failed to create a child process

        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (didIFork == 0)
    {
        // fork is running the child process
        printf("Hello Gusty, I am the child process: %d\n", (int)getpid());
        printf("This is the value of x from the child: %d\n", x);
        x = 215;
        printf("The child changed x to: %d\n", x);
    }
    else
    {
        // the return value of fork is greater than 0 and is the parent

        printf("Hello I am the parent: %d\n", (int)getpid());
        printf("This is the value of x from the parent: %d\n", x);
        x = 45;
        printf("The parent changed x to: %d\n", x);
    }


    printf("This pid: %d, is about to return, x = %d\n",(int) getpid(), x);
    return 0;
}
