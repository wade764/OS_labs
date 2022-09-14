#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

/*
Write a program (q9.c) that connects a child process and a parent process with two pipes.
Parent process
a. reads string from terminal prior to fork
b. writes string read from terminal to first pipe
c. reads from second pipe
d. writes what is read from second pipe to terminal
Child process
e. reads from first pipe
f. concatenates fixed_str to what was read
g. writes concatenated string to second pipe
h. closes pipes
*/

int main(int argc, char **argv) {
    int p[2];
    char *excargv[3];
    
    //*** gdb says this causes a SIGPIPE, broken pipe
    pipe(p);

    char aString[100];
    if(argc == 2){
        strcpy(aString, argv[1]);
    } else { // not enough arguments
        printf("Please enter a string: ./our_p9.c <string>\n");
        scanf("%s",aString);
    }

    if(fork() == 0) { // The child process

        //TEST
        printf("I am the child\n");

        dup2(p[0], 0);
        char buf[100];
        int r = read(0, buf, 80);

        close(p[0]);
        close(p[1]);

        // now reopening the new pipe connecting back to parent
        //pipe(p);

        dup2(p[1], 1); // this time going to stdout

        char *concatMe = {"HelloGusty"};
        int concatLen = strlen(concatMe), total = concatLen + r; // adding r because its the len of buf the original string
        strcat(buf, concatMe);

        buf[total] = 0; // setting end of the buf array to NULL
        
        write(1, buf, total);

        close(p[0]);   // close pipe fd's
        close(p[1]);
        
        //excargv[0] = "ls";
        //excargv[1] = 0;
        //execvp(excargv[0], excargv);
        //printf("HERE\n");
    } else {
        //if (fork() == 0) {
            //printf("Right Child\n");
            //dup2(p[0], 0); // dup pipe read end on top of stdin
            //close(p[0]);   // close pipe fd's
            //close(p[1]);
            //excargv[0] = "grep";
            //if (argc == 2)
            //    excargv[1] = argv[1];
            //else
            //    excargv[1] = "p1";
            //excargv[2] = 0;
            //execvp(excargv[0], excargv);
        //}
        //else { // The parent

            //TEST
            printf("I am the parent\n");

            dup2(p[1], 1); // opening the write side of pipe to stdout

            write(1, aString, strlen(aString));
            //printf("Parent\n");
            
            close(p[0]);
            close(p[1]);

            wait(NULL); // waiting on the child to terminate

            // now the child process is done reopening the read end of the second pipe

            dup2(p[0], 0); // stdin

            char buf[100];
            int r = read(0, buf, 80);
            buf[r] = 0;
            
            close(p[0]);
            close(p[1]);
            
            int i = 0;
            
            printf("%s\n", buf);
            
            //while(buf[i] != 0) {
            //    printf("%c",buf[i]);
            //    i++;

            //    //TEST
            //    printf("Stuck in loop?\n");
            //}
            //printf("\n");

            //The program acts like it is stuck in a loop I am adding the line below to exit
            //exit(0);

            // The exit() does not work I tried commenting out wait that does not work either

        }
    //}
    return 0;
}
