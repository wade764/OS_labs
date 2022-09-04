#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "proc.h"
#include "split.h"

#define BUFFER_LEN 100

int main()
{
    bootstrap();
    printf("firstLab started\n");
    char line[BUFFER_LEN];
    while (fgets(line, BUFFER_LEN, stdin) != NULL)
    {
        line[strlen(line) - 1] = 0; // remove \n from line
        if (line[0] == '#')
            continue;
        struct proc *p = NULL;
        int num;
        char **proc_stuff = split(line, " ", &num);
        if (proc_stuff == NULL || proc_stuff[0] == NULL){

            // TEST
            //printf("Main test 1\n");

            continue;
        }
        if (strcmp(proc_stuff[0], "fork") == 0){
            fork(proc_stuff[1], atoi(proc_stuff[2]), get_pid(proc_stuff[3]));

            // TEST
            //printf("Main test 2\n");

        } else if (strcmp(proc_stuff[0], "kill") == 0) {
            kill(get_pid(proc_stuff[1]));

            // TEST
            //printf("Main test 3\n");

        } else if (strcmp(proc_stuff[0], "printpid") == 0)
        {
            p = find_proc(get_pid(proc_stuff[1]));

            // TEST
            //printf("Main test 4\n");

            if (p != NULL) {
                printf("procname: %s, pid: %d\n", proc_stuff[1], p->pid);

                // TEST
                //printf("Main test 5\n");

            } else printf("procname: %s not found\n", proc_stuff[1]);
        }
        else if (strcmp(proc_stuff[0], "printppid") == 0)
        {
            p = find_proc(get_pid(proc_stuff[1]));

            // TEST
            //printf("Main test 6\n");
            if (p != NULL) {
                printf("procname: %s, ppid: %d\n", proc_stuff[1], p->parent->pid);

                // TEST
                //printf("Main test 7\n");

            } else { printf("procname: %s not found\n", proc_stuff[1]);

                // TEST
                //printf("Main test 8\n");
            } }
        else if (strcmp(proc_stuff[0], "printprocs") == 0) {
            print_procs();

            // TEST
            //printf("Main test 9\n");
        }
    }
}
