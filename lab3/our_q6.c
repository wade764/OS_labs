#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
/*
Write a slight modification of the previous program (q6.c), this time using waitpid
instead of wait
 */

// https://www.geeksforgeeks.org/wait-system-call-c/

//https://www.tutorialspoint.com/unix_system_calls/waitpid.htm
// waitpid(): on success, returns the process ID of the child whose state has changed;
// on error, -1 is returned;
// if WNOHANG was specified and no child(ren) specified by pid has yet changed state, then 0 is returned.

// pid_t wait(int *status); 
// pid_t waitpid(pid_t pid, int *status, int options); 

int main(int argc, char *argv[]) {
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello");
        
        int wc = waitpid(-1, NULL, WNOHANG); // putting -1 means wait for any child process
        // WNOHANG return immediately if no child process has exited
        
        perror("wait errno when called from child: ");
        printf("child wait wc: %d\n", wc);
    } else { // parent goes down this path (original process)
        printf("childpid: %d\n", rc);
        
        int wc = waitpid(-1, NULL, WNOHANG);
	    
        assert(wc >= 0); // this function is used for diagnostics in C
    // https://www.tutorialspoint.com/c_standard_library/c_macro_assert.htm

        printf(" goodbye\n");
        printf("waitrc: %d\n", wc);
    }
    return 0;
}
