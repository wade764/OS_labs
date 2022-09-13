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

// NOTES:
// https://www.geeksforgeeks.org/pipe-system-call/

//int pipe(int fds[2]);

//Parameters :
//fd[0] will be the fd(file descriptor) for the 
//read end of pipe.
//fd[1] will be the fd for the write end of pipe.
//Returns : 0 on Success.
//-1 on error.

// stdin == 0
// stdout == 1
// stderr == 2

int main(int argc, char *argv[])
{
    //int i = argc;
    //while(i != 0) { // was, argv != 0
    //    printf("This is argc: %d, and the argv: %s\n", i, *argv);
    //    i--;
    //    //if(argv[0][i] != 0)
    //    argv++;
    //}

    //TEST
    printf("this is argv[0] : %s and this is argv[1] : %s\n", argv[0], argv[1]);

    if(argc <= 1) { // the program shall take at minimum 2 commands
        printf("Please enter an argument ex: ./our_p8 <process name>\n");
        exit(1);
    }

    // *** Code between these comments came from geeksforgeeks referenced above 
    
    //char inbuf[16];
    //int p[2], i;
  
    //if (pipe(p) < 0)
    //    exit(1);
  
    ///* continued */
    ///* write pipe */
  
    //write(p[1], "msg1", 16); // 
    //write(p[1], "msg2", 16);
    //write(p[1], "msg3", 16);
  
    //for (i = 0; i < 3; i++) {
    //    /* read pipe */
    //    read(p[0], inbuf, 16);
    //    printf("%s\n", inbuf);
    //}
    
    // ***


    //int childOne = fork();
    //int childTwo = fork();
    
    //if (didIFork < 0)
    //{
    //    // fork returned a negative value indicating that the fork
    //    // function failed to create a child process

    //    fprintf(stderr, "fork failed\n");
    //    exit(1);
    //}
    //else if (childOne == 0)
    //{
    //    // fork is running the child process
    //    printf("I am the eldest child process: %d\n", (int)getpid());
    
    //}
    //else
    //{
    //    // the return value of fork is greater than 0 and is the parent

    //    printf("Hello I am the parent: %d\n", (int)getpid());
    //    
    //}


    ////printf("This pid: %d, is about to return, x = %d\n",(int) getpid(), x);
    return 0;
}