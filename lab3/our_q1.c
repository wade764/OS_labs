#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
   Write a programthatcallsfork().
   Before calling fork(), have the main process access a variable (e.g., x) and set its value to something (e.g., 100).
   What value is the variable in the child process?
   What happens to the variable when both the child and parent change the value of x?
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
