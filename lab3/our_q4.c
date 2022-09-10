#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Write a program (q4.c) that calls fork and then calls some form of exec to run the
program /bin/ls. See if you can try all of the variants of exec, including (on Linux)
execl, execle, execlp, execv, execvp, and execvpe.*/

// source: https://linuxhint.com/exec_linux_system_call_c/

int main(int argc, char *argv[])
{
    //int x = 100;

    //printf("This is the value of x before calling fork(): %d\n", x);

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

        // These functions take a NULL parameter as the last entry to note when the end of
        // the arguments being passed end

        execl("/bin/ls", "-lh", "/home", NULL); // running ls -lh ~
        
        // This exec function take an array after the NULL parameter
        // works on Mac and Linux not sure about Windows on this one
        char *binaryPath = "/bin/bash";
        char *arg2 = "echo \"$WORD1 $WORD2 $PHRASE1\"" ;
        char *const envp[] = {"WORD1=Hello", "WORD2=Gusty", "PHRASE1=This is the execlp() function\n", NULL};
        execle(binaryPath, binaryPath, "-c", arg2, NULL, envp);

        //execlp("ls", "ls", "-lh", "/home", NULL);
        
        // this function works very similar to execl()
        // instead of passing the arguments you can just pass it the
        // command line variables
        //char *args[] = {"/bin/ls", "-lh", "/home", NULL};
        //execv("/bin/ls", args);

        //char *args[] = {"ls", "-lh", "/home", NULL};
        //execvp("ls", args);
        
        // This function throws an error or warning depending
        // on the OS but does work
        // https://linux.die.net/man/3/execvpe
        //char *args[] = {"ls", "-lh", "/home", NULL};
        //execvpe("ls", args, NULL);


        //printf("This is the value of x from the child: %d\n", x);
        //x = 215;
        //printf("The child changed x to: %d\n", x);
    }
    else
    {
        // the return value of fork is greater than 0 and is the parent

        printf("Hello I am the parent: %d\n", (int)getpid());
        //printf("This is the value of x from the parent: %d\n", x);

        // These functions take a NULL parameter as the last entry to note when the end of
        // the arguments being passed end

        //execl("/bin/ls", "-lh", "/home", NULL); // running ls -lh ~
        
        // This exec function take an array after the NULL parameter
        // works on Mac and Linux not sure about Windows on this one
        char *binaryPath = "/bin/bash";
        char *arg2 = "echo \"$WORD1 $WORD2 $PHRASE1\"" ;
        char *const envp[] = {"WORD1=Hello", "WORD2=Gusty", "PHRASE1=This is the execlp() function\n", NULL};
        execle(binaryPath, binaryPath, "-c", arg2, NULL, envp);

        //execlp("ls", "ls", "-lh", "/home", NULL);
        
        // this function works very similar to execl()
        // instead of passing the arguments you can just pass it the
        // command line variables
        //char *args[] = {"/bin/ls", "-lh", "/home", NULL};
        //execv("/bin/ls", args);

        //char *args[] = {"ls", "-lh", "/home", NULL};
        //execvp("ls", args);
        
        // This function throws an error or warning depending
        // on the OS but does work
        // https://linux.die.net/man/3/execvpe
        //char *args[] = {"ls", "-lh", "/home", NULL};
        //execvpe("ls", args, NULL);


        //x = 45;
        //printf("The parent changed x to: %d\n", x);
    }


    //printf("This pid: %d, is about to return, x = %d\n",(int) getpid(), x);
    return 0;
}