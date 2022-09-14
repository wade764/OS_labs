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

   Expected output:

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

    // This will exit the program if no additional arguments are passed
    if(argc <= 1) { // the program shall take at minimum 2 commands
        printf("usage: q8 <string>\n");
        exit(1);
    }

    // Code below was from p6.c, but was modified

    int p[2]; // in class this was set to two index 0 for stdin and 1 for the child's file
    char *excargv[3];

    pipe(p); // This initializes the contents of p to the next filedescriptors available

    printf("Parent of two children connected via pipe. (pid:%d)\n", (int) getpid());

    int c1Pid = fork(); // calling fork here for the first time
    int c2Pid, argLen = 0;

    if(argv[1] != 0) {
        argLen = strlen(argv[1]);
    }

    //TEST
    //printf("This is the strlen of the argument: %d\n", argLen);

    if(c1Pid == 0) {

        printf("child 1: pipe reader: (pid:%d)\n", getpid());
        dup2(p[1], 1); // dup pipe write end on top of stdout

        close(p[0]);

        char *theArg = strdup(argv[1]); // duplicating the argument variable

        strcat(theArg, "Cooper");

        write(1, theArg, strlen(theArg)); // writing the argument to stdout

        close(p[1]);

        // *** ISSUE ON THIS LINE ADDED A LEADING \n TO SORT OF GET IT TO PRINT RIGHT 
        printf("\nchildpid: %d finished\n", getpid());
    } else {
        c2Pid = fork(); // calling the second process via fork()
        if (c2Pid == 0) {
            printf("child 2: pipe writer: (pid:%d)\n", getpid());
            dup2(p[0], 0); // dup pipe read end on top of stdin

            char buf[100];

            int r = read(0, buf, 80);

            //close(p[1]);

            buf[r] = 0; // ending the buf string with a null terminator

            int i = 0;

            //TEST
            //printf("Before while\n");

            while(buf[i] != 0){
                printf("%c",buf[i]);
                i++;
            }
            i = argLen - 1; // the length of the initial argument
            do{
                printf("%c",buf[i]);
                i--;
            } while (i >= 0);

            printf("\n");

            //close(p[0]);   // close pipe fd's

            printf("childpid: %d finished\n", getpid());
        }
        else { // this block is for the parent process

            printf("parentpid:%d of child1pid:%d and child2pid:%d\n", getpid(), c1Pid, c2Pid);

            close(p[0]);
            close(p[1]);
            wait(NULL);
            wait(NULL);
        }

    }
    return 0;
}
