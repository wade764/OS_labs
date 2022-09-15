#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

/*
Write a new program (q12.c) that mimics p6.c to be the hardcoded version of the following shell command.
$ cat p7.c | grep close
*/

int main(int argc, char **argv) {
    int p[2];
    char *excargv[3];
    pipe(p);
    if(fork() == 0) {
        printf("Left Child\n");
        dup2(p[1], 1); // dup pipe write end on top of stdout
        close(p[0]);   // close pipe fd's
        close(p[1]);
        //excargv[0] = "grep";
        //excargv[1] = " close";
        //excargv[1] = 0;
        //excargv[2] = 0;
        //execvp(excargv[0], excargv);
        //printf("close");

        char *args[] = {"grep", "close", NULL};
        execvp("grep", args);
    } 
    else {
        if (fork() == 0) {
            printf("Right Child\n");
            dup2(p[0], 0); // dup pipe read end on top of stdin
            close(p[0]);   // close pipe fd's
            close(p[1]);
            excargv[0] = "cat"; // this was "grep"
            if (argc == 2)
                excargv[1] = argv[1];
            else
                excargv[1] = "p7.c"; // this was "p1"
            excargv[2] = 0;
            execvp(excargv[0], excargv);
        }
        else {
            printf("Parent\n");
            close(p[0]);
            close(p[1]);
            wait(NULL);
            wait(NULL);
        }
    }
    return 0;
}