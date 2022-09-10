#include <fcntl.h> // used for the open() function
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Write a program (q2.c) that opens a 
file (with the open system call) and then calls fork to create a new process.
*/

int main(int argc, char **argv) {
    
    const char *path = 
    "./questionTwo.txt"; // this is the current working directory

    //int didItOpen = open(path, 0); // passing a null oflag. this runs and causes no issues
    //int didItOpen = open(path, O_RDWR); // passing a read/write oflag, this runs and causes no issues
    int didItOpen = open(path, O_APPEND); // passing an append flag

    // The code below was duplicated from our_q1.c and slightly modified

    // in class Gusty said the there are 3 files that are open unless specifically
    // closed these files are STDIN STDOUT STDERR the next file to be opened will
    // have a return value of 3 returned from open()

    int x = 100;

    int didIFork = fork();
    if (didIFork < 0) {
        printf("Fork failed: This is the return value of open(\"./questionTwo\"): %d\n",
                didItOpen);

        // fork returned a negative value indicating that the fork
        // function failed to create a child process

        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (didIFork == 0) {
        printf("From child process: This is the return value of open(\"./questionTwo\"): %d\n",
                didItOpen);

        // fork is running the child process
        printf("Hello Gusty, I am the child process: %d\n", (int)getpid());

        //printf("This is the value of x from the child: %d\n", x);
        //x = 215;
        //printf("The child changed x to: %d\n", x);
    } else {
        printf("From parent process: This is the return value of open(\"./questionTwo\"): %d\n",
                didItOpen);

        // the return value of fork is greater than 0 and is the parent

        printf("Hello I am the parent: %d\n", (int)getpid());
        //printf("This is the value of x from the parent: %d\n", x);
        //x = 45;
        //printf("The parent changed x to: %d\n", x);
    }

    //printf("This pid: %d, is about to return, x = %d\n", (int)getpid(), x);
    printf("This pid: %d, is about to return\n", (int)getpid());
    return 0;
}
