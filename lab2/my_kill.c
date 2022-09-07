#include <stdio.h>
#include <stdlib.h>
#include <string.h> // added to use the strcat() function

#include <errno.h> // needed for errno
#include <getopt.h>
#include <signal.h> // must include this for kill()
#include <stdbool.h>
#include <unistd.h>

// A lot of this code was copied from maingetopts, I have modified parts as
// needed I have made a reference to a source that covered printing out FILE
// contents

#define FN_LEN 256

// This bool is used at the end of get_opts
// I used this to determine if a process id was entered or not
bool isAPid = false;

struct Options {
    bool using_h; // -h, human readable
    bool using_f; // -f, has a file optarg

    char filename[FN_LEN]; // -f optarg

    // *** VERY IMPORTANT, if you declare a "flexible string i.e. []" you must put
    // it at the end of the struct object!
    char process_id[128]; // This is a string used for the pid I am giving is a
                          // random size of 128
};

static void init_opts(struct Options *opts) {
    opts->using_h = false;
    opts->using_f = false;

    for (int i = 0; i < FN_LEN; i++)
        opts->filename[i] = 0;

    // setting the process_id string to null just like the filename above
    for (int i = 0; i < 128; i++)
        opts->process_id[i] = 0;
}

struct Options opts;

struct Options get_opts(int count, char *args[]) {

    init_opts(&opts);
    int opt;

    // TEST
    // printf("Initialized opts\n");

    // variables used in the for loop below
    int count_temp = count;
    char **args_temp = args;

    // must include d as one of the shortopts if it is left out calling strcpy
    // will create a seg fault
    while ((opt = getopt(count, args, ":f:hd")) !=
            -1) { // the optional string before was ":f:had"

        // TEST
        // printf("This is count: %d, and this is args[1][0]: %c, inside of
        // while\n", count, args[1][0]);

        switch (opt) {
            case 'h':
                opts.using_h = true;
                break;

            case 'f':
                opts.using_f = true;

                // TEST
                // printf("Before strcpy() for f\n");

                strcpy(opts.filename, optarg);

                // TEST
                // printf("After strcpy() for f\n");

                break;
            case ':':
                printf("-f needs a value\n");
                break;
            case '?':
                printf("Unknown option\n");
                exit(-1);
        }
    }
    // TEST
    // printf("I am outside the for loop\n");

    // copied and modified from mainargs.c
    for (; count_temp > 1; count_temp--, args_temp++) {
        // my thinking is that the numbers are not led by a - so as long as the
        // string is not NULL it should enter this loop

        // TEST
        // printf("I am in the for loop\n");
        // printf("this is argc: %d this is args_temp[1][0]: %d\n",count_temp,
        // atoi(&args_temp[1][0]));

        // If it equals a number then we know it is a pid so set it to the string
        if (args_temp[1][0] == '-') { // do nothing it will increment

            // TEST
            // printf("I am in the '-' if block\n");

        } else {

            // TEST
            // printf("I am in the else block\n");

            args_temp[1][0] == '0' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '1' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '2' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '3' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '4' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '5' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '6' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '7' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '8' ? strcat(opts.process_id, &args_temp[1][0]) : 0;
            args_temp[1][0] == '9' ? strcat(opts.process_id, &args_temp[1][0]) : 0;

            // I had to include this code below inorder to get the Error statement to
            // work properly
            args_temp[1][0] == '0' ? isAPid = true : 0;
            args_temp[1][0] == '1' ? isAPid = true : 0;
            args_temp[1][0] == '2' ? isAPid = true : 0;
            args_temp[1][0] == '3' ? isAPid = true : 0;
            args_temp[1][0] == '4' ? isAPid = true : 0;
            args_temp[1][0] == '5' ? isAPid = true : 0;
            args_temp[1][0] == '6' ? isAPid = true : 0;
            args_temp[1][0] == '7' ? isAPid = true : 0;
            args_temp[1][0] == '8' ? isAPid = true : 0;
            args_temp[1][0] == '9' ? isAPid = true : 0;
        }
    }

    // TEST
    // printf("This is the process_id string: %s\n", opts.process_id);

    if (!isAPid) { // if ((count_temp - optind) != 1)
        printf("Error - command format is $ my_kill -options pid\n");
        exit(-1);
    }

    isAPid = false;

    return opts;
}

int main(int argc, char *argv[]) {

    FILE *fptr;

    // TEST
    // printf("About to call get_opts\n");

    struct Options o = get_opts(argc, argv);

    // TEST
    // printf("Returning from get_opts\n");

    printf("%s", opts.using_h ? "Hello World\n" : "" /* print an empty string */);

    // TEST
    // printf("In main before if\n");

    if (opts.using_f) {
        // ** Added this code to get_opts source:
        // https://www.geeksforgeeks.org/c-program-print-contents-file/

        // Open file
        fptr = fopen(opts.filename, "r");
        if (fptr == NULL) {
            printf("Cannot open file \n");
            exit(0);
        }

        // Read contents from file
        char c = fgetc(fptr);
        while (c != EOF) {
            printf("%c", c);
            c = fgetc(fptr);
        }

        fclose(fptr);
        // **
    }

    // TEST
    // printf("In main after if\n");

    printf("my_kill pid: %d\n", getpid()); // get my_kill's pid

    int status = kill(atoi(opts.process_id), SIGINT); // valid_num is the pid to kill
    int errnum = errno;
    if (status == -1) {
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error killing process: %s\n", strerror(errnum));
    }
    return 0;
}
