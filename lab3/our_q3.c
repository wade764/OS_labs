#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
/*
   Write another program using fork(). The child process should print “hello”; the parent process should print “goodbye”. 
   You should try to ensure that the child process always prints first; 
   Can you do this without calling wait() in the parent? You need some sort of synchronization technique.
 */
int main(int argc, char *argv[])
{

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
        printf("hello\n");
    }
    else
    {
        // the return value of fork is greater than 0 and is the parent
        sleep(3); // When we call sleep() the process get moved to the sleep queue
                  // when the child is finished the parent process will then complete
        printf("goodbye\n");
    }

    return 0;
}
