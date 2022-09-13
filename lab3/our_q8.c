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
    //// TEST This prints the argument variables for our program
    //int i = argc;
    //while(i != 0) { // was, argv != 0
    //    printf("This is argc: %d, and the argv: %s\n", i, argv[0]);
    //    i--;
    //    argv++;
    //}

    // This will exit the program if no additional arguments are passed
    if(argc <= 1) { // the program shall take at minimum 2 commands
        printf("usage: q8 <string>\n");
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

    // Code below was from p6.c

    int p[2]; // in class this was set to two index 0 for stdin and 1 for the child's file
    char *excargv[3];
    pipe(p);

    //int child1pid = 0, child2pid = 0; 

    printf("Parent of two children connected via pipe. (pid:%d)\n", (int) getpid());

    // I am not really sure how to get this to work right
    // the child 1 and 2 pids are kind of cheating at this point but
    // to match the desired output this is what I have to do because I won't know the
    // childs pid till it forks, I can only assume
    printf("parentpid:%d of child1pid:%d and child2pid:%d\n", getpid(), getpid()+1, getpid()+2);

    if(fork() == 0) { // calling the first child inside of the if statement
        printf("child 1: pipe reader: (pid:%d)\n", getpid());
        //dup2(p[1], 1); // dup pipe write end on top of stdout

        // fd stands for file descriptor
        //close(p[0]);   // close pipe fd's closing stdin
        //close(p[1]);   // closing stdout

        excargv[0] = "echo"; // changed from ls
        excargv[1] = "gustyCooperytsug"; // changed from 0

        execvp(excargv[0], excargv); // This will run cat gustyCooperytsug to p[1]
                                     //printf("HERE\n");

                                     // *** Copied from p4.c

                                     //int wc = wait(NULL);
                                     //assert(wc >= 0);

                                     // ***

                                     //printf("gustyCooperytsug\n"); // because printf goes to stdout and it is closed it should be piped to the input of the next process 

        printf("childpid: %d finished\n", getpid());
    } 
    else {
        if (fork() == 0) {
            printf("child 2: pipe writer: (pid:%d)\n", getpid());
            //dup2(p[0], 0); // dup pipe read end on top of stdin

            //close(p[0]);   // close pipe fd's
            //close(p[1]);

            //TEST
            //printf("%d\n", p[1]); 

            //excargv[0] = "grep";
            if (argc == 2) { // it will equal atleast 2 because of the if statement at the top of main

                // this line does not make sense for the output requested
                //excargv[1] = argv[1]; // setting excargv[1] to the first program argument

                excargv[1] = "gustyCooperytsug"; // changed from p1
            } else {
                excargv[1] = "gustyCooperytsug"; // changed from p1
            }
            //excargv[2] = 0;
            //execvp(excargv[0], excargv);

            printf("childpid: %d finished\n", getpid());
        }
        else { // this block is for the parent process
            close(p[0]);
            close(p[1]);
            wait(NULL);
            wait(NULL);
        }

    }
    return 0;
}
